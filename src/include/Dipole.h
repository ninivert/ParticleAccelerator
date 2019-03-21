#ifndef DIPOLE_H
#define DIPOLE_H

#pragma once

#include "src/include/Element.h"
#include "src/include/Particle.h"
#include "src/include/Vector3D.h"
#include "src/globals.h"

/**
 * Dipole
 */

class Dipole : public Element {
public:
	Dipole(Vector3D const& posIn, Vector3D const& posOut, double const& radius, double const& B);

private:
	double const curvature;
	Vector3D const posCenter;
	double const B; // Magnetic field
};


#endif
