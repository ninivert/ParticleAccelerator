#include "include/bundle/Particle.bundle.h"

using namespace std;

/****************************************************************
 * Constructors
 ****************************************************************/

// Constructor for init with velocity

// Particle::Particle(Vector3D const& pos, Vector3D const& speed, double _mass, int charge, bool unitGeV, Renderer * engine_ptr)
// : Drawable(engine_ptr), mass(_mass), charge(charge), pos(pos), forces(Vector3D()), element_ptr(nullptr)
// {
// 	if (unitGeV) mass = CONVERT::MassGeVtoSI(mass);
// 	momentum = speed * mass;
// }

// Constructor for init with velocity and energy

Particle::Particle(Vector3D const& pos, double energy, Vector3D speed, double _mass, int charge, bool unitGeV, Renderer * engine_ptr)
: Drawable(engine_ptr), mass(_mass), charge(charge), pos(pos), forces(Vector3D()), element_ptr(nullptr)
{
	double factor(0);

	if (unitGeV) {
		// Order matters here: we first compute m²/E², then convert the mass
		factor = mass * mass / (energy * energy);
		mass = CONVERT::MassGeVtoSI(mass);
	} else {
		factor = CONSTANTS::C * CONSTANTS::C * mass / energy;
		factor *= factor;
	}

	momentum = ~speed * mass * CONSTANTS::C * sqrt(1 - factor);
}

// Electrons

// Electron::Electron(Vector3D const& pos, Vector3D const& speed, bool unitGeV, Renderer * engine_ptr, double lambda)
// : Particle(pos, speed, CONSTANTS::M_ELECTRON * lambda, -1 * lambda, unitGeV, engine_ptr)
// {}

Electron::Electron(Vector3D const& pos, double energy, Vector3D speed, bool unitGeV, Renderer * engine_ptr, double lambda)
: Particle(pos, energy, speed, CONSTANTS::M_ELECTRON * lambda, -1 * lambda, unitGeV, engine_ptr)
{}

// Protons

// Proton::Proton(Vector3D const& pos, Vector3D const& speed, bool unitGeV, Renderer * engine_ptr, double lambda)
// : Particle(pos, speed, CONSTANTS::M_PROTON * lambda, 1 * lambda, unitGeV, engine_ptr)
// {}

Proton::Proton(Vector3D const& pos, double energy, Vector3D speed, bool unitGeV, Renderer * engine_ptr, double lambda)
: Particle(pos, energy, speed, CONSTANTS::M_PROTON * lambda, 1 * lambda, unitGeV, engine_ptr)
{}

// AntiProtons

// AntiProton::AntiProton(Vector3D const& pos, Vector3D const& speed, bool unitGeV, Renderer * engine_ptr, double lambda)
// : Particle(pos, speed, CONSTANTS::M_PROTON * lambda, -1 * lambda, unitGeV, engine_ptr)
// {}

AntiProton::AntiProton(Vector3D const& pos, double energy, Vector3D speed, bool unitGeV, Renderer * engine_ptr, double lambda)
: Particle(pos, energy, speed, CONSTANTS::M_PROTON * lambda, -1 * lambda, unitGeV, engine_ptr)
{}


/****************************************************************
 * Destructor
 ****************************************************************/

Particle::~Particle() { element_ptr = nullptr; }

/****************************************************************
 * Polymorphic copy for Beam
 ****************************************************************/

unique_ptr<Particle> Particle::copy() const {
	return unique_ptr<Particle>(new Particle(*this));
}

unique_ptr<Particle> Proton::copy() const {
	return unique_ptr<Particle>(new Proton(*this));
}

unique_ptr<Particle> AntiProton::copy() const {
	return unique_ptr<Particle>(new AntiProton(*this));
}

unique_ptr<Particle> Electron::copy() const {
	return unique_ptr<Particle>(new Electron(*this));
}

/****************************************************************
 * Scaled copies
 ****************************************************************/

unique_ptr<Particle> Particle::scaledCopy(Vector3D const& pos, double energy, Vector3D speed, double _mass, int charge, double lambda) const {
	return unique_ptr<Particle>(new Particle(pos, energy * lambda, speed, _mass * lambda, charge * lambda));
}

unique_ptr<Particle> Proton::scaledCopy(Vector3D const& pos, double energy, Vector3D speed, double _mass, int charge, double lambda) const {
	(void) _mass;
	(void) charge;
	return unique_ptr<Particle>(new Proton(pos, energy, speed, lambda));
}

unique_ptr<Particle> AntiProton::scaledCopy(Vector3D const& pos, double energy, Vector3D speed, double _mass, int charge, double lambda) const {
	(void) _mass;
	(void) charge;
	return unique_ptr<Particle>(new AntiProton(pos, energy, speed, lambda));
}

unique_ptr<Particle> Electron::scaledCopy(Vector3D const& pos, double energy, Vector3D speed, double _mass, int charge, double lambda) const {
	(void) _mass;
	(void) charge;
	return unique_ptr<Particle>(new Electron(pos, energy, speed, lambda));
}

/****************************************************************
 * Getters
 ****************************************************************/

double Particle::getEnergy() const {
	return getGamma() * getMass() * CONSTANTS::C * CONSTANTS::C;
}

double Particle::getGamma() const {
	double tmp = getSpeed().norm() / CONSTANTS::C;
	return 1 / sqrt(1 - tmp * tmp);
}

double Particle::getMass() const { return mass; }

double Particle::getCharge() const { return getChargeNumber() * CONSTANTS::EV; }

int Particle::getChargeNumber() const { return charge; }

Vector3D Particle::getSpeed() const { return getMoment() / getMass(); }

Vector3D Particle::getForces() const { return forces; }

Vector3D Particle::getMoment() const { return momentum; }

Vector3D Particle::getPos() const { return pos; }

Element const * Particle::getElementPtr() const {
	if (element_ptr != nullptr) {
		return element_ptr;
	} else {
		ERROR(EXCEPTIONS::NULLPTR);
	}
}

/****************************************************************
 * Setters
 ****************************************************************/

void Particle::setElement(Element * _element_ptr) {
	// Protection against empty pointers
	if (_element_ptr != nullptr) {
		element_ptr = _element_ptr;
	} else {
		ERROR(EXCEPTIONS::NULLPTR);
	}
}

/****************************************************************
 * Methods
 ****************************************************************/

string const Particle::to_string() const {
	stringstream stream;
	stream << setprecision(STYLES::PRECISION);
	stream << left;
	stream
		// Position
		<< setw(STYLES::PADDING_XSM) << ""
		<< setw(STYLES::PADDING_MD) << "Position"
		<< setw(STYLES::PADDING_LG) << getPos()
		<< " (" << UNITS::DISTANCE << ")"
		<< endl
		// Speed
		<< setw(STYLES::PADDING_XSM) << ""
		<< setw(STYLES::PADDING_MD) << "Speed"
		<< setw(STYLES::PADDING_LG) << getSpeed()
		<< " (" << UNITS::SPEED << ")"
		<< endl
		// Gamma
		<< setw(STYLES::PADDING_XSM) << ""
		<< setw(STYLES::PADDING_MD) << "Gamma"
		<< setw(STYLES::PADDING_LG) << getGamma()
		<< " (" << UNITS::SCALAR << ")"
		<< endl
		// Energy
		<< setw(STYLES::PADDING_XSM) << ""
		<< setw(STYLES::PADDING_MD) << "Energy"
		<< setw(STYLES::PADDING_LG) << CONVERT::EnergySItoGeV(getEnergy())
		<< " (" << UNITS::ENERGY << ")"
		<< endl
		// // Mass
		<< setw(STYLES::PADDING_XSM) << ""
		<< setw(STYLES::PADDING_MD) << "Mass"
		<< setw(STYLES::PADDING_LG) << CONVERT::MassSItoGeV(mass)
		<< " (" << UNITS::MASS << ")"
		<< endl
		// Charge
		<< setw(STYLES::PADDING_XSM) << ""
		<< setw(STYLES::PADDING_MD) << "Charge"
		<< setw(STYLES::PADDING_LG) << getCharge()
		<< " (" << UNITS::CHARGE << ")"
		<< endl
		// // Forces
		// << setw(STYLES::PADDING_XSM) << ""
		// << setw(STYLES::PADDING_MD) << "Forces"
		// << setw(STYLES::PADDING_LG) << getForces()
		// << " (" << UNITS::FORCE << ")"
		// << endl
		// // Element
		// << setw(STYLES::PADDING_XSM) << ""
		// << setw(STYLES::PADDING_MD) << "Element adr."
		// << setw(STYLES::PADDING_LG) << element_ptr
		<< endl;
	return stream.str();
}

/****************************************************************
 * Physics engine
 ****************************************************************/

void Particle::step(double dt, bool methodChapi) {
	// Do nothing if dt is null
	if (abs(dt) < GLOBALS::DELTA_DIV0) { return; }

	// Integrate the movement equations
	double const lambda(1 / (getGamma() * getMass()));

	// A particle can live freely without an Element so no return of EXCEPTIONS::NULLPTR in the other case
	// In that case you have to do a Particle::exertLorentzForce by yourself
	if (element_ptr != nullptr) {
		exertLorentzForce(element_ptr->getField(pos, methodChapi), dt);
	}

	momentum += getMass() * dt * lambda * getForces();
	pos += dt * getSpeed();
	forces.setNull();
}

void Particle::exertForce(Vector3D const& force) { forces += force; }

void Particle::exertLorentzForce(Vector3D const& B, double dt) {
	// Do nothing if dt is null or B is null (for example in Straight elements)
	if (dt < GLOBALS::DELTA_DIV0 or B == Vector3D(0, 0, 0)) { return; }

	// Apply Lorentz force
	Vector3D F(getSpeed());
	F ^= B;
	F *= getCharge();

	// Correct force term due to Euler integration
	// Angle of correction
	double alpha(asin(dt * F.norm() / (2 * getGamma() * getMoment().norm())));
	F.rotate(getSpeed() ^ F, alpha);

	// Apply the force
	exertForce(F);
}

/****************************************************************
 * Operator overloading
 ****************************************************************/

ostream& operator << (ostream& stream, Particle const& p) {
	return stream << p.to_string();
}

/****************************************************************
 * Drawing
 ****************************************************************/

void Particle::draw(Renderer * engine_ptr) const {
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

void Proton::draw(Renderer * engine_ptr) const {
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

void AntiProton::draw(Renderer * engine_ptr) const {
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

void Electron::draw(Renderer * engine_ptr) const {
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
