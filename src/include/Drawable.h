#ifndef DRAWABLE_H
#define DRAWABLE_H

#pragma once

// We are not including the full header because we only need the type
// Including the full header would give a circular dependency from HELL
#include "src/include/fwd/Renderer.fwd.h"

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
