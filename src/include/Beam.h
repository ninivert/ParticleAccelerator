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
class Drawable;
class Renderer;

#include "src/globals.h"
#include "src/exceptions.h"


class Beam : public Drawable {
public:
	/****************************************************************
	 * Constructors and destructors
	 ****************************************************************/

	/**
	 * Constructor
	 */

	Beam();

	/**
	 * Destructor: we are storing pointers (smart pointers but ok)
	 */

	~Beam();

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
	 * Mean energy of the `Particle`s in the Beam
	 */

	double getMeanEnergy() const;

	/**
	 * Get the emittance epsilon_r
	 */

	double getEmittanceR() const;

	/**
	 * Get the emittance epsilon_z
	 */

	double getEmittanceZ() const;

	Vector3D getEllipsePhaseCoef() const;

	/****************************************************************
	 * Methods
	 ****************************************************************/

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

private:

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

	Particle defaultParticle;

	/**
	 * Number of Particles in the Beam
	 */

	size_t particleCount;

	/**
	 * Scaling factor for the macroparticles
	 */

	double lambda;

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
