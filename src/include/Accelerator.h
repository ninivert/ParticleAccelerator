#ifndef ACCELERATOR_H
#define ACCELERATOR_H

#pragma once

// Storing particles and elements dynamically
#include <vector>
// Maths
#include <cmath>
// unique_ptr on Particle + shared_ptr on Element
#include <memory>
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
 * Accelerator
 */

class Accelerator {
public:
	/****************************************************************
	 * Constructors
	 ****************************************************************/

	/**
	 * Default constructor
	 */

	Accelerator();

	/**
	 * Destructor calls the clear() method
	 */

	~Accelerator();

	/**
	 * Delete copy constructor
	 */

	Accelerator(Accelerator const&) = delete;

	/**
	 * Delete assignment operator
	 */

	Accelerator& operator = (Accelerator const&) = delete;

	/****************************************************************
	 * Methods
	 ****************************************************************/

	/**
	 * Simulate the particle accelerator over a timestep `dt`
	 *
	 * If `dt` is null (aka inferior to GLOBALS::DELTA), then this doesn't do anything
	 */

	void step(double const& dt = GLOBALS::DT);

	/**
	 * Add an element (dipole, quadrupole, etc.) to the accelerator
	 *
	 * This element is unlinked from any other element
	 */

	void addElement(Element * element);

	/**
	 * Add an element (dipole, quadrupole, etc.) to the accelerator
	 * and assemble it after another element
	 *
	 * `element.prev` and `prevElement.next` pointers are modified to assure cohesion
	 */

	void addElement(Element * element, Element * prevElement);

	/**
	 * Adds a particle to the accelerator
	 */

	void addParticle(Particle * particle);

	/**
	 * Removes all elements and particles from the accelerator
	 */

	void clear();

	/**
	 * Removes all particles from the accelerator
	 */

	void clearParticles();

	/**
	 * Removes all elements from the accelerator
	 */

	void clearElements();

	/**
	 * Generates the string representation of the accelerator
	 */

	std::string to_string() const;

private:
	// Attributes

	/**
	 * Homogeneous collection of unique_ptr on Particle
	 *
	 * We chose unique_ptr because the Accelerator will be the only object to point on particles and the intelligent pointers offer a good feature for such usage (dynamical allocation)
	 */

	std::vector<std::unique_ptr<Particle>> particles;

	/**
	 * Heterogeneous collection of shared_ptr on Element
	 *
	 * We chose shared_ptr because the Accelerator will NOT be the only object to point on particles so we cannot use unique_ptr here, and the intelligent pointers are recommended for this because of dynamical allocation (more convenient than C-pointers)
	 */

	std::vector<std::shared_ptr<Element>> elements;
};

/**
 * Overloads ostream operator <<
 */

std::ostream& operator<< (std::ostream& stream, Accelerator const& a);

#endif
