#ifndef BEAM_H
#define BEAM_H

#include <vector>
#include <cmath>
#include <memory>
#include <string>
#include <sstream>
#include <iomanip>

// Forward declarations
class Vector3D;
class Particle;
class Element;
class Accelerator;
class Drawable;
class Renderer;

#include "globals.h"
#include "exceptions.h"


class Beam : public Drawable {
public:

	/****************************************************************
	 * Constructors
	 ****************************************************************/

	/**
	 * Constructor
	 *
	 * - `Particle defaultParticle`: represents the default settings
	 * - `size_t particleCount`: number of total particles
	 * - `double lambda`: scaling factor for the macroparticles (> 1)
	 */

	Beam(Particle const& defaultParticle, size_t const& particleCount, double lambda, Accelerator const& acc, Renderer * engine = nullptr);

	/**
	 * Constructor with only one particle
	 *
	 * - `Particle defaultParticle`: represents the default settings
	 */

	Beam(Particle const& defaultParticle, Renderer * engine = nullptr);

	/****************************************************************
	 * Destructor
	 ****************************************************************/

	/**
	 * Destructor: we are storing pointers (smart pointers but ok)
	 */

	~Beam();

	/****************************************************************
	 * Copy constructor and operator =
	 ****************************************************************/

	/**
	 * Delete copy constructor
	 *
	 * - To avoid to copy a Beam (big object)
	 * - To forbid the transmission of pointers on `Particle` (std::unique_ptr)
	 */

	Beam(Beam const& b) = delete;

	/**
	 * Delete assignment operator
	 *
	 * - To avoid to copy a Beam (big object)
	 * - To forbid the transmission of pointers on `Particle` (std::unique_ptr)
	 */

	Beam& operator = (Beam const&) = delete;

	/****************************************************************
	 * Getters
	 ****************************************************************/

	/**
	 * Mean energy of the `Particle`s in the Beam in GeV
	 */

	double getMeanEnergy() const;

	/**
	 * Returns the Gamma coefficient of the Particle at index part
	 */

	double getGamma(size_t part) const;

	/**
	 * Returns the position of the Particle at index part
	 */

	Vector3D getPos(size_t part) const;

	/**
	 * Returns the charge of a Particle in the Beam
	 */

	double getCharge() const;

	/**
	 * Get the emittance epsilon_r along the horizontal axis
	 */

	double getEmittanceR() const;

	/**
	 * Get the emittance epsilon_z along the vertical axis
	 */

	double getEmittanceZ() const;

	/**
	 * Get the emittance coefficients along the horizontal axis
	 *
	 * X-coord : A11_R
	 * Z-coord : A12_R
	 * Y-coord : A22_R
	 */

	Vector3D const getEllipsePhaseCoefR() const;

	/**
	 * Get the emittance coefficients along the vertical axis
	 *
	 * X-coord : A11_Z
	 * Y-coord : A22_Z
	 * Z-coord : A12_Z
	 */

	Vector3D const getEllipsePhaseCoefZ() const;

	/****************************************************************
	 * Methods
	 ****************************************************************/

	/**
	 * Integrates the movement equations over a time step `dt`, which defaults to `GLOBALS::DT(1e-11)`.
	 *
	 * We need the methodChapi for the getField (if it's a FODO element)
	 *
	 * If `dt` is null (aka inferior to GLOBALS::DELTA_DIV0), then this doesn't do anything
	 */

	void step(double dt = GLOBALS::DT, bool methodChapi = false);

	/**
	 * Returns true if there is no Particle left in the Beam
	 *
	 * Returns false otherwise
	 */

	bool noParticle() const;

	/**
	 * Calls Element::updatePointedElement() (with polymorphism) on all particles of the Beam
	 */

	void updatePointedElement(bool methodChapi = false) const;

	/**
	 * Modifies the associatedProgress by updating the progress for each Particle which is still in the Beam (clears the vector and update afterwards to adapt to the loss of Particles)
	 */

	void updateProgresses(std::vector<double> & associatedProgress, Accelerator const& acc) const;

	/**
	 * Exerts the force to the particle at index part (add the force using Particle::exertForce(Vector3D const& force))
	 */

	void exertForce(Vector3D const& force, size_t part);

	/**
	 * Returns a string representation of the Beam
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
	 * Draw particles
	 */

	void drawParticles() const;

private:

	/****************************************************************
	 * Private methods
	 ****************************************************************/

	/**
	 * Returns the means necessary for the getEmittanceR and getEllipsePhaseCoefR
	 *
	 * - X-coor : <r²>
	 * - Y-coor : <vr²>
	 * - Z-coor : <r * vr>
	 */

	Vector3D const getRMeans() const;

	/**
	 * Returns the means necessary for the getEmittanceR and getEllipsePhaseCoefR
	 *
	 * - X-coor : <z²>
	 * - Y-coor : <vz²>
	 * - Z-coor : <z * vz>
	 */

	Vector3D const getZMeans() const;

	/**
	 * Adds the interaction forces to each Particle
	 */

	// void exertInteractions();

	/**
	 * Remove the Particle of the Beam that are out of the Accelerator
	 *
	 * Private: this method should only be used internally in Beam::step()
	 */

	void clearDeadParticles();

	/****************************************************************
	 * Attributes
	 ****************************************************************/

	/**
	 * Default particle indicates the default
	 *
	 * - charge
	 * - mass
	 * - start position
	 * - start velocity
	 * - initial Element
	 *
	 * for each particle in the Beam
	 */

	std::unique_ptr<Particle> defaultParticle_ptr;

	/**
	 * Number of Particles in the Beam
	 */

	size_t const particleCount;

	/**
	 * Scaling factor for the macroparticles
	 */

	double const lambda;

	/**
	 * Collection of the stored Particles of the same "nature"
	 */

	std::vector<std::unique_ptr<Particle>> particles_ptr;
};

/****************************************************************
 * Cout overloading
 ****************************************************************/

/**
 * Streams the `Particle::to_string()` representation to a given stream
 */

std::ostream& operator << (std::ostream& stream, Beam const& beam);

#endif
