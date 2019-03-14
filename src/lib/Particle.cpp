#include "src/include/Particle.h"

using namespace std;

/****************************************************************
 * Constructor
 ****************************************************************/

Particle::Particle(Vector3D const& pos, Vector3D const& speed, double mass, double charge)
: pos(pos), momentum(speed * mass), mass(mass),
  charge(charge), forces(Vector3D())
{}

/****************************************************************
 * Getters
 ****************************************************************/

double Particle::getEnergyGeV() const {
	return getGamma() * getMass();
}

double Particle::getGamma() const {
	return 1 / sqrt(1 - pow(getSpeed().norm() / CONSTANTS::C, 2));
}

double Particle::getMass() const { return mass; }
double Particle::getCharge() const { return charge * CONSTANTS::E; }
Vector3D Particle::getSpeed() const { return momentum / getMass(); }
Vector3D Particle::getForces() const { return forces; }
Vector3D Particle::getMoment() const { return momentum; }
Vector3D Particle::getPos() const { return pos; }


/****************************************************************
 * Methods
 ****************************************************************/

string Particle::to_string() const {
	string str("Particule : \n");
	str += "\tPosition: "s + getPos().to_string() + " ("s + UNITS::DISTANCE + ")\n"s;
	str += "\tSpeed:    "s + getSpeed().to_string() + "\n"s;
	str += "\tGamma:    "s + std::to_string(getGamma()) + "\n"s;
	str += "\tEnergy:   "s + std::to_string(getEnergyGeV()) + " (" + UNITS::ENERGY + ")\n"s;
	str += "\tMass:     "s + std::to_string(getMass()) + " ("s + UNITS::MASS + ")\n"s;
	str += "\tCharge:   "s + std::to_string(getCharge()) + " ("s + UNITS::CHARGE + ")\n"s;
	str += "\tForces:   "s + getForces().to_string() + " ("s + UNITS::FORCE + ")\n"s;
	return str;
}

/****************************************************************
 * Physics engine
 ****************************************************************/

void Particle::step(double dt) {
	double const lambda(1/(getGamma() * getMass()));
	momentum += getMass() * dt * lambda * getForces();
	pos += dt * getSpeed();
	forces.setNull();
}

void Particle::exertForce(Vector3D const& force) { forces += force; }

void Particle::exertMagnetForce(Vector3D const& B, double dt) {
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
