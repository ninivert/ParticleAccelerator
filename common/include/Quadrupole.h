#ifndef QUADRUPOLE_H
#define QUADRUPOLE_H

#pragma once

#include <iomanip>
#include <iostream>
#include <memory>
#include <string>
#include <sstream>

// Forward declaration
class Vector3D;
class Particle;
class Straight;
class Drawable;
class Renderer;

#include "globals.h"
#include "exceptions.h"

/**
 * The Quadrupole Element focuses a Particle beam towards their ideal trajectory using 4 magnets
 */

class Quadrupole : public Straight {
public:

	/****************************************************************
	 * Constructors
	 ****************************************************************/

	/**
	 * Constructor for initialisation of a simple Quadrupole element
	 * (without linking to the previous one)
	 * with the initial and final position
	 *
	 * - `Vector3D posIn`: initial position of the Quadrupole element
	 * - `Vector3D posOut`: final position of the Quadrupole element
	 * - `double radius`: internal radius of the vacuum chamber of the Quadrupole element
	 * - `double b`: proper internal magnetic field of the Quadrupole (for propotional recall force)
	 * - `Renderer * engine_ptr` : initialization of the `Renderer` if given, nullptr by default
	 *
	 * The constructor is explicit to prevent accidental type casting.
	 */

	explicit Quadrupole(Vector3D const& posIn, Vector3D const& posOut, double const& radius, double const& b, Renderer * engine_ptr = nullptr);

	/**
	 * Constructor for initialisation of a simple Quadrupole element
	 * (without linking to the previous one)
	 * with the initial position, the length of the element and the direction
	 *
	 * - `Vector3D posIn`: initial position of the Quadrupole element
	 * - `double length` : length of the element
	 * - `Vector3D direction`: direction of the Quadrupole element (from initial position) copy in order to normalize it
	 * - `double radius`: internal radius of the vacuum chamber of the Quadrupole element
	 * - `double b`: proper internal magnetic field of the Quadrupole (for propotional recall force)
	 * - `Renderer * engine_ptr` : initialization of the `Renderer` if given, nullptr by default
	 *
	 * The constructor is explicit to prevent accidental type casting.
	 */

	explicit Quadrupole(Vector3D const& posIn, double const& length, Vector3D direction, double const& radius, double const& b, Renderer * engine_ptr = nullptr);

	/****************************************************************
	 * Polymorphic copy for Accelerator
	 ****************************************************************/

	/**
	 * Returns a new shared_ptr constructed dynamically
	 *
	 * This new pointer contains a polymorphic copy of the current Quadrupole element.
	 *
	 * We are returning a pointer on Element because in Accelerator we store them as shared_ptr<Element> (for polymorphism)
	 */

	virtual std::shared_ptr<Element> copy() const override;

	/****************************************************************
	 * Getter (virtual)
	 ****************************************************************/

	/**
	 * Returns a Vector3D representing the magnetic field at the position pos
	 *
	 * methodChapi is useless here, but we need to put it in order to avoid Quadrupole to be an abstract class
	 */

	virtual Vector3D getField(Vector3D const& pos, bool const& methodChapi = false) const override;

	/****************************************************************
	 * Virtual methods
	 ****************************************************************/

	/**
	 * Returns a string representation of the Quadrupole
	 */

	virtual std::string to_string() const;

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
	 * Private methods (Polymorphic copy)
	 ****************************************************************/

	/**
	 * Returns a pointer to a copy of the current Quadrupole element (this)
	 */

	std::shared_ptr<Quadrupole> cloneThis() const;

	/****************************************************************
	 * Attributes
	 ****************************************************************/

	/**
	 * Intensity of the magnetic field
	 */

	double b;
};


#endif
