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
class Beam;
class Drawable;
class Renderer;

#include "globals.h"
#include "exceptions.h"

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
	 * Possibility to choose which representation of the Accelerator we want (methodChapi)
	 *
	 * - true  : The accelerator is represented by a circle
	 * - false : It is represented as it would look in real life
	 *
	 * Possibility to choose which way we are constructing the Beams (beamFromParticle)
	 *
	 * - true  : The Beams are constructed using a physical source of Particle from the default Particle position by evolving a Particle a given number of times
	 * - false : The Beams are constructed by spreading out a given number of Particles on the ideal trajectory
	 *
	 * The constructor is explicit to prevent accidental type casting.
	 *
	 * Can be used as a default constructor
	 */

	explicit Accelerator(Renderer * engine_ptr = nullptr, bool methodChapi = true, bool beamFromParticle = false);

	/****************************************************************
	 * Destructor
	 ****************************************************************/

	/**
	 * Destructor calls the Accelerator::clear() method
	 */

	~Accelerator();

	/****************************************************************
	 * Copy constructor and operator =
	 ****************************************************************/

	/**
	 * Delete copy constructor
	 *
	 * - To avoid to copy an accelerator (big object)
	 * - To forbid the transmission of pointers on `Particle` (std::unique_ptr) and `Element` (std::shared_ptr)
	 */

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
	 ****************************************************************/

	bool getBeamFromParticle() const;

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
	 * Adds a copy of a new Beam created at the moment to the Accelerator
	 *
	 * It dynamically creates space for a new Beam
	 * We don't add Beam, because a Beam requires an Accelerator to be instantiated so it is easier for the user to just add Particles which will be transformed into Beams
	 *
	 */

	void addBeam(Particle const& defaultParticle, size_t const& particleCount, double const& lambda);

	/**
	 * Adds a Particle to the Accelerator, transform it into a Beam before storing it
	 */

	void addParticle(Particle particle);

	/**
	 * Initialization of a particle by searching which element is the closest
	 *
	 * This method is used in Accelerator::addParticle() and Beam::Beam()
	 */

	void initParticleToClosestElement(Particle & particle) const;

	/**
	 * Complete the accelerator by linking the first element and the last one
	 *
	 * If the position of the input and output are different, throws `EXCEPTIONS::ELEMENT_LOOP_INCOMPLETE`
	 */

	void closeElementLoop();

	/**
	 * Removes all Elements and Beams from the accelerator and DELETE THEM
	 */

	void clear();

	/**
	 * Removes all Beams from the accelerator and DELETE THEM
	 */

	void clearBeams();

	/**
	 * Returns a Vector3D containing the position (e.g. of a Particle) at a certain pourcentage of the Accelerator (between 0 and 1)
	 */

	Vector3D getPosAtProgress(double const& progress) const;

	/**
	 * Returns a Vector3D containing the direction (not normalized) of the Dipole at a certain pourcentage of the Accelerator (between 0 and 1)
	 */

	Vector3D getVelAtProgress(double const& progress, bool const& clockwise) const;

	/**
	 * Simulate the particle accelerator over a timestep `dt`
	 *
	 * Make a Particle point to the next Element if it has moved past its current Element
	 *
	 * If `dt` is null (aka inferior to GLOBALS::DELTA), then this doesn't do anything
	 */

	void step(double const& dt = GLOBALS::DT);

	/**
	 * Generates a string representation of the accelerator
	 */

	std::string to_string() const;

	/****************************************************************
	 * Rendering engine
	 ****************************************************************/

	/**
	 * Reroute the drawing call (double dispatching)
	 *
	 * - Use renderer in argument if given
	 * - Else use class renderer
	 * - Else throw EXCEPTIONS::NULLPTR
	 */

	virtual void draw(Renderer * engine_ptr = nullptr) const override;

	/**
	 * Draw particles only
	 */

	void drawBeams() const;

	/**
	 * Draw elements only
	 */

	void drawElements() const;

private:

	/****************************************************************
	 * Private methods
	 ****************************************************************/

	/**
	 * Removes all Elements from the Accelerator and DELETE THEM
	 *
	 * Private: the user is not allowed to remove Elements while Particles are still pointing on them
	 */

	void clearElements();

	/**
	 * Removes all dead Beams (i.e. containing 0 macroparticles) from the accelerator and DELETE THEM
	 */

	void clearDeadBeams();

	/**
	 * Returns the total length of the Accelerator (sum of the length of each element)
	 *
	 * Used only in Accelerator::getPosAtProgress() and Accelerator::getVelAtProgress()
	 */

	double getTotalLength() const;

	/****************************************************************
	 * Attributes
	 ****************************************************************/

	/**
	 * Homogeneous collection of std::unique_ptr on Beam
	 *
	 * We chose std::unique_ptr because the Accelerator will be the only object to point on beams and the intelligent pointers offer a good feature for such usage (dynamical allocation)
	 */

	std::vector<std::unique_ptr<Beam>> beams_ptr;

	/**
	 * For each Particle in the Beams, we associate a progress of that Particle in the Accelerator which will be used to evaluate the interaction between the Particles
	 */

	std::vector<std::vector<size_t>> associatedProgresses;

	/**
	 * Heterogeneous collection of shared_ptr on Element
	 *
	 * We chose std::shared_ptr because the Accelerator will NOT be the only object to point on elements (elements are pointing to each other) so we cannot use std::unique_ptr here, and the intelligent pointers are recommended for this because of dynamical allocation (more convenient than C-pointers)
	 */

	std::vector<std::shared_ptr<Element>> elements_ptr;

	/**
	 * SALE TRES SALE BEURK
	 */

	bool const methodChapi;

	/**
	 * Describe how we are constructing the Beams
	 *
	 * - true  : The Beams are constructed using a physical source of Particle from the default Particle position by evolving a Particle a given number of times
	 * - false : The Beams are constructed by spreading out a given number of Particles on the ideal trajectory
	 */

	bool const beamFromParticle;
};

/**
 * Overloads ostream operator <<
 */

std::ostream& operator<< (std::ostream& stream, Accelerator const& a);

#endif
