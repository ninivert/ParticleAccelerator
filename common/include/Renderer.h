#ifndef RENDERER_H
#define RENDERER_H

#pragma once

// Forward declaration
class Beam;
class Accelerator;
class Element;
class Dipole;
class Quadrupole;
class Straight;
class Frodo;
class Particle;
class Vector3D;

/**
 * Rendering engine called from each class respectively
 */

class Renderer {
public:

	/****************************************************************
	 * Constructors and destructors
	 ****************************************************************/

	/**
	 * Default constructor
	 */

	explicit Renderer();

	/**
	 * We don't want to copy a rendering engine
	 */

	Renderer(Renderer const& engine) = delete;

	/**
	 * Get the default destructor but allow it to be overridden
	 * by inheriting classes
	 */

	virtual ~Renderer() = default;

	/****************************************************************
	 * Operators
	 ****************************************************************/

	/**
	 * We don't want to copy/assign a rendering engine
	 */

	Renderer& operator = (Renderer const& engine) = delete;

	/****************************************************************
	 * Drawing methods
	 ****************************************************************/

	/**
	 * Draw a Beam
	 */

	virtual void draw(Beam const& beam) = 0;

	/**
	 * Draw an entire Accelerator
	 */

	virtual void draw(Accelerator const& acc) = 0;

	/**
	 * We do not want to draw an abstract type
	 */

	virtual void draw(Element const& elmt) = delete;

	/**
	 * Draw a Dipole element
	 */

	virtual void draw(Dipole const& dipole) = 0;

	/**
	 * Draw a Quadrupole element
	 */

	virtual void draw(Quadrupole const& quadrupole) = 0;

	/**
	 * Draw a Frodo element
	 */

	virtual void draw(Frodo const& frodo) = 0;

	/**
	 * Draw a Straight element
	 */

	virtual void draw(Straight const& straight) = 0;

	/**
	 * Draw a Particle
	 */

	virtual void draw(Particle const& particle) = 0;

	/**
	 * Draw a Vector3D (debugging purposes)
	 */

	virtual void draw(Vector3D const& vec) = 0;
};

#endif
