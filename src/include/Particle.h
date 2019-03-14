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

	// Particle(Vector3D const& pos, Vector3D const& speed, double mass, double gamma, double charge = 0);

	Particle(Vector3D const& pos, double const& energy, double mass, double charge = 0);

	// Getters

	double getEnergy() const;

	double getCharge() const;
	double getMass() const;
	double getGamma() const;
	Vector3D getSpeed();
	Vector3D getForces() const;


	// Methods

	std::string to_string() const;
	void step(double dt = GLOBALS::DT);
	void exertForce(Vector3D const& force);
	void addMagnetForce(Vector3D const& B, double dt = GLOBALS::DT);


private:
	Vector3D pos;
	Vector3D speed;	// vector direction
	Vector3D forces;
	double energy;
	double mass;	// GeV
	double charge;
};

/**
 * Operator overloading
 */

std::ostream& operator << (std::ostream& stream, Particle const& p);
