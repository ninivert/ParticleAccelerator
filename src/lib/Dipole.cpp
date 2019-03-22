#include "src/include/Dipole.h"

/****************************************************************
 * Constructors
 ****************************************************************/

Dipole::Dipole(Vector3D const& posIn, Vector3D const& posOut, double const& radius, double const& curvature)
: Element(posIn, posOut, radius), curvature(curvature)
{}


Dipole::Dipole(Vector3D const& posIn, Vector3D const& posOut, double const& radius, double const& curvature, Element & prev)
: Element(posIn, posOut, radius, prev), curvature(curvature)
{}


/****************************************************************
 * Setters
 ****************************************************************/

void Dipole::setB(double const& _B) { B = _B; }
