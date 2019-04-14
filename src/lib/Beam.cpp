#include "src/include/bundle/Beam.bundle.h"

using namespace std;

/****************************************************************
 * Constructor
 ****************************************************************/

Beam::Beam(Particle const& defaultParticle, size_t const& particleCount, double const& lambda)
: defaultParticle_ptr(defaultParticle.copy()), particleCount(particleCount), lambda(lambda)
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
	mean /= particleCount;
	return CONVERT::EnergySItoGeV(mean);
}

double Beam::getEmittanceR() const {
	Vector3D means(getRMeans());

	double A11_R(means.getX());
	double A22_R(means.getY());
	double A12_R(means.getZ());
	double emittanceR(A11_R * A22_R - A12_R * A12_R);

	return sqrt(emittanceR);
}

double Beam::getEmittanceZ() const {
	Vector3D means(getZMeans());

	double A11_Z(means.getX());
	double A22_Z(means.getY());
	double A12_Z(means.getZ());
	double emittanceZ(A11_Z * A22_Z - A12_Z * A12_Z);

	return sqrt(emittanceZ);
}

Vector3D const Beam::getEllipsePhaseCoefR() const {
	double emittanceR(getEmittanceR());

	// No deviation along the R-axis
	// => the area of the ellipse is 0
	// => all R-coeff are 0
	if (emittanceR < GLOBALS::DELTA) {
		return Vector3D();
	}

	Vector3D means(getRMeans());

	// A11_R = <vr²> / emittanceR
	// A22_R = <r²> / emittanceR
	// A12_R = <r * vr> / emittanceR

	Vector3D coeff(means.getY(), means.getX(), - means.getZ());
	coeff /= emittanceR;
	return coeff;
}

Vector3D const Beam::getEllipsePhaseCoefZ() const {
	double emittanceZ(getEmittanceZ());

	// No deviation along the Z-axis
	// => the area of the ellipse is 0
	// => all Z-coeff are 0
	if (emittanceZ < GLOBALS::DELTA) {
		return Vector3D();
	}

	Vector3D means(getZMeans());

	// A11_Z = <vz²> / emittanceZ
	// A22_Z = <z²> / emittanceZ
	// A12_Z = <z * vz> / emittanceZ

	Vector3D coeff(means.getY(), means.getX(), - means.getZ());

	return coeff;
}

Vector3D const Beam::getRMeans() const {
	double moyR_Squared(0.0);
	double moyVr_Squared(0.0);
	double moyR_Vr(0.0);
	double r(0.0);
	double vr(0.0);
	Vector3D perpDirectionElement;

	for (unique_ptr<Particle> const& particle_ptr : particles_ptr) {
		perpDirectionElement = particle_ptr->getElementPtr()->perpDirection(particle_ptr->getPos());
		r = (particle_ptr->getPos() - particle_ptr->getElementPtr()->getPosIn()) * perpDirectionElement;
		vr = particle_ptr->getSpeed() * perpDirectionElement;

		moyR_Squared	+= r * r;
		moyVr_Squared	+= vr * vr;
		moyR_Vr 		+= r * vr;
	}

	Vector3D means(moyR_Squared, moyVr_Squared, moyR_Vr);
	means /= particleCount;

	return means;
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

	Vector3D means(moyZ_Squared, moyVz_Squared, moyZ_Vz);
	means /= particleCount;

	return means;
}

/****************************************************************
 * Methods
 ****************************************************************/

string Beam::to_string() const {
	stringstream stream;
	stream << setprecision(STYLES::PRECISION);
	stream << left;
	stream
		<< STYLES::COLOR_YELLOW
		<< STYLES::FORMAT_BOLD
		<< "Beam contains " << particles_ptr.size() << " macroparticle(s)"
		<< STYLES::NONE << endl
		// Mean Energy
		<< setw(STYLES::PADDING_XSM) << ""
		<< setw(STYLES::PADDING_MD) << "Mean energy"
		<< setw(STYLES::PADDING_LG) << getMeanEnergy()
		<< " (" << UNITS::ENERGY << ")"
		<< endl
		// EmittanceR
		<< setw(STYLES::PADDING_XSM) << ""
		<< setw(STYLES::PADDING_MD) << "EmittanceR"
		<< setw(STYLES::PADDING_LG) << getEmittanceR()
		<< " (" << UNITS::SCALAR << ")"
		<< endl
		// EmittanceZ
		<< setw(STYLES::PADDING_XSM) << ""
		<< setw(STYLES::PADDING_MD) << "EmittanceZ"
		<< setw(STYLES::PADDING_LG) << getEmittanceZ()
		<< " (" << UNITS::SCALAR << ")"
		<< endl;
	Vector3D coeff(getEllipsePhaseCoefR());
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
	cout << coeff.getX() * coeff.getY() -coeff.getZ() * coeff.getZ() << endl;
	coeff = getEllipsePhaseCoefZ();
	stream
		// Coeff of Phase Ellipse Z
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
