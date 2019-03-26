#ifndef PARTICLE_H
#define PARTICLE_H

#pragma once

#include <cmath>
#include <iomanip>
#include <string>
#include <sstream>

#include "src/include/Element.h"
#include "src/include/Vector3D.h"
#include "src/globals.h"
#include "src/converter.h"

// Resolve ciruclar header definition
class Element;

/**
 * The Particle Class represents a particle evolving in the 3D carthesian space
 */

class Particle {
public:

	/****************************************************************
	* Constructors
	****************************************************************/

	/**
	 * Constructor for initialisation with velocity
	 *
	 * - `Vector3D pos`: initial position of the particle
	 * - `Vector3D speed`: initial speed of the particle (if applicable)
	 * - `double mass`: mass of the particle
	 * - `int charge = 1`: charge of the particle in multiples of the elementary charge (i.e. multiples of 1 eV, charge of the electron)
	 * - `bool unitGeV = true`: specify the units of the scalars given to the constructor
	 *
	 * Per default, units are expected in GeV. To specify units in the SI system, add `false` at the end of the argument list.
	 */

	Particle(Vector3D const& pos, Vector3D const& speed, double const& mass, int const& charge = 1, bool const& unitGeV = true);

	/**
	 * Constructor for initialisation with energy and direction vector velocity
	 *
	 * - `Vector3D pos`: initial position of the particle
	 * - `Vector3D speed`: initial speed of the particle (if applicable)
	 * - `double energy`: intial energy of the particle (if applicable)
	 * - `double mass`: mass of the particle
	 * - `int charge = 1`: charge of the particle in multiples of the elementary charge (i.e. multiples of 1 eV, charge of the electron)
	 * - `bool unitGeV = true`: specify the units of the scalars given to the constructor
	 *
	 * Per default, units are expected in GeV. To specify units in the SI system, add `false` at the end of the argument list.
	 */

	Particle(Vector3D const& pos, double const& energy, Vector3D speed, double const& mass, int const& charge = 1, bool const& unitGeV = true);

	/****************************************************************
	 * Destructor
	 ****************************************************************/

	/**
	 * Destructor to set element to nullptr and don't delete an instance of Element
	 */

	~Particle();

	/****************************************************************
	 * Getters (SI units)
	 ****************************************************************/

	/**
	 * Returns the energy in SI
	 */

	double getEnergy() const;

	/**
	 * Returns the factor gamma (1 / sqrt(1 - v^2 / c^2))
	 */

	double getGamma() const;

	/**
	 * Returns the attribute mass in SI [kg]
	 */

	double getMass() const;

	/**
	 * Returns the total charge of the particle / macroparticle
	 */

	double getCharge() const;

	/**
	 * Returns the attribute number of elementary charge of the particle / macroparticle
	 */

	int getChargeNumber() const;

	/**
	 * Returns the velocity of the particle in [m/s]
	 */

	Vector3D getSpeed() const;

	/**
	 * Returns the attribute forces which are the forces that are currently moving the particle
	 */

	Vector3D getForces() const;

	/**
	 * Returns the attribute Momentum in SI [m * kg / s]
	 */

	Vector3D getMoment() const;

	/**
	 * Returns the attribute position according to the carthesian space and the origin in (0, 0, 0)
	 */

	Vector3D getPos() const;

	/****************************************************************
	 * Setters
	 ****************************************************************/

	/**
	 * Make the particle point a given element pointer
	 */

	void setElement(Element * elmt);

	/****************************************************************
	 * Methods
	 ****************************************************************/

	/**
	 * Returns a string representation of the particle
	 */

	std::string to_string() const;

	/****************************************************************
	 * Physics engine
	 ****************************************************************/

	/**
	 * Integrates the movement equations over a time step `dt`, which defaults to `GLOBALS::DT(1e-11)`.
	 *
	 * If `dt` is null (aka inferior to GLOBALS::DELTA), then this doesn't do anything
	 */

	void step(double const& dt = GLOBALS::DT);

	/**
	 * Exerts a force onto a particle until the next `step` is called.
	 */

	void exertForce(Vector3D const& force);

	/**
	 * Exerts the Lorentz force on a particle traversing a magnetic field given by the `B` vector over a timestep `dt` (defaults to `GLOBALS::DT(1e-11)`).
	 *
	 * If `dt` is null (aka inferior to GLOBALS::DELTA), then this doesn't do anything
	 */

	void exertLorentzForce(Vector3D const& B, double const& dt = GLOBALS::DT);

private:

	// Attributes

	Vector3D pos;
	Vector3D momentum;	// stored in [m * kg / s]	(GeV / c)
	Vector3D forces;
	double mass;		// stored in [kg]			(GeV / c²)
	int const charge;	// Physically, only whole multiples of elementary charges make sense
	Element * element;
};

/****************************************************************
 * Cout overloading
 ****************************************************************/

/**
 * Streams the `Particle::to_string()` representation to a given stream
 */

std::ostream& operator << (std::ostream& stream, Particle const& p);

#endif
