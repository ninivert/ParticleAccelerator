#ifndef PARTICLE_H
#define PARTICLE_H

#pragma once

#include <cmath>
#include <iomanip>
#include <string>
#include <sstream>

#include "src/include/Converter.h"
#include "src/include/Vector3D.h"
#include "src/globals.h"

/**
 * Particle Class
 */

class Particle {
public:
	// Constructor

	// Constructor for init with velocity
	Particle(Vector3D const& pos, Vector3D const& speed, double const& mass, int const& charge = 1, bool const& unitGeV = true);
	// Constructor for init with velocity and energy
	Particle(Vector3D const& pos, double const& energy, Vector3D speed, double const& mass, int const& charge = 1, bool const& unitGeV = true);

	// Getters (SI units)

	double getEnergy() const;
	double getGamma() const;
	double getMass() const;
	double getCharge() const;
	int getChargeNumber() const;

	Vector3D getSpeed() const;
	Vector3D getForces() const;
	Vector3D getMoment() const;
	Vector3D getPos() const;

	// Methods

	std::string to_string() const;

	// Physics engine

	void step(double const& dt = GLOBALS::DT);
	void exertForce(Vector3D const& force);
	void exertLorentzForce(Vector3D const& B, double const& dt = GLOBALS::DT);

private:
	Vector3D pos;
	Vector3D momentum;	// m * kg / s	(GeV / c)
	Vector3D forces;
	double mass;		// kg			(GeV / c²)
	int const charge;	// Physically, only whole multiples of elementary charges make sense
};

/**
 * Operator overloading
 */

std::ostream& operator << (std::ostream& stream, Particle const& p);

#endif
