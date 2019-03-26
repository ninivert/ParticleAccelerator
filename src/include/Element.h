#ifndef ELEMENT_H
#define ELEMENT_H

#pragma once

#include <iomanip>
#include <iostream>
#include <string>
#include <sstream>

#include "src/include/Vector3D.h"
#include "src/include/Particle.h"
#include "src/globals.h"
#include "src/exceptions.h"

// Resolve ciruclar header definition
class Particle;

/**
 * Element is an abstract class which embodies the element of an accelerator
 */

class Element {
public:

	/****************************************************************
	 * Constructors
	 ****************************************************************/

	/**
	 * Constructor for initialisation of a simple Element (without linking to the previous one) with the initial and final position
	 *
	 * - `Vector3D posIn`: initial position of the element
	 * - `Vector3D posOut`: final position of the element
	 * - `double radius`: internal radius of the vacuum chamber of the element
	 */

	Element(Vector3D const& posIn, Vector3D const& posOut, double const& radius);
	/**
	 * Constructor for initialisation of an Element with a reference to the previous element with the initial and final position
	 *
	 * - `Vector3D posIn`: initial position of the element
	 * - `Vector3D posOut`: final position of the element
	 * - `double radius`: internal radius of the vacuum chamber of the element
	 * - `Element & prev` : reference to the previous Element (for pointer init.)
	 *
	 * WARNING: prev and next need to stay coherent
	 */

	Element(Vector3D const& posIn, Vector3D const& posOut, double const& radius, Element & prev);

	/****************************************************************
	 * Copy constructor and operator =
	 ****************************************************************/

	/**
	 * Copy Constructor deleted because copying an element has no physical meaning (superposition ? how do you modify the pointers ?) and to avoid copying pointers without knowing it
	 */

	Element(Element const&) = delete;

	/**
	 * operator = deleted for the same reasons as the copy constructor (Element::Element(Element const&))
	 */

	Element& operator = (Element const&) = delete;

	/****************************************************************
	 * Destructor
	 ****************************************************************/

	/**
	 * Destructor for the 2 attributes which are pointers on Element, prev and next, to point to nullptr without deleting these elements
	 */

	~Element();

	/****************************************************************
	 * Getters
	 ****************************************************************/

	/**
	 * Returns the private getPosIn attribute
	 */

	Vector3D getPosIn() const;

	/**
	 * Returns the private getPosOut attribute
	 */

	Vector3D getPosOut() const;

	/**
	 * Returns the private getRadius attribute
	 */

	double getRadius() const;

	/****************************************************************
	 * Getter (virtual)
	 ****************************************************************/

	/**
	 * Returns a Vector3D representing the magnetic field at the position pos
	 */

	virtual Vector3D getField(Vector3D const& pos) const = 0;

	/****************************************************************
	 * Methods
	 ****************************************************************/

	/**
	 * Make the pointer next of the current particle point at the _next and reciprocally the pointer prev of the _next particle point at the current particle
	 *
	 * Useful in Accelerator in order to make a full circle (link the last one with the first element)
	 */

	void linkNext(Element & _next);

	/**
	 * Returns true if the Particle p has surpassed the current element and is in the next Element
	 */

	bool isInNext(Particle const& p) const;

	/****************************************************************
	 * Virtual methods
	 ****************************************************************/

	/**
	 * Returns true if the Particle p is still inside the Element
	 */

	virtual bool isOut(Particle const& p) const = 0;

	/**
	 * Returns a string representation of the element
	 */

	virtual std::string to_string() const;

protected:

	// Attributes

	Vector3D posIn;
	Vector3D posOut;
	double const radius;
	Element * next;		// initialised to nullptr
	Element * prev;		// initialised to nullptr
};

/**
 * Overloads ostream operator << for Element
 */

std::ostream& operator<< (std::ostream& stream, Element const& e);

#endif
