#ifndef STRAIGHT_H
#define STRAIGHT_H

#pragma once

#include "src/include/Element.h"
#include "src/include/Particle.h"
#include "src/include/Vector3D.h"
#include "src/globals.h"

/**
 * Straight
 */

class Straight : public Element {
public:

	// Getter
	virtual Vector3D getField(Vector3D const& pos) const override;

	// Methods
	virtual bool isOut(Particle const& p) const override;
	virtual bool isInNext(Particle const& p) const override;

	virtual std::string to_string() const override;
};


#endif
