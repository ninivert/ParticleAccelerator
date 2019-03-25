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
 * Element
 */

class Element {
public:
	// Constructors

	Element(Vector3D const& posIn, Vector3D const& posOut, double const& radius);
	// WARNING: prev and next need to stay coherent
	Element(Vector3D const& posIn, Vector3D const& posOut, double const& radius, Element & prev);

	// Element(Element const&) = delete;
	Element& operator = (Element const&) = delete;

	// Destructor

	~Element();

	// Getters

	Vector3D getPosIn() const;
	Vector3D getPosOut() const;
	double getRadius() const;

	// Methods

	void linkNext(Element & _next);
	virtual std::string to_string() const = 0;

	// Virtual methods

	virtual Vector3D getField(Vector3D const& pos) const = 0;
	virtual bool isOut(Particle const& p) const = 0;
	virtual bool isInNext(Particle const& p) const = 0;

protected:
	Vector3D posIn;
	Vector3D posOut;
	double const radius;
	Element * next;		// initialised to nullptr
	Element * prev;		// initialised to nullptr
};

/**
 * Cout overloading
 */

std::ostream& operator<< (std::ostream& stream, Element const& e);

#endif
