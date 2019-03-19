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

	Particle(Vector3D const& pos, Vector3D const& speed, double const& mass, double const& charge = 0, bool const& GeV = true);

	// speed is copied in order to normalize it
	Particle(Vector3D const& pos, double const& energy, Vector3D speed, double const& mass, double const& charge = 0, bool const& GeV = true);

	// Getters

		// SI units
	double getEnergy() const;
	double getCharge() const;
	double getMass() const;
	double getGamma() const;

	Vector3D getSpeed() const;
	Vector3D getForces() const;
	Vector3D getMoment() const;
	Vector3D getPos() const;

		// GeV units
	double getMassGeV() const;
	double getEnergyGeV() const;


	// Methods
	std::string to_string() const;
	void step(double const& dt = GLOBALS::DT);
	void exertForce(Vector3D const& force);
	void exertMagnetForce(Vector3D const& B, double const& dt = GLOBALS::DT);


private:
	Vector3D pos;
	Vector3D momentum;	// m * kg / s (GeV / c)
	Vector3D forces;
	double energy;		// J (GeV)
	double mass;		// kg (GeV / c²)
	double const charge;
};

/**
 * Operator overloading
 */

std::ostream& operator << (std::ostream& stream, Particle const& p);
