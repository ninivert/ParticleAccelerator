#include "src/include/Particle.h"

using namespace std;

/****************************************************************
 * Constructor
 ****************************************************************/

Particle::Particle(Vector3D pos, Vector3D speed, double mass, double gamma, double charge)
: pos(pos), speed(speed), mass(mass), gamma(gamma), charge(charge), forces(Vector3D()) {
	momentum = gamma * mass * speed;
}

/****************************************************************
 * Getters
 ****************************************************************/

double Particle::getEnergy() const {
	return gamma * mass * pow(CONSTANTS::C, 2);
}

/****************************************************************
 * Methods
 ****************************************************************/

string Particle::to_string() const {
	string str("");
	str += "Position: "s + pos.to_string() + " ("s + UNITS::DISTANCE + ")\n"s;
	str += "Speed:    "s + speed.to_string() + "\n"s;
	str += "Momentum: "s + momentum.to_string() + " ("s + UNITS::MOMENTUM + ")\n"s;
	str += "Forces:   "s + forces.to_string() + " ("s + UNITS::FORCE + ")\n"s;
	str += "Mass:     "s + std::to_string(mass) + " ("s + UNITS::MASS + ")\n"s;
	str += "Charge:   "s + std::to_string(charge) + " ("s + UNITS::CHARGE + ")\n"s;
	str += "Energy:   "s + std::to_string(getEnergy()) + " (" + UNITS::ENERGY + ")\n"s;
	str += "Gamma:    "s + std::to_string(gamma) + "\n"s;
	return str;
}

/****************************************************************
 * Physics engine
 ****************************************************************/

void Particle::step(double dt) {
	double const lambda(1/(gamma * mass));
	speed += dt * lambda * forces;
	momentum = gamma * mass * speed;
	pos += speed;
	forces.setNull();
}

void Particle::exertForce(Vector3D force) { forces += force; }

/****************************************************************
 * Operator overloading
 ****************************************************************/

ostream& operator << (ostream& stream, Particle const& p) {
	return stream << p.to_string();
}