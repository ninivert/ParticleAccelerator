#ifndef ACCELERATOR_H
#define ACCELERATOR_H

#pragma once

// Storing particles and elements dynamically
#include <vector>
// Maths
#include <cmath>
// String representation
#include <string>
#include <sstream>
#include <iomanip>

#include "src/include/Vector3D.h"
#include "src/include/Particle.h"
#include "src/include/Element.h"
#include "src/include/Dipole.h"
#include "src/include/Quadrupole.h"
#include "src/globals.h"

/**
 * Element
 */

class Accelerator {
public:
	// Constructor

	Accelerator();
	Accelerator(Accelerator const&) = delete;
	Accelerator& operator = (Accelerator const&) = delete;

	// Methods

	void step(double const& dt = GLOBALS::DT);
	void addElement(Element const& element);
	void addElement(Element & element, Element & prevElement);
	void addParticle(Particle const& particle);
	void clear();
	void clearParticles();
	void clearElements();
	std::string to_string() const;

private:
	std::vector<Particle> particles;
	std::vector<Element> elements;
};

/**
 * Cout overloading
 */

std::ostream& operator<< (std::ostream& stream, Accelerator const& a);

#endif
