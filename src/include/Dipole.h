#ifndef DIPOLE_H
#define DIPOLE_H

#pragma once

#include <cmath>
#include <iomanip>
#include <iostream>
#include <string>
#include <sstream>

#include "src/include/Element.h"
#include "src/include/Particle.h"
#include "src/include/Vector3D.h"
#include "src/globals.h"

/**
 * Dipole
 */

class Dipole : public Element {
public:
	// Constructors

	Dipole(Vector3D const& posIn, Vector3D const& posOut, double const& radius, double const& curvature);
	Dipole(Vector3D const& posIn, Vector3D const& posOut, double const& radius, double const& curvature, Element & prev);

	// Getters

	// By convention the magnetic field is alongside the direction of the third vector of the canonical basis
	Vector3D getField(Vector3D const& pos) const;

	// Setter

	void setB(double const& B);

	// Methods

	std::string to_string() const;

	bool isOut(Particle const& p) const;
	bool isInNext(Particle const& p) const;



private:
	double const curvature;
	Vector3D const posCenter;
	double B;					// Magnetic field
};

std::ostream& operator<< (std::ostream& stream, Element const& e);

#endif
