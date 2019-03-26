#ifndef QUADRUPOLE_H
#define QUADRUPOLE_H

#pragma once

#include "src/include/Element.h"
#include "src/include/Particle.h"
#include "src/include/Vector3D.h"
#include "src/globals.h"

/**
 * Quadrupole
 */

class Quadrupole : public Element {
public:

	virtual Vector3D getField(Vector3D const& pos) const override;
	virtual bool isOut(Particle const& p) const override;

	virtual std::string to_string() const;


private:


};


#endif
