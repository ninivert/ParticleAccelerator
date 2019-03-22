#include "src/include/Dipole.h"

using namespace std;

/****************************************************************
 * Constructors
 ****************************************************************/

Dipole::Dipole(Vector3D const& posIn, Vector3D const& posOut, double const& radius, double const& curvature)
: Element(posIn, posOut, radius), curvature(curvature),
  posCenter (0.5 * (posOut + posIn) + 1 / curvature * sqrt(1 - (posOut - posIn).normSquared() * curvature * curvature / 4) * ((posOut - posIn) ^ Vector3D(0, 0, 1)))
{}


Dipole::Dipole(Vector3D const& posIn, Vector3D const& posOut, double const& radius, double const& curvature, Element & prev)
: Element(posIn, posOut, radius, prev), curvature(curvature)
{}


/****************************************************************
 * Setters
 ****************************************************************/

void Dipole::setB(double const& _B) { B = _B; }

string Dipole::to_string() const {
	stringstream stream;
	stream << Element::to_string();
	stream << setprecision(STYLES::PRECISION);
	stream << left;
	stream
		// Entry position
		<< setw(STYLES::PADDING_SM) << ""
		<< setw(STYLES::PADDING_MD) << "Curvature"s
		<< setw(STYLES::PADDING_LG) << curvature
		<< " ("s + UNITS::DISTANCE << "^-1)"s
		<< endl
		// Release position
		<< setw(STYLES::PADDING_SM) << ""
		<< setw(STYLES::PADDING_MD) << "Curvature center"s
		<< setw(STYLES::PADDING_LG) << posCenter
		<< " ("s + UNITS::DISTANCE << ")"s
		<< endl
		// Radius
		<< setw(STYLES::PADDING_SM) << ""
		<< setw(STYLES::PADDING_MD) << "Magnetic field"s
		<< setw(STYLES::PADDING_LG) << B
		<< " ("s + UNITS::DISTANCE << ")"s
		<< endl;
	return stream.str();
}

/****************************************************************
 * Operator overloading
 ****************************************************************/

ostream& operator << (ostream& stream, Dipole const& d) {
	return stream << d.to_string();
}
