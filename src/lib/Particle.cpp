#include "src/include/Particle.h"

using namespace std;

/****************************************************************
 * Constructor
 ****************************************************************/

// Constructor for init with velocity

Particle::Particle(Vector3D const& pos, Vector3D const& speed, double const& _mass, int const& charge, bool const& unitGeV)
: pos(pos), mass(_mass), charge(charge), forces(Vector3D()), element(nullptr)
{
	if (unitGeV) mass = CONVERT::MassGeVtoSI(mass);
	momentum = speed * mass;
}

// Constructor for init with velocity and energy

Particle::Particle(Vector3D const& pos, double const& energy, Vector3D speed, double const& _mass, int const& charge, bool const& unitGeV)
: pos(pos), mass(_mass), charge(charge), forces(Vector3D()), element(nullptr)
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

/****************************************************************
 * Destructor
 ****************************************************************/

Particle::~Particle() { element = nullptr; }

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

int Particle::getChargeNumber() const { return charge; }
double Particle::getCharge() const { return getChargeNumber() * CONSTANTS::EV; }
double Particle::getMass() const { return mass; }

Vector3D Particle::getSpeed() const { return getMoment() / getMass(); }
Vector3D Particle::getForces() const { return forces; }
Vector3D Particle::getMoment() const { return momentum; }
Vector3D Particle::getPos() const { return pos; }

Element const& Particle::getElement() const {
	if (element != nullptr) {
		return *element;
	} else {
		ERROR(EXCEPTIONS::NULLPTR);
	}
}

/****************************************************************
 * Setters
 ****************************************************************/

void Particle::setElement(Element * _element) {
	// Protection against empty pointers
	if (_element != nullptr) {
		element = _element;
	} else {
		ERROR(EXCEPTIONS::NULLPTR);
	}
}

/****************************************************************
 * Methods
 ****************************************************************/

string Particle::to_string() const {
	stringstream stream;
	stream << setprecision(STYLES::PRECISION);
	stream << left;
	stream
		// Position
		<< setw(STYLES::PADDING_SM) << ""
		<< setw(STYLES::PADDING_MD) << "Position"
		<< setw(STYLES::PADDING_LG) << getPos()
		<< " (" << UNITS::DISTANCE << ")"
		<< endl
		// Speed
		<< setw(STYLES::PADDING_SM) << ""
		<< setw(STYLES::PADDING_MD) << "Speed"
		<< setw(STYLES::PADDING_LG) << getSpeed()
		<< " (" << UNITS::SPEED << ")"
		<< endl
		// Gamma
		<< setw(STYLES::PADDING_SM) << ""
		<< setw(STYLES::PADDING_MD) << "Gamma"
		<< setw(STYLES::PADDING_LG) << getGamma()
		<< " (" << UNITS::SCALAR << ")"
		<< endl
		// Energy
		<< setw(STYLES::PADDING_SM) << ""
		<< setw(STYLES::PADDING_MD) << "Energy"
		<< setw(STYLES::PADDING_LG) << CONVERT::EnergySItoGeV(getEnergy())
		<< " (" << UNITS::ENERGY << ")"
		<< endl
		// Mass
		<< setw(STYLES::PADDING_SM) << ""
		<< setw(STYLES::PADDING_MD) << "Mass"
		<< setw(STYLES::PADDING_LG) << CONVERT::MassSItoGeV(mass)
		<< " (" << UNITS::MASS << ")"
		<< endl
		// Charge
		<< setw(STYLES::PADDING_SM) << ""
		<< setw(STYLES::PADDING_MD) << "Charge"
		<< setw(STYLES::PADDING_LG) << getCharge()
		<< " (" << UNITS::CHARGE << ")"
		<< endl
		// Forces
		<< setw(STYLES::PADDING_SM) << ""
		<< setw(STYLES::PADDING_MD) << "Forces"
		<< setw(STYLES::PADDING_LG) << getForces()
		<< " (" << UNITS::FORCE << ")"
		// << endl
		// // Element
		// << setw(STYLES::PADDING_SM) << ""
		// << setw(STYLES::PADDING_MD) << "Element adr."
		// << setw(STYLES::PADDING_LG) << element
		<< endl;
	return stream.str();
}

/****************************************************************
 * Physics engine
 ****************************************************************/

void Particle::step(double const& dt) {
	// Do nothing if dt is null
	if (abs(dt) < GLOBALS::DELTA) { return; }

	// Integrate the movement equations
	double const lambda(1 / (getGamma() * getMass()));

	// A particle can live freely without an Element so no return of EXCEPTIONS::NULLPTR in the other case
	// In that case you have to do a Particle::exertLorentzForce by yourself
	if (element != nullptr) {
		exertLorentzForce(element->getField(pos), dt);
	}

	momentum += getMass() * dt * lambda * getForces();
	pos += dt * getSpeed();
	forces.setNull();
}

void Particle::exertForce(Vector3D const& force) { forces += force; }

void Particle::exertLorentzForce(Vector3D const& B, double const& dt) {
	// Do nothing if dt is null or B is null (for example in Straight elements)
	if (dt < GLOBALS::DELTA or B == Vector3D(0, 0, 0)) { return; }

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
