#ifndef ELEMENT_H
#define ELEMENT_H

#pragma once

#include <iomanip>
#include <iostream>
#include <string>
#include <sstream>

// Forward declaration
class Particle;
class Vector3D;
class Drawable;
class Renderer;

#include "src/globals.h"
#include "src/exceptions.h"

/**
 * Element is an abstract class which embodies the element of an accelerator
 */

class Element : public Drawable {
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
	 * - `Renderer * engine_ptr` : initialization of the `Renderer` if given, nullptr by default
	 *
	 * The constructor is explicit to prevent accidental type casting.
	 */

	explicit Element(Vector3D const& posIn, Vector3D const& posOut, double const& radius, Renderer * engine_ptr = nullptr);

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

	virtual ~Element();

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
	 * Make the pointer next_ptr of the current element point at the _next and reciprocally the pointer prev_ptr of the _next element point at the current element
	 *
	 * Useful in Accelerator in order to make a full circle (link the last one with the first element)
	 */

	void linkNext(Element & _next);

	/**
	 * Returns true if the Particle p has surpassed the current element and is in the next Element
	 */

	bool isInNextElement(Particle const& p) const;

	/**
	 * Make the pointer "element_ptr" of the Particle p point to the new element in which the particle is
	 *
	 * Used primarily in Accelerator::updateParticleElement(Particle&)
	 *
	 * We evaluate the distance between the particle and the output position of the previous element and the distance between the particle and the input position of the next element
	 * We return the element whose distance is the shortest
	 *
	 * If the distance are the same are both prev and next are nullptr we will return the ancient element without doing anything by CONVENTION, but it should never happen normally
	 */

	void updatePointedElement(Particle & p) const;

	/****************************************************************
	 * Virtual methods
	 ****************************************************************/

	/**
	 * Returns true if the Particle p is outside the Element (touched the wall)
	 */

	virtual bool isInWall(Particle const& p) const = 0;

	/**
	 * Returns a string representation of the element
	 */

	virtual std::string to_string() const;

protected:

	// Attributes

	Vector3D posIn;
	Vector3D posOut;
	double const radius;
	Element * next_ptr;		// initialised to nullptr
	Element * prev_ptr;		// initialised to nullptr
};

/**
 * Overloads ostream operator << for Element
 */

std::ostream& operator<< (std::ostream& stream, Element const& e);

#endif
