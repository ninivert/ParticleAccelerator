#ifndef FRODO_H
#define FRODO_H

#pragma once

#include <iomanip>
#include <iostream>
#include <memory>
#include <string>
#include <sstream>
#include <cmath>

// Forward declaration
class Vector3D;
class Particle;
class Straight;
class Quadrupole;
class Drawable;
class Renderer;

#include "globals.h"
#include "exceptions.h"

/**
 * YOU MUST PROTECT THE RING FRODO
 */

class Frodo : public Straight {
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
	 * - `Renderer * engine_ptr` : initialization of the `Renderer` if given, nullptr by default
	 *
	 * The constructor is explicit to prevent accidental type casting.
	 */

	explicit Frodo(Vector3D const& posIn, Vector3D const& posOut, double radius, double b, double straightLength, Renderer * engine_ptr = nullptr);

	/**
	 * Constructor using
	 *
	 * - posIn: entry of the FODO
	 * - totalLength: total length of the FODO element
	 * - direction: direction of the FODO element
	 * - radius: radius of the vacuum chamber
	 * - b: quadrupole magnetic field intensity
	 * - straightLength: length of each straight element
	 * - `Renderer * engine_ptr` : initialization of the `Renderer` if given, nullptr by default
	 *
	 * The constructor is explicit to prevent accidental type casting.
	 */

	explicit Frodo(Vector3D const& posIn, double totalLength, Vector3D direction, double radius, double b, double straightLength, Renderer * engine_ptr = nullptr);

	/****************************************************************
	 * Polymorphic copy for Accelerator
	 ****************************************************************/

	/**
	 * Returns a new shared_ptr constructed dynamically
	 * This new pointer contains a polymorphic copy of the current FODO element.
	 * We are returning a pointer on Element because in Accelerator we store them as shared_ptr<Element> (for polymorphism)
	 */

	virtual std::shared_ptr<Element> copy() const override;

	/****************************************************************
	 * Getter (virtual)
	 ****************************************************************/

	/**
	 * Returns a Vector3D Field at the position pos
	 *
	 * Possibility to choose between the method wanted by Chap (returned value is always positive) or a method that does not approximate the accelerator by a circle
	 */

	virtual Vector3D getField(Vector3D const& pos, bool const& methodChapi = false) const override;

	/****************************************************************
	 * Virtual methods
	 ****************************************************************/

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

	/**
	 * Draw elements in the Frodo element (Quadrupole and Straight)
	 */

	void drawElements() const;

private:

	/****************************************************************
	 * Private methods (Polymorphic copy)
	 ****************************************************************/

	/**
	 * Returns a pointer to a copy of the current FODO element (this)
	 */

	std::shared_ptr<Frodo> cloneThis() const;

	/****************************************************************
	 * Attributes
	 ****************************************************************/

	/**
	 * Quadrupole magnetic field intensity
	 */

	double b;

	/**
	 * Length of the straight neutral sections
	 */

	double straightLength;

	/**
	 * Length of the focalizer sections (computed)
	 */

	double lensLength;

	/**
	 * Direction Frodo is facing (computed)
	 */

	Vector3D direction;

	/**
	 * First intersection, between focalizer and firstStraight (computed)
	 */

	Vector3D intersect1;

	/**
	 * Second intersection, between firstStraight and defocalizer (computed)
	 */

	Vector3D intersect2;

	/**
	 * First intersection, between defocalizer and lastStraight (computed)
	 */

	Vector3D intersect3;

	// posIn, posOut, radius -> inherited from Straight

	/**
	 * Focalizer Quadrupole element
	 */

	Quadrupole focalizer;

	/**
	 * Defocalizer Quadrupole element
	 */

	Quadrupole defocalizer;

	/**
	 * First Straight element
	 */

	Straight firstStraight;

	/**
	 * Second Straight element
	 */

	Straight lastStraight;
};

#endif
