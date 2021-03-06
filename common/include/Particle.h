#ifndef PARTICLE_H
#define PARTICLE_H

#pragma once

#include <cmath>
#include <iomanip>
#include <memory>
#include <string>
#include <sstream>

// Forward declaration
class Vector3D;
class Element;
class Drawable;
class Renderer;

#include "globals.h"
#include "exceptions.h"

/**
 * The Particle Class represents a particle evolving in the 3D carthesian space
 */

class Particle : public Drawable {
public:

	/****************************************************************
	 * Constructors
	 ****************************************************************/

	/**
	 * Constructor for initialisation with velocity
	 *
	 * - `Vector3D pos`: initial position of the particle
	 * - `Vector3D speed`: initial speed of the particle
	 * - `double mass`: mass of the particle
	 * - `int charge = 1`: charge of the particle in multiples of the elementary charge (i.e. multiples of 1 eV, charge of the electron)
	 * - `bool unitGeV = true`: specify the units of the scalars given to the constructor
	 * - `Renderer * engine_ptr` : initialization of the `Renderer` if given, nullptr by default
	 *
	 * By default, units are expected in GeV. To specify units in the SI system, add `false` at the end of the argument list.
	 *
	 * The constructor is explicit to prevent accidental type casting.
	 */

	// explicit Particle(Vector3D const& pos, Vector3D const& speed, double mass, int charge = 1, bool unitGeV = true, Renderer * engine_ptr = nullptr);

	/**
	 * Constructor for initialisation with energy and direction vector velocity
	 *
	 * - `Vector3D pos`: initial position of the particle
	 * - `Vector3D speed`: initial speed of the particle
	 * - `double energy`: intial energy of the particle
	 * - `double mass`: mass of the particle
	 * - `int charge = 1`: charge of the particle in multiples of the elementary charge (i.e. multiples of 1 eV, charge of the electron)
	 * - `bool unitGeV = true`: specify the units of the scalars given to the constructor
	 * - `Renderer * engine_ptr` : initialization of the `Renderer` if given, nullptr by default
	 *
	 * By default, units are expected in GeV. To specify units in the SI system, add `false` at the end of the argument list.
	 *
	 * The constructor is explicit to prevent accidental type casting.
	 */

	explicit Particle(Vector3D const& pos, double energy, Vector3D speed, double mass, int charge = 1, bool unitGeV = true, Renderer * engine_ptr = nullptr);

	/****************************************************************
	 * Destructor
	 ****************************************************************/

	/**
	 * Destructor:
	 *
	 * - Set Particle::element to nullptr
	 * - Don't delete the Element !!
	 */

	virtual ~Particle() override;

	/****************************************************************
	 * Polymorphic copy for Accelerator
	 ****************************************************************/

	/**
	 * Returns a new unique_ptr constructed dynamically
	 *
	 * This new pointer contains a polymorphic copy of the current Particle.
	 *
	 * We are returning a pointer on Particule because in Accelerator we store them as unique_ptr<Element>
	 */

	virtual std::unique_ptr<Particle> copy() const;

	/**
	 * Returns a new unique_ptr constructed dynamically
	 *
	 * This new pointer contains a polymorphic copy with constructor arguments.
	 *
	 * We are returning a pointer on Particule because in Accelerator we store them as unique_ptr<Element>
	 */

	virtual std::unique_ptr<Particle> scaledCopy(Vector3D const& pos, double energy, Vector3D speed, double _mass, int charge, double lambda) const;

	/****************************************************************
	 * Getters (SI units)
	 ****************************************************************/

	/**
	 * Returns the energy in SI
	 */

	double getEnergy() const;

	/**
	 * Returns the factor gamma 1 / sqrt(1 - v² / c²)
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
	 * Returns the attribute number of elementary charge of the particle
	 */

	int getChargeNumber() const;

	/**
	 * Returns the velocity of the particle in [m/s]
	 */

	Vector3D getSpeed() const;

	/**
	 * Returns the sum of forces exerted on the Particle
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

	/**
	 * Returns a pointer (for polymorphism purposes) to the Element the Particle is in
	 *
	 * Used primarily in Accelerator::updateParticleElement()
	 *
	 * Return: pointer on a constant Element to prevent mistakes (and hoping not to transgress the principles of the OOP)
	 */

	Element const * getElementPtr() const;

	/****************************************************************
	 * Setters
	 ****************************************************************/

	/**
	 * Make the particle point a given element pointer
	 */

	void setElement(Element * element_ptr);

	/****************************************************************
	 * Methods
	 ****************************************************************/

	/**
	 * Returns a string representation of the particle
	 */

	std::string const to_string() const;

	/****************************************************************
	 * Physics engine
	 ****************************************************************/

	/**
	 * Integrates the movement equations over a time step `dt`, which defaults to `GLOBALS::DT(1e-11)`.
	 *
	 * We need the methodChapi for the getField (if it's a FODO element)
	 *
	 * If `dt` is null (aka inferior to GLOBALS::DELTA_DIV0), then this doesn't do anything
	 */

	void step(double dt = GLOBALS::DT, bool methodChapi = false);

	/**
	 * Exerts a force onto a particle until the next `step` is called.
	 */

	void exertForce(Vector3D const& force);

	/**
	 * Exerts the Lorentz force on a particle traversing a magnetic field given by the `B` vector over a timestep `dt` (defaults to `GLOBALS::DT(1e-11)`).
	 *
	 * If `dt` is null (aka inferior to GLOBALS::DELTA_DIV0), then this doesn't do anything
	 *
	 * If `B` is null (aka its components are all inferior to GLOBALS::DELTA_DIV0), then this doesn't do anything
	 * (prevent EXCEPTIONS::DIV_0 in `F.rotate()`
	 *
	 * 1. If B is null, then F ^ B is null
	 * 2. Then F.rotate(Vector3D(0, 0, 0), alpha) tries to normalize Vector3D(0, 0, 0) which will scream at you
	 */

	void exertLorentzForce(Vector3D const& B, double dt = GLOBALS::DT);

	/****************************************************************
	 * Rendering engine
	 ****************************************************************/

	/**
	 * Reroute the drawing call (double dispatching)
	 *
	 * - Use renderer in argument if given
	 * - Else use class renderer
	 * - Else throw EXCEPTIONS::NULLPTR
	 */

	virtual void draw(Renderer * engine_ptr = nullptr) const override;

private:

	/****************************************************************
	 * Attributes
	 ****************************************************************/

	/**
	 * Mass of the Particle (stored in [kg] (GeV / c²))
	 */

	double mass;

	/**
	 * Charge of the Particle
	 *
	 * Integer because physically, only whole multiples of elementary charges make sense
	 */

	int charge;

	/**
	 * Position of the Particle
	 */

	Vector3D pos;

	/**
	 * Momentum of the Particle (stored in [m * kg / s] (GeV / c))
	 */

	Vector3D momentum;

	/**
	 * Sum of forces exterted on the Particle
	 */

	Vector3D forces;

	/**
	 * Pointer on the Element the Particle is in
	 */

	Element * element_ptr;

};

/****************************************************************
 * Electrons and protons
 ****************************************************************/

/**
 * Stupid simple electron class
 */

class Electron : public Particle {
public:
	// explicit Electron(Vector3D const& pos, Vector3D const& speed, bool unitGeV = true, Renderer * engine_ptr = nullptr, double lambda = 1);
	explicit Electron(Vector3D const& pos, double energy, Vector3D speed, bool unitGeV = true, Renderer * engine_ptr = nullptr, double lambda = 1);
	virtual void draw(Renderer * engine_ptr = nullptr) const override;
	virtual std::unique_ptr<Particle> copy() const override;
	virtual std::unique_ptr<Particle> scaledCopy(Vector3D const& pos, double energy, Vector3D speed, double _mass, int charge, double lambda) const override;
};

/**
 * Stupid simple proton class
 */

class Proton : public Particle {
public:
	// explicit Proton(Vector3D const& pos, Vector3D const& speed, bool unitGeV = true, Renderer * engine_ptr = nullptr, double lambda = 1);
	explicit Proton(Vector3D const& pos, double energy, Vector3D speed, bool unitGeV = true, Renderer * engine_ptr = nullptr, double lambda = 1);
	virtual void draw(Renderer * engine_ptr = nullptr) const override;
	virtual std::unique_ptr<Particle> copy() const override;
	virtual std::unique_ptr<Particle> scaledCopy(Vector3D const& pos, double energy, Vector3D speed, double _mass, int charge, double lambda) const override;
};

/**
 * Stupid simple antiproton class
 */

class AntiProton : public Particle {
public:
	// explicit AntiProton(Vector3D const& pos, Vector3D const& speed, bool unitGeV = true, Renderer * engine_ptr = nullptr, double lambda = 1);
	explicit AntiProton(Vector3D const& pos, double energy, Vector3D speed, bool unitGeV = true, Renderer * engine_ptr = nullptr, double lambda = 1);
	virtual void draw(Renderer * engine_ptr = nullptr) const override;
	virtual std::unique_ptr<Particle> copy() const override;
	virtual std::unique_ptr<Particle> scaledCopy(Vector3D const& pos, double energy, Vector3D speed, double _mass, int charge, double lambda) const override;
};

/****************************************************************
 * Cout overloading
 ****************************************************************/

/**
 * Streams the `Particle::to_string()` representation to a given stream
 */

std::ostream& operator << (std::ostream& stream, Particle const& p);

#endif
