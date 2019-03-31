#ifndef TEXTRENDERER_H
#define TEXTRENDERER_H

#pragma once

// Forward declaration
class Accelerator;
class Element;
class Dipole;
class Quadrupole;
class Straight;
class Particle;
class Vector3D;
class Renderer;

class TextRenderer : public Renderer {
public:

	/****************************************************************
	 * Constructors and destructors
	 ****************************************************************/

	TextRenderer();

	/**
	 * Get the default destructor but allow it to be overridden
	 * by inheriting classes
	 */

	virtual ~TextRenderer() override;

	/**
	 * We don't want to copy a rendering engine
	 */

	TextRenderer(TextRenderer const& engine) = delete;


	/****************************************************************
	 * Operators
	 ****************************************************************/

	/**
	 * We don't want to copy/assign a rendering engine
	 */

	TextRenderer& operator = (TextRenderer const& engine) = delete;

	/****************************************************************
	 * Drawing methods
	 ****************************************************************/

	/**
	 * Draw an entire Accelerator
	 */

	virtual void draw(Accelerator const& acc) override;

	/**
	 * Draw an element. This method is not overridden in Element.cpp
	 * thus the Element remains abstract.
	 */

	virtual void draw(Element const& elmt) override;

	/**
	 * Draw a Dipole element
	 */

	virtual void draw(Dipole const& dipole) override;

	/**
	 * Draw a Quadrupole element
	 */

	virtual void draw(Quadrupole const& quadrupole) override;

	/**
	 * Draw a Straight element
	 */

	virtual void draw(Straight const& straight) override;

	/**
	 * Draw a Particle
	 */

	virtual void draw(Particle const& particle) override;

	/**
	 * Draw a Vector3D (debugging purposes)
	 */

	virtual void draw(Vector3D const& vec) override;
};

#endif
