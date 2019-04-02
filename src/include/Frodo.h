#ifndef FRODO_H
#define FRODO_H

#pragma once

#include <iomanip>
#include <iostream>
#include <string>
#include <sstream>

// Forward declaration
class Particle;
class Vector3D;
class Element;
class Drawable;
class Renderer;

#include "src/globals.h"
#include "src/exceptions.h"

/**
 * YOU MUST PROTECT THE RING FRODO
 */

class Frodo : public Straight, public Quadrupole {
public:

	/****************************************************************
	 * Constructors and destructors
	 ****************************************************************/

	/**
	 * Constructor using
	 *
	 * - posIn: entry of the FODO
	 * - posOut: output of the FODO
	 * - radius: radius of the vacuum chamber
	 * - b: quadrupole magnetic field intensity
	 * - straightLength: length of each straight element
	 */

	Frodo(Vector3D const& posIn, Vector3D const& posOut, double const& radius, double const& b, double const& straightLength);

	/**
	 * Constructor using
	 *
	 * - posIn: entry of the FODO
	 * - totalLength: total length of the FODO element
	 * - direction: direction of the FODO element
	 * - radius: radius of the vacuum chamber
	 * - b: quadrupole magnetic field intensity
	 * - straightLength: length of each straight element
	 */

	Frodo(Vector3D const& posIn, double const& totalLength, Vector3D direction, double const& radius, double const& b, double const& straightLength);

	/****************************************************************
	 * Getter (virtual)
	 ****************************************************************/

	/**
	 * Returns a Vector3D Field at the position pos
	 *
	 * In the Straight class the Electric and Magnetic fields are null so it returns the 0 vector
	 */

	virtual Vector3D getField(Vector3D const& pos) const override;

	/****************************************************************
	 * Virtual methods
	 ****************************************************************/

	/**
	 * Returns true if the Particle p is outside the straight element (touched the wall)
	 */

	virtual bool isInWall(Particle const& p) const override;

	/**
	 * Returns a string representation of the straight element
	 */

	virtual std::string to_string() const override;

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

	/**
	 * Length of the straight neutral sections
	 */

	double straightLength;

	// posIn, posOut, radius -> inherited from Element
	// b -> inherited from Quadrupole
};

#endif
