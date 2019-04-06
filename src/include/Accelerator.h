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
	 * Constructor
	 ****************************************************************/

	/**
	 * Constructor with init of the pointer to a `Renderer` inherited from `Drawable`
	 *
	 * The constructor is explicit to prevent accidental type casting.
	 *
	 * Can be used as a default constructor
	 */

	explicit Accelerator(Renderer * engine_ptr = nullptr);

	/**
	 * Destructor calls the Accelerator::clear() method
	 */

	/****************************************************************
	 * Destructor
	 ****************************************************************/

	~Accelerator();

	/**
	 * Delete copy constructor
	 *
	 * - To avoid to copy an accelerator (big object)
	 * - To forbid the transmission of pointers on `Particle` (std::unique_ptr) and `Element` (std::shared_ptr)
	 */

	/****************************************************************
	 * Copy constructor and operator =
	 ****************************************************************/

	Accelerator(Accelerator const&) = delete;

	/**
	 * Delete assignment operator
	 *
	 * - To avoid to copy an accelerator (big object)
	 * - To forbid the transmission of pointers on `Particle` (std::unique_ptr) and `Element` (std::shared_ptr)
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
	 * Add an Element (Dipole, Quadrupole, etc.) to the Accelerator
	 *
	 * If another Element already exists, then this binds the two together
	 */

	void addElement(Element const& element);

	/**
	 * Adds a particle to the accelerator
	 */

	void addParticle(Particle const& particle);

	/**
	 * Complete the accelerator by linking the first element and the last one
	 *
	 * If the position of the input and output are different, throws `EXCEPTIONS::ELEMENT_LOOP_INCOMPLETE`
	 */

	void closeElementLoop();

	/**
	 * Simulate the particle accelerator over a timestep `dt`
	 *
	 * Make a Particle point to the next Element if it has moved past its current Element
	 *
	 * If `dt` is null (aka inferior to GLOBALS::DELTA), then this doesn't do anything
	 */

	void step(double const& dt = GLOBALS::DT);


	/**
	 * Removes all elements and particles from the accelerator and DELETE THEM
	 */

	void clear();

	/**
	 * Removes all particles from the accelerator and DELETE THEM
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

	/**
	 * Draw the vector using a given renderer
	 */

	virtual void drawTo(Renderer * engine_ptr) const override;

private:

	/****************************************************************
	 * Private methods
	 ****************************************************************/

	/**
	 * Removes all elements from the accelerator and DELETE THEM
	 *
	 * Private: the user is not allowed to remove elements while particles are still pointing on them
	 */

	void clearElements();

	/**
	 * Remove Particle that are out of the Accelerator
	 *
	 * Private: this method should only be used internally in Accelerator::step()
	 */

	void clearDeadParticles();

	/**
	 * Initialization of a particle by searching which element is the closest
	 *
	 * Private: this method should only be used internally in Accelerator::addParticle()
	 */

	void initOneParticle(Particle & particle) const;

	/****************************************************************
	 * Attributes
	 ****************************************************************/

	/**
	 * Homogeneous collection of std::unique_ptr on Particle
	 *
	 * We chose std::unique_ptr because the Accelerator will be the only object to point on particles and the intelligent pointers offer a good feature for such usage (dynamical allocation)
	 */

	std::vector<std::unique_ptr<Particle>> particles_ptr;

	/**
	 * Heterogeneous collection of shared_ptr on Element
	 *
	 * We chose std::shared_ptr because the Accelerator will NOT be the only object to point on elements (elements are pointing to each other) so we cannot use std::unique_ptr here, and the intelligent pointers are recommended for this because of dynamical allocation (more convenient than C-pointers)
	 */

	std::vector<std::shared_ptr<Element>> elements_ptr;
};

/**
 * Overloads ostream operator <<
 */

std::ostream& operator<< (std::ostream& stream, Accelerator const& a);

#endif
