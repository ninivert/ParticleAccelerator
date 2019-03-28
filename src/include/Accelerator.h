#ifndef ACCELERATOR_H
#define ACCELERATOR_H

#pragma once

#include <vector>
#include <cmath>
#include <memory>
#include <string>
#include <sstream>
#include <iomanip>

// Forward declaration
class Vector3D;
class Particle;
class Element;
class Drawable;
class Renderer;

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
	 * Destructor calls the Accelerator::clear() method
	 */

	~Accelerator();

	/**
	 * Delete copy constructor
	 *
	 * - To avoid to copy an accelerator (big object)
	 * - To forbid the transmission of pointers on particles (std::unique_ptr) and elements
	 */

	Accelerator(Accelerator const&) = delete;

	/**
	 * Delete assignment operator
	 *
	 * - To avoid to copy an accelerator (big object)
	 * - To forbid the transmission of pointers on particles (std::unique_ptr) and elements
	 */

	Accelerator& operator = (Accelerator const&) = delete;

	/****************************************************************
	 * Getters
	 *
	 * ooooooooooh naw naw naw, that would break the encapsulation !
	 ****************************************************************/

	/****************************************************************
	 * Methods
	 ****************************************************************/

	/**
	 * Add an element (Dipole, Quadrupole, etc.) to the Accelerator
	 *
	 * If another Element already exists, then this binds the two together
	 */

	void addElement(Element * element);

	/**
	 * Adds a particle to the accelerator
	 */

	void addParticle(Particle * particle);

	/**
	 * Complete the accelerator by linking the first element and the last one
	 *
	 * If the position of the input and output are different, throws `EXCEPTIONS::ELEMENT_LOOP_INCOMPLETE`
	 */

	void closeElementLoop();

	/**
	 * Simulate the particle accelerator over a timestep `dt`
	 *
	 * If `dt` is null (aka inferior to GLOBALS::DELTA), then this doesn't do anything
	 */

	void step(double const& dt = GLOBALS::DT);


	/**
	 * Removes all elements and particles from the accelerator
	 */

	void clear();

	/**
	 * Removes all particles from the accelerator
	 */

	void clearParticles();

	/**
	 * Generates a string representation of the accelerator
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

	/****************************************************************
	 * Private methods
	 ****************************************************************/

	/**
	 * Removes all elements from the accelerator
	 *
	 * Private: the user is not allowed to remove elements while particles are still pointing on them
	 */

	void clearElements();

	/**
	 * Make a Particle point to the next Element if it has moved past its current Element
	 *
	 * Private: this method should only be used internally
	 *
	 * Used in Accelerator::step()
	 */

	void updateParticleElement(Particle & particle) const; // const ?

	/****************************************************************
	 * Attributes
	 ****************************************************************/

	/**
	 * Homogeneous collection of std::unique_ptr on Particle
	 *
	 * We chose std::unique_ptr because the Accelerator will be the only object to point on particles and the intelligent pointers offer a good feature for such usage (dynamical allocation)
	 */

	std::vector<std::unique_ptr<Particle>> particles;

	/**
	 * Heterogeneous collection of shared_ptr on Element
	 *
	 * We chose std::shared_ptr because the Accelerator will NOT be the only object to point on particles so we cannot use std::unique_ptr here, and the intelligent pointers are recommended for this because of dynamical allocation (more convenient than C-pointers)
	 */

	std::vector<std::shared_ptr<Element>> elements;
};

/**
 * Overloads ostream operator <<
 */

std::ostream& operator<< (std::ostream& stream, Accelerator const& a);

#endif
