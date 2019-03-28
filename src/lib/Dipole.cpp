#include "src/include/bundle/Dipole.bundle.h"

using namespace std;

/****************************************************************
 * Constructors
 ****************************************************************/

Dipole::Dipole(Vector3D const& posIn, Vector3D const& posOut, double const& radius, double const& curvature, double const& B)
: Element(posIn, posOut, radius), curvature(curvature), B(B),
  posCenter (0.5 * (posOut + posIn) + 1 / (curvature) * sqrt(1 - curvature * curvature * (posOut - posIn).normSquared()/ 4.0) * ((posOut - posIn) ^ Vector3D(0, 0, 1)) / (posOut - posIn).norm())
{}

Dipole::Dipole(Vector3D const& posIn, Vector3D const& posOut, double const& radius, double const& curvature, Element & prev, double const& B)
: Element(posIn, posOut, radius, prev), curvature(curvature), B(B),
  posCenter (0.5 * (posOut + posIn) + 1 / (curvature) * sqrt(1 - curvature * curvature * (posOut - posIn).normSquared()/ 4.0) * ((posOut - posIn) ^ Vector3D(0, 0, 1)) / (posOut - posIn).norm())
{}

/****************************************************************
 * Getters (virtual)
 ****************************************************************/

Vector3D Dipole::getField(Vector3D const& pos) const { return Vector3D(0, 0, B); }

/****************************************************************
 * Setters
 ****************************************************************/

void Dipole::setB(double const& _B) { B = _B; }

/****************************************************************
 * Methods
 ****************************************************************/

string Dipole::to_string() const {
	stringstream stream;
	stream << "Dipole : " << endl;
	stream << Element::to_string();
	stream << setprecision(STYLES::PRECISION);
	stream << left;
	stream
		// Curvature
		<< setw(STYLES::PADDING_SM) << ""
		<< setw(STYLES::PADDING_MD) << "Curvature"
		<< setw(STYLES::PADDING_LG) << curvature
		<< " (" << UNITS::CURVATURE << ")"
		<< endl
		// Curvature center
		<< setw(STYLES::PADDING_SM) << ""
		<< setw(STYLES::PADDING_MD) << "Curv. center"
		<< setw(STYLES::PADDING_LG) << posCenter
		<< " (" << UNITS::DISTANCE << ")"
		<< endl
		// Magnetic field
		<< setw(STYLES::PADDING_SM) << ""
		<< setw(STYLES::PADDING_MD) << "Magnetic field"
		<< setw(STYLES::PADDING_LG) << getField(Vector3D(0, 0, 0))
		<< " (" << UNITS::DISTANCE << ")"
		<< endl;
	return stream.str();
}

bool Dipole::isOut(Particle const& p) const {
	Vector3D X(p.getPos() - posCenter);
	Vector3D u(X - p.getPos().getZ() * Vector3D(0, 0, 1));
	return ((X - 1 / abs(curvature) * u).norm() > getRadius());
}
