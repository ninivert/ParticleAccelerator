#include "src/include/Particle.h"

using namespace std;

/****************************************************************
 * Constructor
 ****************************************************************/

// Particle::Particle(Vector3D const& pos, Vector3D const& speed, double mass, double gamma, double charge)
// : pos(pos), speed(speed), mass(mass),
//   gamma(gamma), charge(charge), forces(Vector3D())
// {}

Particle::Particle(Vector3D const& pos, double const& energy, double mass, double charge)
: pos(pos), energy(energy), mass(mass),
  charge(charge), forces(Vector3D()), speed(Vector3D())
{}
/****************************************************************
 * Getters
 ****************************************************************/

double Particle::getEnergy() const { return energy; }

double Particle::getGamma() const {
	return  getEnergy() / (getMass() * pow(CONSTANTS::C, 2));
}

Vector3D Particle::getSpeed() {
	return ~speed * pow(CONSTANTS::C, 2) * sqrt(1 - 1 / pow(getGamma(), 2));
}
Vector3D Particle::getForces() const { return forces; }
double Particle::getCharge() const { return charge; }
double Particle::getMass() const { return mass; }



/****************************************************************
 * Methods
 ****************************************************************/

string Particle::to_string() const {
	string str("");
	str += "Position: "s + pos.to_string() + " ("s + UNITS::DISTANCE + ")\n"s;
	str += "Speed:    "s + getSpeed().to_string() + "\n"s;
	str += "Gamma:    "s + std::to_string(getGamma()) + "\n"s;
	str += "Energy:   "s + std::to_string(getEnergy()) + " (" + UNITS::ENERGY + ")\n"s;
	str += "Mass:     "s + std::to_string(getMass()) + " ("s + UNITS::MASS + ")\n"s;
	str += "Charge:   "s + std::to_string(getCharge()) + " ("s + UNITS::CHARGE + ")\n"s;
	str += "Forces:   "s + forces.to_string() + " ("s + UNITS::FORCE + ")\n"s;
	return str;
}

/****************************************************************
 * Physics engine
 ****************************************************************/

void Particle::step(double dt) {
	double const lambda(1/(getGamma() * getMass()));
	speed += dt * lambda * getForces();
	pos += dt * getSpeed();
	forces.setNull();
}

void Particle::exertForce(Vector3D const& force) { forces += force; }

void Particle::addMagnetForce(Vector3D const& B, double dt) {
	if (abs(dt) < GLOBALS::EPSILON) { return; }
	Vector3D F(getSpeed());
	F ^= B;
	F *= getCharge();
	double alpha(asin(dt * F.norm() / (2 * getGamma() * getMass() * getSpeed().norm())));
	F.rotate(getSpeed() ^ F, alpha);

	exertForce(F);
}


/****************************************************************
 * Operator overloading
 ****************************************************************/

ostream& operator << (ostream& stream, Particle const& p) {
	return stream << p.to_string();
}
