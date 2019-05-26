#ifndef DRAWABLE_H
#define DRAWABLE_H

#pragma once

// Forward declaration
class Renderer;

/**
 * Simple class to simulate double double dispatching in C++
 *
 * TODO: add new constructors for Drawable classes
 */

class Drawable {
protected:

	Renderer * engine_ptr;

public:

	/****************************************************************
	 * Constructors and destructors
	 ****************************************************************/

	/**
	 * Constructor takes a pointer to a rendering engine
	 *
	 * Default is nullptr because if the user does not bother, then that shouldn't yield an error
	 */

	explicit Drawable(Renderer * engine_ptr = nullptr);

	/**
	 * We need to explicitly specify the virtual destructor
	 * in order for all inherited classes to be deconstructed correctly
	 *
	 * Get the default destructor but allow it to be overridden
	 * by inheriting classes
	 */

	virtual ~Drawable() = default;

	/****************************************************************
	 * Virtual methods
	 ****************************************************************/

	/**
	 * Virtual method that is required to be overwritten
	 */

	virtual void draw(Renderer * engine_ptr = nullptr) const = 0;
};

#endif
