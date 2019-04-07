#ifndef DIPOLE_H
#define DIPOLE_H

#pragma once

#include <cmath>
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

#include "src/globals.h"
#include "src/exceptions.h"

/**
 * The Dipole corrects the trajectory of the Particles in turns
 */

class Dipole : public Element {
public:

	/****************************************************************
	 * Constructors
	 ****************************************************************/

	/**
	 * Constructor for initialisation of a simple Dipole element (without linking to the previous one) with the initial and final position
	 *
	 * - `Vector3D posIn`: initial position of the dipole element
	 * - `Vector3D posOut`: final position of the dipole element
	 * - `double radius`: internal radius of the vacuum chamber of the dipole element
	 * - `double curvature`: curvature of the vacuum chamber of the dipole (curvature = 1 / R where R is the radius of curvature)
	 * - `double B`: the magnetic field of the dipole will change according to the particles that the user wants to keep (depending on their energy)
	 * - `Renderer * engine_ptr` : initialization of the `Renderer` if given, nullptr by default
	 *
	 * The constructor is explicit to prevent accidental type casting.
	 *
	 * The center of curvature is initialized with the CONVENTION that when k is positive, the direction of the arc from the initial position to the final position is CLOCKWISE (anti-trigonometric)
	 */

	explicit Dipole(Vector3D const& posIn, Vector3D const& posOut, double const& radius, double const& curvature, double const& B, Renderer * engine_ptr = nullptr);

	/****************************************************************
	 * Polymorphic copy for Accelerator
	 ****************************************************************/

	/**
	 * Returns a new shared_ptr constructed dynamically
	 *
	 * This new pointer contains a polymorphic copy of the current Dipole element.
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
	 *
	 * By convention the magnetic field is alongside the direction of the third vector of the canonical basis (Vector3D(0, 0, 1))
	 */

	virtual Vector3D getField(Vector3D const& pos, bool const& methodChapi = false) const override;

	/****************************************************************
	 * Setter
	 ****************************************************************/

	/**
	 * Sets the magnetic field exerted by the Dipole
	 */

	void setB(double const& B);

	/****************************************************************
	 * Virtual methods
	 ****************************************************************/

	/**
	 * Returns true if the Particle p is outside the dipole (touched the wall)
	 */

	virtual bool isInWall(Particle const& p) const override;

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
	 * Returns a string representation of the dipole
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

private:


	/****************************************************************
	 * Private methods (Polymorphic copy)
	 ****************************************************************/

	/**
	 * Returns a pointer to a copy of the current FODO element (this)
	 */

	std::shared_ptr<Dipole> cloneThis() const;

	/****************************************************************
	 * Attributes
	 ****************************************************************/

	double const curvature;
	Vector3D const posCenter;

	/**
	 * Magnetic field intensity
	 */

	double B;
};

#endif
