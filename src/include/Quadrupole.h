#ifndef QUADRUPOLE_H
#define QUADRUPOLE_H

#pragma once

// Forward declaration
class Vector3D;
class Particle;
class Straight;
class Drawable;
class Renderer;

#include "src/globals.h"
#include "src/exceptions.h"

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
	 */

	Quadrupole(Vector3D const& posIn, Vector3D const& posOut, double const& radius, double const& b);

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
	 */

	Quadrupole(Vector3D const& posIn, double const& length, Vector3D direction, double const& radius, double const& b);

	/****************************************************************
	 * Getter (virtual)
	 ****************************************************************/

	/**
	 * Returns a Vector3D representing the magnetic field at the position pos
	 */

	virtual Vector3D getField(Vector3D const& pos) const override;

	/****************************************************************
	 * Virtual methods
	 ****************************************************************/

	/**
	 * Returns true if the Particle p is outside the Quadrupole (touched the wall)
	 */

	virtual bool isInWall(Particle const& p) const override;

	/**
	 * Returns a string representation of the Quadrupole
	 */

	virtual std::string to_string() const;

	/****************************************************************
	 * Rendering engine
	 ****************************************************************/

	/**
	 * Reroute the drawing call (double dispatching)
	 */

	virtual void draw() const override;

	/**
	 * Draw the vector using a given renderer
	 */

	virtual void drawTo(Renderer * engine) const override;

private:

	/****************************************************************
	 * Attributes
	 ****************************************************************/

	/**
	 * Intensity of the magnetic field
	 */

	double b;
};


#endif
