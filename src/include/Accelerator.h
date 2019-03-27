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

// Circular dependency resolution
#include "src/include/fwd/Renderer.fwd.h"

#include "src/include/Vector3D.h"
#include "src/include/Particle.h"
#include "src/include/Element.h"
#include "src/include/Dipole.h"
#include "src/include/Quadrupole.h"
#include "src/include/Straight.h"
#include "src/globals.h"
#include "src/exceptions.h"

/**
 * Accelerator
 */

class Accelerator : public Drawable {
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
	 * Delete copy constructor mainly to avoid to copy an accelerator (big object) and to forbid the transmission of pointers on particles (unique_ptr) and elements
	 */

	Accelerator(Accelerator const&) = delete;

	/**
	 * Delete assignment operator for the same reasons as the copy constructor (Accelerator::Accelerator(Accelerator const&))
	 */

	Accelerator& operator = (Accelerator const&) = delete;

	/****************************************************************
	 * Getters
	 ****************************************************************/

	/**
	 * OH NO NO NO NO NOOOOOOOOOOOOOO => AGAINST ENCAPSULATION
	 */

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
	 * Generates the string representation of the accelerator
	 */

	std::string to_string() const;

	/****************************************************************
	 * Rendering engine
	 ****************************************************************/

	/**
	 * Reroute the drawing call (double dispatching)
	 */

	virtual void draw() const override;

private:

	/**
	 * Removes all elements from the accelerator
	 *
	 * Private for the user not to be allowed to remove elements while particles are still pointing at them
	 */

	void clearElements();

	/**
	 * Make the pointer "element" of the Particle p point to the new element in which the particle is now or if there are none
	 *
	 * Used in Accelerator::step()
	 *
	 * We evaluate the distance between the particle and the output position of the previous element and the distance between the particle and the input position of the next element
	 * We return the element whose distance is the shortest
	 *
	 * If the distance are the same are both prev and next are nullptr we will return the ancient element without doing anything by CONVENTION, but it should never happen normally
	 *
	 * Private for the user not to be allowed to change elements like that
	 */

	void updateElement(Particle & particle) const; // const ?

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
