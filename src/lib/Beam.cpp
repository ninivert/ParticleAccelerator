#include "src/include/bundle/Beam.bundle.h"

using namespace std;

/****************************************************************
 * Constructors
 ****************************************************************/

Beam::Beam(Particle const& defaultParticle, size_t const& particleCount, double const& lambda, Accelerator const& acc)
: defaultParticle_ptr(defaultParticle.copy()), particleCount(particleCount), lambda(lambda)
{
	if (particleCount == 0) {
		ERROR(EXCEPTIONS::NO_PARTICLES);
	}
	if (lambda < 1) {
		ERROR(EXCEPTIONS::BAD_LAMBDA);
	}

	double orientation(Vector3D::tripleProduct(Vector3D(0, 0, 1), defaultParticle_ptr->getPos(), defaultParticle_ptr->getPos() + defaultParticle_ptr->getSpeed()));
	bool clockwise((orientation < 0));
	int lastPart(particleCount / lambda);

	for (double i(0); i < lastPart; ++i) {
		// i is a double to avoid division of 2 integers
		double progress(i / lastPart);

		this->particles_ptr.push_back(unique_ptr<Particle>(new Particle
			(acc.getPosAtProgress(progress),
			lambda * CONVERT::EnergySItoGeV(defaultParticle_ptr->getEnergy()),
			acc.getVelAtProgress(progress, clockwise),
			lambda * CONVERT::MassSItoGeV(defaultParticle_ptr->getMass()),
			lambda * defaultParticle_ptr->getChargeNumber()
		)));
		acc.initParticleToClosestElement(*particles_ptr[i]);
	}
}

Beam::Beam(Particle const& defaultParticle)
: defaultParticle_ptr(defaultParticle.copy()), particleCount(1), lambda(1)
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

/****************************************************************
 * Methods
 ****************************************************************/

void Beam::step(double const& dt, bool const& methodChapi) {
	if (abs(dt) < GLOBALS::DELTA) { return; }

	for (unique_ptr<Particle> const& particle_ptr : particles_ptr) {
		particle_ptr->step(dt, methodChapi);
	}
}

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
		<< setw(STYLES::PADDING_LG) << "Mean energy (macro) "
		<< setw(STYLES::PADDING_MD) << getMeanEnergy()
		<< " (" << UNITS::ENERGY << ")"
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
