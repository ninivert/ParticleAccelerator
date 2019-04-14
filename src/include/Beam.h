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
	 *
	 * - `Particle defaultParticle`: represents the default settings
	 * - `size_t particleCount`: number of total particles
	 * - `double lambda`: scaling factor for the macroparticles (> 1)
	 */

	Beam(Particle const& defaultParticle, size_t const& particleCount, double const& lambda = 1);

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
	 * Mean energy of the `Particle`s in the Beam in GeV
	 */

	double getMeanEnergy() const;

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
