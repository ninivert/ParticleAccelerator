#include "src/include/Particle.h"

using namespace std;

/****************************************************************
 * Constructor
 ****************************************************************/

Particle::Particle(Vector3D const& pos, Vector3D const& speed, double const& _mass, double const& charge, bool const& in_GeV)
: pos(pos), mass(_mass), charge(charge), forces(Vector3D())
{
	if (in_GeV) {
		mass = CONVERT::MassGeVtoSI(mass);
	}
	momentum = speed * mass;
}

Particle::Particle(Vector3D const& pos, double const& energy, Vector3D speed, double const& _mass, double const& charge, bool const& in_GeV)
: pos(pos), mass(_mass), charge(charge), forces(Vector3D())
{
	double factor (0);
	if (in_GeV) {
		factor = pow(mass / energy, 2);		// WARNING order
		mass = CONVERT::MassGeVtoSI(mass);
	} else {
		factor = pow(pow(CONSTANTS::C, 2) * mass / energy, 2);
	}

	momentum = ~speed * mass * CONSTANTS::C * sqrt(1 - factor);
}

/****************************************************************
 * Getters
 ****************************************************************/

double Particle::getEnergy() const {
	return getGamma() * getMass() * pow(CONSTANTS::C, 2);
}

double Particle::getGamma() const {
	return 1 / sqrt(1 - pow(getSpeed().norm() / CONSTANTS::C, 2));
}

double Particle::getMass() const { return mass; }
double Particle::getCharge() const { return charge * CONSTANTS::E; }

Vector3D Particle::getSpeed() const { return getMoment() / getMass(); }
Vector3D Particle::getForces() const { return forces; }
Vector3D Particle::getMoment() const { return momentum; }
Vector3D Particle::getPos() const { return pos; }

/****************************************************************
 * Methods
 ****************************************************************/

string Particle::to_string() const {
	stringstream stream;
	stream << setprecision(6);
	stream 	<< "\tPosition :\t"s << getPos() << " ("s + UNITS::DISTANCE << ")\n"s
			<< "\tSpeed :\t\t"s << getSpeed() << "\n"s
			<< "\tGamma :\t\t"s << getGamma() << "\n"s
			<< "\tEnergy :\t"s << CONVERT::EnergySItoGeV(getEnergy()) << " (" << UNITS::ENERGY << ")\n"s
			<< "\tMass :\t\t"s << CONVERT::MassSItoGeV(mass) << " ("s << UNITS::MASS << ")\n"s
			<< "\tCharge :\t"s << getCharge() << " ("s << UNITS::CHARGE << ")\n"s
			<< "\tForces :\t"s << getForces() << " ("s << UNITS::FORCE << ")\n\n"s;
	return stream.str();
}

/****************************************************************
 * Physics engine
 ****************************************************************/

void Particle::step(double const& dt) {
	double const lambda(1/(getGamma() * getMass()));
	momentum += getMass() * dt * lambda * getForces();
	pos += dt * getSpeed();
	// forces.setNull();
}

void Particle::exertForce(Vector3D const& force) { forces += force; }

void Particle::exertMagnetForce(Vector3D const& B, double const& dt) {
	if (abs(dt) < GLOBALS::DT) { return; }
	Vector3D F(getSpeed());
	F ^= B;
	F *= getCharge();

	double alpha(asin(dt * F.norm() / (2 * getGamma() * getMoment().norm())));
	F.rotate(getSpeed() ^ F, alpha);
	exertForce(F);
}

/****************************************************************
 * Operator overloading
 ****************************************************************/

ostream& operator << (ostream& stream, Particle const& p) {
	return stream << p.to_string();
}
