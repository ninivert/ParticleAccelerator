#include "src/include/Particle.h"

using namespace std;

/****************************************************************
 * Constructor
 ****************************************************************/

// Constructor for init with velocity

Particle::Particle(Vector3D const& pos, Vector3D const& speed, double const& _mass, int const& charge, bool const& unitGeV)
: pos(pos), mass(_mass), charge(charge), forces(Vector3D())
{
	if (unitGeV) mass = CONVERT::MassGeVtoSI(mass);
	momentum = speed * mass;
}

// Constructor for init with velocity and energy

Particle::Particle(Vector3D const& pos, double const& energy, Vector3D speed, double const& _mass, int const& charge, bool const& unitGeV)
: pos(pos), mass(_mass), charge(charge), forces(Vector3D())
{
	double factor(0);

	if (unitGeV) {
		// Order matters here: we first compute m²/E², then convert the mass
		factor = mass * mass / (energy * energy);
		mass = CONVERT::MassGeVtoSI(mass);
	} else {
		factor = CONSTANTS::C * CONSTANTS::C * mass * energy;
		factor *= factor;
	}

	momentum = ~speed * mass * CONSTANTS::C * sqrt(1 - factor);
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

int Particle::getChargeNumber() const { return charge; }
double Particle::getCharge() const { return getChargeNumber() * CONSTANTS::EV; }
double Particle::getMass() const { return mass; }

Vector3D Particle::getSpeed() const { return getMoment() / getMass(); }
Vector3D Particle::getForces() const { return forces; }
Vector3D Particle::getMoment() const { return momentum; }
Vector3D Particle::getPos() const { return pos; }

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
		<< setw(STYLES::PADDING_MD) << "Position"s
		<< setw(STYLES::PADDING_LG) << getPos()
		<< " ("s + UNITS::DISTANCE << ")"s
		<< endl
		// Speed
		<< setw(STYLES::PADDING_SM) << ""
		<< setw(STYLES::PADDING_MD) << "Speed"s
		<< setw(STYLES::PADDING_LG) << getSpeed()
		<< " ("s + UNITS::SPEED << ")"s
		<< endl
		// Gamma
		<< setw(STYLES::PADDING_SM) << ""
		<< setw(STYLES::PADDING_MD) << "Gamma"s
		<< setw(STYLES::PADDING_LG) << getGamma()
		<< " ("s + UNITS::SCALAR << ")"s
		<< endl
		// Energy
		<< setw(STYLES::PADDING_SM) << ""
		<< setw(STYLES::PADDING_MD) << "Energy"s
		<< setw(STYLES::PADDING_LG) << CONVERT::EnergySItoGeV(getEnergy())
		<< " (" << UNITS::ENERGY << ")"s
		<< endl
		// Mass
		<< setw(STYLES::PADDING_SM) << ""
		<< setw(STYLES::PADDING_MD) << "Mass"s
		<< setw(STYLES::PADDING_LG) << CONVERT::MassSItoGeV(mass)
		<< " ("s << UNITS::MASS << ")"s
		<< endl
		// Charge
		<< setw(STYLES::PADDING_SM) << ""
		<< setw(STYLES::PADDING_MD) << "Charge"s
		<< setw(STYLES::PADDING_LG) << getCharge()
		<< " ("s << UNITS::CHARGE << ")"s
		<< endl
		// Forces
		<< setw(STYLES::PADDING_SM) << ""
		<< setw(STYLES::PADDING_MD) << "Forces"s
		<< setw(STYLES::PADDING_LG) << getForces()
		<< " ("s << UNITS::FORCE << ")"s
		<< endl;
	return stream.str();
}

/****************************************************************
 * Physics engine
 ****************************************************************/

void Particle::step(double const& dt) {
	// Do nothing if dt is null
	if (dt == 0) { return; }

	// Integrate the movement equations
	double const lambda(1 / (getGamma() * getMass()));
	momentum += getMass() * dt * lambda * getForces();
	pos += dt * getSpeed();
	forces.setNull();
}

void Particle::exertForce(Vector3D const& force) { forces += force; }

void Particle::exertLorentzForce(Vector3D const& B, double const& dt) {
	// Do nothing if dt is null
	if (dt == 0) { return; }

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
