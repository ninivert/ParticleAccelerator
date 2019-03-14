#pragma once

#include <string>
#include <sstream>
#include <iomanip>
#include <cmath>
#include "src/globals.h"
#include "src/include/Vector3D.h"

/**
 * Particle Class
 */

class Particle {
public:
	// Constructor

	Particle(Vector3D const& pos, Vector3D const& speed, double mass, double charge = 0);

	// Getters

	double getEnergyGeV() const;
	double getCharge() const;
	double getMass() const;
	double getGamma() const;
	Vector3D getSpeed() const;
	Vector3D getForces() const;
	Vector3D getMoment() const;
	Vector3D getPos() const;

	// Methods
	std::string to_string() const;
	void step(double dt = GLOBALS::DT);
	void exertForce(Vector3D const& force);
	void exertMagnetForce(Vector3D const& B, double dt = GLOBALS::DT);


private:
	Vector3D pos;
	Vector3D momentum;	// GeV / c
	Vector3D forces;
	double energy;		// GeV
	double mass;		// GeV / c²
	double const charge;
};

/**
 * Operator overloading
 */

std::ostream& operator << (std::ostream& stream, Particle const& p);
