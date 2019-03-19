#include "src/include/Particle.h"

using namespace std;

/****************************************************************
 * Constructor
 ****************************************************************/

Particle::Particle(Vector3D const& pos, Vector3D const& speed, double const& mass, double const& charge)
: pos(pos), momentum(mass * speed), mass(mass),
  charge(charge), forces(Vector3D())
{}

Particle::Particle(Vector3D const& pos, double const& energy, Vector3D speed, double const& mass, double const& charge)
: pos(pos), momentum(mass * CONSTANTS::C * sqrt(1 - pow( mass / energy, 2)) * ~speed),
  mass(mass), charge(charge), forces(Vector3D())
{}

/****************************************************************
 * Getters
 ****************************************************************/

double Particle::getEnergy() const {
	return getGamma() * getMass();
}

double Particle::getGamma() const {
	return 1 / sqrt(1 - pow(getSpeed().norm() / CONSTANTS::C, 2));
}

double Particle::getMass() const { return mass; }
double Particle::getMassSI() const { return mass * 1e9 * CONSTANTS::E / pow(CONSTANTS::C, 2); }

double Particle::getCharge() const { return charge * CONSTANTS::E; }
Vector3D Particle::getSpeed() const { return getMoment() / getMass(); }
Vector3D Particle::getSpeedSI() const { return getMomentSI() / getMassSI(); }
Vector3D Particle::getForces() const { return forces; }
Vector3D Particle::getMoment() const { return momentum; }
Vector3D Particle::getMomentSI() const {
	return getMoment() * 1e9 * CONSTANTS::E / CONSTANTS::C;
}
Vector3D Particle::getPos() const { return pos; }


/****************************************************************
 * Methods
 ****************************************************************/

string Particle::to_string() const {
	stringstream stream;
	stream << scientific << setprecision(6);
	stream 	<< "Position: "s << getPos() << " ("s + UNITS::DISTANCE << ")\n"s
			<< "Speed:    "s << getSpeed() << "\n"s
			<< "Gamma:    "s << getGamma() << "\n"s
			<< "Energy:   "s << getEnergy() << " (" << UNITS::ENERGY << ")\n"s
			<< "Mass:     "s << getMass() << " ("s << UNITS::MASS << ")\n"s
			<< "Charge:   "s << getCharge() << " ("s << UNITS::CHARGE << ")\n"s
			<< "Forces:   "s << getForces() << " ("s << UNITS::FORCE << ")\n"s;
	return stream.str();
}

/****************************************************************
 * Physics engine
 ****************************************************************/

void Particle::step(double const& dt) {
	double const lambda(1/(getGamma() * getMassSI()));
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
	double alpha(asin(dt * F.norm() / (2 * getGamma() * getMomentSI().norm())));
	F.rotate(getSpeed() ^ F, alpha);

	exertForce(F);
}


/****************************************************************
 * Operator overloading
 ****************************************************************/

ostream& operator << (ostream& stream, Particle const& p) {
	return stream << p.to_string();
}
