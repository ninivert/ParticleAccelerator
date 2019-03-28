#ifndef QUADRUPOLE_H
#define QUADRUPOLE_H

#pragma once

// Forward declaration
class Vector3D;
class Particle;
class Element;
class Drawable;
class Renderer;

#include "src/globals.h"

/**
 * Quadrupole class is a sub-class of Element
 *
 * It represents straight elements with a magnetic field in order to focus the particles beam to an ideal trajectory
 */

class Quadrupole : public Element {
public:

	/****************************************************************
	 * Constructors
	 ****************************************************************/

	/**
	 * Constructor for initialisation of a simple Quadrupole element (without linking to the previous one) with the initial and final position
	 *
	 * - `Vector3D posIn`: initial position of the quadrupole element
	 * - `Vector3D posOut`: final position of the quadrupole element
	 * - `double radius`: internal radius of the vacuum chamber of the quadrupole element
	 * - `double b`: proper internal magnetic field of the quadrupole (for propotional recall force)
	 */

	Quadrupole(Vector3D const& posIn, Vector3D const& posOut, double const& radius, double const& b);

	/**
	 * Constructor for initialisation of a simple Quadrupole element (without linking to the previous one) with the initial position, the length of the element and the direction
	 *
	 * - `Vector3D posIn`: initial position of the quadrupole element
	 * - `double length` : length of the element
	 * - `Vector3D direction`: direction of the quadrupole element (from initial position) copy in order to normalize it
	 * - `double radius`: internal radius of the vacuum chamber of the quadrupole element
	 * - `double b`: proper internal magnetic field of the quadrupole (for propotional recall force)
	 */

	Quadrupole(Vector3D const& posIn, double const& length, Vector3D direction, double const& radius, double const& b);

	/**
	 * Constructor for initialisation of a Quadrupole with a reference to the previous element with the initial and final position
	 *
	 * Useful in Accelerator::addElement(Element * element)
	 *
	 * - `Vector3D posIn`: initial position of the quadrupole
	 * - `Vector3D posOut`: final position of the quadrupole
	 * - `double radius`: internal radius of the vacuum chamber of the quadrupole
	 * - `double b`: proper internal magnetic field of the quadrupole (for propotional recall force)
	 * - `Element & prev` : reference to the previous Element (for pointer init.)
	 */

	Quadrupole(Vector3D const& posIn, Vector3D const& posOut, double const& radius, double const& b, Element & prev);

	/**
	 * Constructor for initialisation of a Quadrupole with a reference to the previous element with the initial position, the length of the quadrupole and the direction
	 *
	 * Useful in Accelerator::addElement(Element * element)
	 *
	 * - `Vector3D posIn`: initial position of the quadrupole
	 * - `double length` : length of the element
	 * - `Vector3D direction`: direction of the quadrupole (from initial position) copy in order to normalize it
	 * - `double radius`: internal radius of the vacuum chamber of the quadrupole
	 * - `double b`: proper internal magnetic field of the quadrupole (for propotional recall force)
	 * - `Element & prev` : reference to the previous Element (for pointer init.)
	 */

	Quadrupole(Vector3D const& posIn, double const& length, Vector3D direction, double const& radius, double const& b, Element & prev);

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
	 * Returns true if the Particle p is outside the quadrupole (touched the wall)
	 */

	virtual bool isOut(Particle const& p) const override;

	/**
	 * Returns a string representation of the quadrupole
	 */

	virtual std::string to_string() const;

	/****************************************************************
	 * Rendering engine
	 ****************************************************************/

	/**
	 * Reroute the drawing call (double dispatching)
	 */

	virtual void draw() const override;

private:

	// Attribute

	double b;		// Intensity of the magnetic field
};


#endif
