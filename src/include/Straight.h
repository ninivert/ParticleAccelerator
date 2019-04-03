#ifndef STRAIGHT_H
#define STRAIGHT_H

#pragma once

// Forward declaration
class Vector3D;
class Particle;
class Element;
class Drawable;
class Renderer;

#include "src/globals.h"
#include "src/exceptions.h"

/**
 * Straight is a straight section of an accelerator (duh)
 *
 * It is used to bind 2 differents magnets and avoid an overlap of magnetic leakage fields
 */

class Straight : public Element {
public:

	/****************************************************************
	 * Constructors
	 ****************************************************************/

	/**
	 * Constructor for initialisation of a simple Straight element (without linking to the previous one) with the initial and final position
	 *
	 * - `Vector3D posIn`: initial position of the straight element
	 * - `Vector3D posOut`: final position of the straight element
	 * - `double radius`: internal radius of the vacuum chamber of the straight element
	 * - `Renderer * engine_ptr` : initialization of the `Renderer` if given, nullptr by default
	 *
	 * The constructor is explicit to prevent accidental type casting.
	 */

	explicit Straight(Vector3D const& posIn, Vector3D const& posOut, double const& radius, Renderer * engine_ptr = nullptr);

	/**
	 * Constructor for initialisation of a simple Straight element (without linking to the previous one) with the initial position, the length of the element and the direction
	 *
	 * - `Vector3D posIn`: initial position of the straight element
	 * - `double length` : length of the element
	 * - `Vector3D direction`: direction of the straight element (from initial position) copy in order to normalize it
	 * - `double radius`: internal radius of the vacuum chamber of the straight element
	 * - `Renderer * engine_ptr` : initialization of the `Renderer` if given, nullptr by default
	 *
	 * The constructor is explicit to prevent accidental type casting.
	 */

	explicit Straight(Vector3D const& posIn, double const& length, Vector3D direction, double const& radius, Renderer * engine_ptr = nullptr);

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

	virtual void drawTo(Renderer * engine_ptr) const override;

};


#endif
