#ifndef ACCELERATOR_H
#define ACCELERATOR_H

#pragma once

#include <vector>
#include <string>

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

	void step();
	void addElement();
	void addElement(Element const& prevElement);
	void addParticle(Particle const& particle);
	void clear();
	void clearParticles();
	void clearElements();
	std::string to_string();

private:
	std::vector<Particle> particles;
	std::vector<Element> elements;
};

/**
 * Cout overloading
 */

std::ostream& operator<< (std::ostream& stream, Accelerator const& a);

#endif
