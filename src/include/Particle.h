#pragma once

#include <string>
#include <cmath>
#include "src/globals.h"
#include "src/include/Vector3D.h"

/**
 * Particle Class
 */

class Particle {
public:
	// Constructor

	Particle(Vector3D pos, Vector3D speed, double mass, double gamma, double charge = 0);

	// Getters

	double getEnergy() const;

	// Methods 

	std::string to_string() const;
	void step(double dt = GLOBALS::DT);
	void exertForce(Vector3D force);

private:
	Vector3D pos;
	Vector3D speed;
	Vector3D momentum;
	Vector3D forces;
	double mass;
	double charge;
	double gamma;
};

/**
 * Operator overloading
 */

std::ostream& operator << (std::ostream& stream, Particle const& p);