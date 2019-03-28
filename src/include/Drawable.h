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
	Renderer * engine;

public:
	/**
	 * Constructor takes a pointer to a rendering engine
	 *
	 * Default is nullptr because if the user does not bother, then that shouldn't yield an error
	 */

	Drawable(Renderer * engine = nullptr);

	/**
	 * Virtual method that is required to be overwritten
	 */

	virtual void draw() const = 0;
};

#endif
