#ifndef STRAIGHT_H
#define STRAIGHT_H

#pragma once

#include <iomanip>
#include <iostream>
#include <memory>
#include <string>
#include <sstream>

// Forward declaration
class Vector3D;
class Particle;
class Element;
class Drawable;
class Renderer;

#include "globals.h"
#include "exceptions.h"

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

	explicit Straight(Vector3D const& posIn, Vector3D const& posOut, double radius, Renderer * engine_ptr = nullptr);

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

	explicit Straight(Vector3D const& posIn, double length, Vector3D direction, double radius, Renderer * engine_ptr = nullptr);

	/****************************************************************
	 * Polymorphic copy for Accelerator
	 ****************************************************************/

	/**
	 * Returns a new shared_ptr constructed dynamically
	 *
	 * This new pointer contains a polymorphic copy of the current Straight element.
	 *
	 * We are returning a pointer on Element because in Accelerator we store them as shared_ptr<Element> (for polymorphism)
	 */

	virtual std::shared_ptr<Element> copy() const override;

	/****************************************************************
	 * Getter (virtual)
	 ****************************************************************/

	/**
	 * Returns a Vector3D Field at the position pos
	 *
	 * methodChapi is useless here, but we need to put it in order to avoid Straight to be an abstract class
	 *
	 * In the Straight class the Electric and Magnetic fields are null so it returns the 0 vector
	 */

	virtual Vector3D getField(Vector3D const& pos, bool const& methodChapi = false) const override;

	/**
	 * Returns the HORIZONTAL direction perpendicular to the Straight Element at a certain position
	 *
	 * The position is useless here but we need it for polymorphism
	 */

	virtual Vector3D const getNormalDirection(Vector3D const& pos) const override;

	/**
	 * Returns the percentage of the trajectory effected by the particle in the Element
	 *
	 * Possibility to choose between the method wanted by Chap (returned value is always positive) or a method that does not approximate the accelerator by a circle
	 *
	 * - < 0 : the Particle might be in the previous Element (if it exists)
	 * - Between 0 and 1 : the Particle in inside the Element
	 * - > 1 : the Particle might be in the next Element (if it exists)
	 */

	virtual double getParticleProgress(Vector3D const& pos, bool const& methodChapi = false) const override;

	/**
	 * Returns the total length of the Straight Element
	 */

	virtual double getLength() const override;

	/**
	 * Returns a Vector3D containing the position (e.g. of a Particle) at a certain purrcentage of the Straight Element (between 0 and 1)
	 */

	virtual Vector3D getPosAtProgress(double progress) const override;

	/**
	 * Returns a Vector3D containing the direction (not normalized) of the Straight Element at a certain pourrcentage of the Straight Element (between 0 and 1)
	 */

	virtual Vector3D getVelAtProgress(double progress, bool const& clockwise) const override;

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
	 * Returns a pointer to a copy of the current FODO element (this)
	 */

	std::shared_ptr<Straight> cloneThis() const;

};


#endif
