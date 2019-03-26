#ifndef DIPOLE_H
#define DIPOLE_H

#pragma once

#include <cmath>
#include <iomanip>
#include <iostream>
#include <string>
#include <sstream>

#include "src/include/Element.h"
#include "src/include/Particle.h"
#include "src/include/Vector3D.h"
#include "src/globals.h"

/**
 * Dipole : it is a sub-class of Element
 *
 * It implements the representation of curved elements with magnetic field which aims at balancing the centrifugal force for an ideal trajectory
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
	 *
	 * The center of curvature is initialized with the CONVENTION that when k is positive, the direction of the arc from the initial position to the final position is counter-clockwise (trigonometric)
	 */

	Dipole(Vector3D const& posIn, Vector3D const& posOut, double const& radius, double const& curvature, double const& B);

	/**
	 * Constructor for initialisation of a Dipole with a reference to the previous element with the initial and final position
	 *
	 * Useful in Accelerator::addElement(Element * element)
	 *
	 * - `Vector3D posIn`: initial position of the dipole
	 * - `Vector3D posOut`: final position of the dipole
	 * - `double radius`: internal radius of the vacuum chamber of the dipole
	 * - `double curvature`: curvature of the vacuum chamber of the dipole (curvature = 1 / R where R is the radius of curvature)
	 * - `Element & prev` : reference to the previous Element (for pointer init.)
	 * - `double B`: the magnetic field of the dipole will change according to the particles that the user wants to keep (depending on their energy)
	 *
	 * The center of curvature is initialized with the CONVENTION that when k is positive, the direction of the arc from the initial position to the final position is counter-clockwise (trigonometric)
	*/

	Dipole(Vector3D const& posIn, Vector3D const& posOut, double const& radius, double const& curvature, Element & prev, double const& B);

	/****************************************************************
	 * Getter (virtual)
	 ****************************************************************/

	/**
	 * Returns a Vector3D representing the magnetic field at the position pos
	 *
	 * By convention the magnetic field is alongside the direction of the third vector of the canonical basis (Vector3D(0, 0, 1))
	 */

	virtual Vector3D getField(Vector3D const& pos) const override;

	/****************************************************************
	 * Setter
	 ****************************************************************/

	/**
	 * Sets private B to the given parameter
	 */

	void setB(double const& B);

	/****************************************************************
	 * Virtual methods
	 ****************************************************************/

	/**
	 * Returns true if the Particle p is still inside the dipole (touched the wall)
	 */

	virtual bool isOut(Particle const& p) const override;

	/**
	 * Returns a string representation of the dipole
	 */

	virtual std::string to_string() const override;

private:

	// Attributes

	double const curvature;
	Vector3D const posCenter;	// CONVENTION : k positive => counterclockwise (opposite from given parameters)
	double B;					// Magnetic field
};

#endif
