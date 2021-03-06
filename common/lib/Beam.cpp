#include "include/bundle/Beam.bundle.h"

using namespace std;

/****************************************************************
 * Constructors
 ****************************************************************/

Beam::Beam(Particle const& defaultParticle, size_t const& particleCount, double lambda, Accelerator const& acc, Renderer * engine)
: Drawable(engine),
  defaultParticle_ptr(defaultParticle.copy()), particleCount(particleCount), lambda(lambda)
{
	if (particleCount == 0) {
		ERROR(EXCEPTIONS::NO_PARTICLES);
	}
	if (lambda < 1) {
		ERROR(EXCEPTIONS::BAD_LAMBDA);
	}

	bool beamFromParticle(acc.getBeamFromParticle());

	if (beamFromParticle) {
		int lastPart(particleCount / lambda);

		unique_ptr<Particle> temporaryPart(
			unique_ptr<Particle>(defaultParticle.scaledCopy(
				defaultParticle_ptr->getPos(),
				CONVERT::EnergySItoGeV(defaultParticle_ptr->getEnergy()),
				defaultParticle_ptr->getSpeed(),
				CONVERT::MassSItoGeV(defaultParticle_ptr->getMass()),
				defaultParticle_ptr->getChargeNumber(),
				lambda
			))
		);

		// To trigger the exception if the initial particle is outside the accelerator
		acc.initParticleToClosestElement(*temporaryPart);

		for (double i(0); i < lastPart; ++i) {
			temporaryPart->getElementPtr()->updatePointedElement(*temporaryPart);
			temporaryPart->step();
			this->particles_ptr.push_back(temporaryPart->copy());
		}


	} else {
		// To trigger the exception if the initial particle is outside the accelerator
		acc.initParticleToClosestElement(*defaultParticle_ptr);

		double orientation(Vector3D::tripleProduct(Vector3D(0, 0, 1), defaultParticle_ptr->getPos(), defaultParticle_ptr->getPos() + defaultParticle_ptr->getSpeed()));
		bool clockwise((orientation < 0));
		int lastPart(particleCount / lambda);

		for (double i(0); i < lastPart; ++i) {
			// i is a double to avoid division of 2 integers
			double progress(i / lastPart);

			this->particles_ptr.push_back(
				unique_ptr<Particle>(defaultParticle.scaledCopy(
					acc.getPosAtProgress(progress),
					CONVERT::EnergySItoGeV(defaultParticle_ptr->getEnergy()),
					acc.getVelAtProgress(progress, clockwise),
					CONVERT::MassSItoGeV(defaultParticle_ptr->getMass()),
					defaultParticle_ptr->getChargeNumber(),
					lambda
				))
			);

			acc.initParticleToClosestElement(*particles_ptr[i]);
		}
	}
}

Beam::Beam(Particle const& defaultParticle, Renderer * engine)
: Drawable(engine),
  defaultParticle_ptr(defaultParticle.copy()), particleCount(1), lambda(1)
{
	if (particleCount == 0) {
		ERROR(EXCEPTIONS::NO_PARTICLES);
	}
	if (lambda < 1) {
		ERROR(EXCEPTIONS::BAD_LAMBDA);
	}
	particles_ptr.push_back(defaultParticle.copy());
}

/****************************************************************
 * Destructor
 ****************************************************************/

Beam::~Beam() {
	defaultParticle_ptr.reset();
	particles_ptr.clear();
}

/****************************************************************
 * Getters
 ****************************************************************/

double Beam::getMeanEnergy() const {
	double mean(0.0);
	for (unique_ptr<Particle> const& particle_ptr : particles_ptr) {
		mean += particle_ptr->getEnergy();
	}
	mean /= particles_ptr.size();
	return CONVERT::EnergySItoGeV(mean);
}

double Beam::getGamma(size_t part) const {
	if (part < particles_ptr.size()) {
		return particles_ptr[part]->getGamma();
	} else {
		ERROR(EXCEPTIONS::NO_PARTICLES);
	}
}

Vector3D Beam::getPos(size_t part) const {
	if (part < particles_ptr.size()) {
		return particles_ptr[part]->getPos();
	} else {
		ERROR(EXCEPTIONS::NO_PARTICLES);
	}
}

double Beam::getCharge() const {
	return (lambda * defaultParticle_ptr->getCharge());
}

double Beam::getEmittanceR() const {
	Vector3D means(getRMeans());

	double moyR_Squared(means.getX());
	double moyVr_Squared(means.getY());
	double moyR_Vr(means.getZ());
	double emittanceR(moyR_Squared * moyVr_Squared - moyR_Vr * moyR_Vr);

	if (emittanceR < GLOBALS::DELTA_DIV0) { emittanceR = 0; }
	return sqrt(emittanceR);
}

double Beam::getEmittanceZ() const {
	Vector3D means(getZMeans());

	double moyZ_Squared(means.getX());
	double moyVz_Squared(means.getY());
	double moyZ_Vz(means.getZ());
	double emittanceZ(moyZ_Squared * moyVz_Squared - moyZ_Vz * moyZ_Vz);

	if (emittanceZ < GLOBALS::DELTA_DIV0) { emittanceZ = 0; }
	return sqrt(emittanceZ);
}

Vector3D const Beam::getEllipsePhaseCoefR() const {
	double emittanceR(getEmittanceR());

	// No deviation along the R-axis
	// => the area of the ellipse is 0
	// => We assume that they are all 0 bcs we have no mean to calculate them (0/0)
	if (abs(emittanceR) < GLOBALS::DELTA_DIV0) {
		return Vector3D();
	}

	Vector3D means(getRMeans());

	// A11_R = <vr²> / emittanceR
	// A22_R = <r²> / emittanceR
	// A12_R = <r * vr> / emittanceR

	return Vector3D(means.getY(), means.getX(), - means.getZ()) / emittanceR;
}

Vector3D const Beam::getEllipsePhaseCoefZ() const {
	double emittanceZ(getEmittanceZ());

	// No deviation along the Z-axis
	// => The area of the ellipse is 0
	// => We assume that they are all 0 bcs we have no mean to calculate them (0/0)
	if (abs(emittanceZ) < GLOBALS::DELTA_DIV0) {
		return Vector3D();
	}

	Vector3D means(getZMeans());

	// A11_Z = <vz²> / emittanceZ
	// A22_Z = <z²> / emittanceZ
	// A12_Z = <z * vz> / emittanceZ

	return Vector3D(means.getY(), means.getX(), - means.getZ()) / emittanceZ;
}

Vector3D const Beam::getRMeans() const {
	double moyR_Squared(0.0);
	double moyVr_Squared(0.0);
	double moyR_Vr(0.0);
	double r(0.0);
	double vr(0.0);
	Vector3D perpDirectionElement;

	for (unique_ptr<Particle> const& particle_ptr : particles_ptr) {
		perpDirectionElement = particle_ptr->getElementPtr()->getNormalDirection(particle_ptr->getPos());
		r = particle_ptr->getPos() * perpDirectionElement;
		vr = particle_ptr->getSpeed() * perpDirectionElement;

		moyR_Squared	+= r * r;
		moyVr_Squared	+= vr * vr;
		moyR_Vr 		+= r * vr;
	}

	return (Vector3D(moyR_Squared, moyVr_Squared, moyR_Vr) /= particleCount);
}

Vector3D const Beam::getZMeans() const {
	double moyZ_Squared(0.0);
	double moyVz_Squared(0.0);
	double moyZ_Vz(0.0);
	double z(0.0);
	double vz(0.0);

	for (unique_ptr<Particle> const& particle_ptr : particles_ptr) {
		z = particle_ptr->getPos().getZ();
		vz = particle_ptr->getSpeed().getZ();

		moyZ_Squared	+= z * z;
		moyVz_Squared	+= vz * vz;
		moyZ_Vz 		+= z * vz;
	}

	return (Vector3D(moyZ_Squared, moyVz_Squared, moyZ_Vz) /= particleCount);
}

/****************************************************************
 * Methods
 ****************************************************************/

void Beam::step(double dt, bool methodChapi) {
	if (abs(dt) < GLOBALS::DELTA_DIV0) { return; }

	// exertInteractions();

	for (unique_ptr<Particle> & particle_ptr : particles_ptr) {
		particle_ptr->step(dt, methodChapi);
	}

	// At the end because we can't initialize particles (basis of beams) outside the accelerator
	clearDeadParticles();
}

// void Beam::exertInteractions() {
// 	if (particles_ptr.size() < 2) { return; }

// 	double charge(lambda * defaultParticle_ptr->getCharge());
// 	double cst(charge * charge / (4 * M_PI * CONSTANTS::EPISLON0));

// 	for (size_t i(0); i < particles_ptr.size() - 1; ++i) {
// 		for (size_t j(i + 1); j < particles_ptr.size(); ++j) {
// 			Vector3D force(particles_ptr[j]->getPos() - particles_ptr[i]->getPos());
// 			double r(force.norm());
// 			// Arbitrary gamma because of small relative speed
// 			double gamma(particles_ptr[i]->getGamma());
// 			force *= cst / (r * r * r * gamma * gamma);
// 			particles_ptr[j]->exertForce(force);
// 			particles_ptr[i]->exertForce(-force);
// 		}
// 	}
// }

void Beam::clearDeadParticles() {
	// Remove particles that are out of the simulation
	size_t size(particles_ptr.size());
	for (size_t i(0); i < size; ++i) {
		if (particles_ptr[i]->getElementPtr()->isInWall(*particles_ptr[i])) {
			particles_ptr[i].reset();

			// using swap + pop_back
			// faster but changes indexes
			swap(particles_ptr[i], particles_ptr[size - 1]);
			particles_ptr.pop_back();

			// using erase
			// slower but preserves indexes
			// particles_ptr.erase(particles_ptr.begin() + i);

			// We resized the vector so we need to take it into account
			--size;
			// We need to evalute the new `particles_ptr[i]` that has been swapped
			--i;
		}
	}
}

bool Beam::noParticle() const {
	if (particles_ptr.size() > 0) { return false; }
	else { return true; }
}

void Beam::updatePointedElement(bool methodChapi) const {
	for (unique_ptr<Particle> const& particle_ptr : particles_ptr) {
		particle_ptr->getElementPtr()->updatePointedElement(*particle_ptr, methodChapi);
	}
}

void Beam::updateProgresses(vector<double> & associatedProgress, Accelerator const& acc) const {
	associatedProgress.clear();
	for (unique_ptr<Particle> const& particle_ptr : particles_ptr) {
		associatedProgress.push_back(acc.getParticleProgress(particle_ptr->getPos()));
	}
}

void Beam::exertForce(Vector3D const& force, size_t part) {
	if (part < particles_ptr.size()) {
		particles_ptr[part]->exertForce(force);
	} else {
		ERROR(EXCEPTIONS::NO_PARTICLES);
	}
}

string const Beam::to_string() const {
	stringstream stream;
	stream << setprecision(STYLES::PRECISION);
	stream << left;
	double emittanceR(getEmittanceR());
	double emittanceZ(getEmittanceZ());
	stream
		<< STYLES::COLOR_CYAN
		<< STYLES::FORMAT_BOLD
		<< "Beam contains " << particles_ptr.size() << " macroparticle(s)"
		<< STYLES::NONE << endl
		// Mean Energy
		<< setw(STYLES::PADDING_XSM) << ""
		<< setw(STYLES::PADDING_LG) << "Mean energy (macro) "
		<< setw(STYLES::PADDING_MD) << getMeanEnergy()
		<< " (" << UNITS::ENERGY << ")"
		<< endl
		// EmittanceR
		<< setw(STYLES::PADDING_XSM) << ""
		<< setw(STYLES::PADDING_MD) << "EmittanceR"
		<< setw(STYLES::PADDING_LG) << emittanceR
		<< " (" << UNITS::SCALAR << ")"
		<< endl
		// EmittanceZ
		<< setw(STYLES::PADDING_XSM) << ""
		<< setw(STYLES::PADDING_MD) << "EmittanceZ"
		<< setw(STYLES::PADDING_LG) << emittanceZ
		<< " (" << UNITS::SCALAR << ")"
		<< endl;

	// Coeff of Phase Ellipse R
	Vector3D coeff(getEllipsePhaseCoefR());
	if (emittanceR < GLOBALS::DELTA_DIV0) {
		stream
			<< setw(STYLES::PADDING_XSM) << ""
			<< setw(STYLES::PADDING_MD) << "Coeff EllipseR"
			<< setw(STYLES::PADDING_MD) << "The emittance in R <= 0, the coefficients are undefined for such behaviour"
			<< endl;
	} else {
		// cout << coeff.getX() * coeff.getY() - coeff.getZ() * coeff.getZ() << endl;
		stream
			// Coeff of Phase Ellipse R
			<< setw(STYLES::PADDING_XSM) << ""
			<< setw(STYLES::PADDING_MD) << "Coeff EllipseR"
			<< setw(STYLES::PADDING_MD) << "A11 R : " << coeff.getX()
			<< endl
			<< setw(STYLES::PADDING_XSM) << "" << setw(STYLES::PADDING_MD) << ""
			<< setw(STYLES::PADDING_MD) << "A22 R : " << coeff.getY()
			<< endl
			<< setw(STYLES::PADDING_XSM) << "" << setw(STYLES::PADDING_MD) << ""
			<< setw(STYLES::PADDING_MD) << "A12 R : " << coeff.getZ()
			<< endl;
	}

	coeff = getEllipsePhaseCoefZ();
	// Coeff of Phase Ellipse Z
	if (emittanceZ < GLOBALS::DELTA_DIV0) {
		stream
			<< setw(STYLES::PADDING_XSM) << ""
			<< setw(STYLES::PADDING_MD) << "Coeff EllipseZ"
			<< setw(STYLES::PADDING_MD) << "The emittance in Z <= 0, the coefficients are undefined for such behaviour"
			<< endl;
	} else {
		// cout << coeff.getX() * coeff.getY() - coeff.getZ() * coeff.getZ() << endl;
		stream
			<< setw(STYLES::PADDING_XSM) << ""
			<< setw(STYLES::PADDING_MD) << "Coeff EllipseZ"
			<< setw(STYLES::PADDING_MD) << "A11 Z : " << coeff.getX()
			<< endl
			<< setw(STYLES::PADDING_XSM) << "" << setw(STYLES::PADDING_MD) << ""
			<< setw(STYLES::PADDING_MD) << "A22 Z : " << coeff.getY()
			<< endl
			<< setw(STYLES::PADDING_XSM) << "" << setw(STYLES::PADDING_MD) << ""
			<< setw(STYLES::PADDING_MD) << "A12 Z : " << coeff.getZ()
			<< endl;
	}

	stream
		// Default Particle
		<< setw(STYLES::PADDING_MD) << "Default Particle "
		<< endl
		<< setw(STYLES::PADDING_LG) << *defaultParticle_ptr;
	// for (auto const& particle_ptr : particles_ptr) { stream << *particle_ptr; }
	return stream.str();
}

/****************************************************************
 * Operator overloading
 ****************************************************************/

ostream& operator << (ostream& stream, Beam const& beam) {
	return stream << beam.to_string();
}

/****************************************************************
 * Drawing
 ****************************************************************/

void Beam::draw(Renderer * engine_ptr) const {
	// No engine specified, try to substitute it ?
	if (engine_ptr == nullptr) {
		// Do we have another engine ?
		if (this->engine_ptr == nullptr) {
			ERROR(EXCEPTIONS::NULLPTR);
		} else {
			engine_ptr = this->engine_ptr;
		}
	}
	engine_ptr->draw(*this);
}

void Beam::drawParticles() const {
	if (engine_ptr == nullptr) ERROR(EXCEPTIONS::NULLPTR);
	for (unique_ptr<Particle> const& particle_ptr : particles_ptr) {
		particle_ptr->draw(engine_ptr);
	}
}
