#ifndef STRAIGHT_H
#define STRAIGHT_H

#pragma once

#include "src/include/Element.h"
#include "src/include/Particle.h"
#include "src/include/Vector3D.h"
#include "src/globals.h"

/**
 * Straight class is a sub-class of Element
 *
 * It implements the straight section of an accelerator.
 *
 * It is used to bind 2 differents magnets to avoid an overlap of leakage fields
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
	 */

	Straight(Vector3D const& posIn, Vector3D const& posOut, double const& radius);

	/**
	 * Constructor for initialisation of a simple Straight element (without linking to the previous one) with the initial position, the length of the element and the direction
	 *
	 * - `Vector3D posIn`: initial position of the straight element
	 * - `double length` : length of the element
	 * - `Vector3D direction`: direction of the straight element (from initial position) copy in order to normalize it
	 * - `double radius`: internal radius of the vacuum chamber of the straight element
	 */

	Straight(Vector3D const& posIn, double const& length, Vector3D direction, double const& radius);

	/**
	 * Constructor for initialisation of a Straight element with a reference to the previous element with the initial and final position
	 *
	 * Useful in Accelerator::addElement(Element * element)
	 *
	 * - `Vector3D posIn`: initial position of the straight element
	 * - `Vector3D posOut`: final position of the straight element
	 * - `double radius`: internal radius of the vacuum chamber of the straight element
	 * - `Element & prev` : reference to the previous Element (for pointer init.)
	 */

	Straight(Vector3D const& posIn, Vector3D const& posOut, double const& radius, Element & prev);

	/**
	 * Constructor for initialisation of a Straight element with a reference to the previous element with the initial position, the length of the element and the direction
	 *
	 * Useful in Accelerator::addElement(Element * element)
	 *
	 * - `Vector3D posIn`: initial position of the straight element
	 * - `double length` : length of the element
	 * - `Vector3D direction`: direction of the straight element (from initial position) copy in order to normalize it
	 * `double radius`: internal radius of the vacuum chamber of the straight element
	 * - `Element & prev` : reference to the previous Element (for pointer init.)
	 */

	Straight(Vector3D const& posIn, double const& length, Vector3D direction, double const& radius, Element & prev);

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

	virtual bool isOut(Particle const& p) const override;

	/**
	 * Returns a string representation of the straight element
	 */

	virtual std::string to_string() const override;
};


#endif
