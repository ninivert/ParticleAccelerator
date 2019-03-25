#include "src/include/Dipole.h"

using namespace std;

/****************************************************************
 * Constructors
 ****************************************************************/

Dipole::Dipole(Vector3D const& posIn, Vector3D const& posOut, double const& radius, double const& curvature)
: Element(posIn, posOut, radius), curvature(curvature),
  posCenter (0.5 * (posOut + posIn) + sqrt(1 / (curvature * curvature) - (posOut - posIn).normSquared()/ 4.0) * ((posOut - posIn) ^ Vector3D(0, 0, 1)) / (posOut - posIn).norm())
{}


Dipole::Dipole(Vector3D const& posIn, Vector3D const& posOut, double const& radius, double const& curvature, Element & prev)
: Element(posIn, posOut, radius, prev), curvature(curvature)
{}

/****************************************************************
 * Getters
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
		<< setw(STYLES::PADDING_MD) << "Curvature"s
		<< setw(STYLES::PADDING_LG) << curvature
		<< " ("s + UNITS::CURVATURE << ")"s
		<< endl
		// Curvature center
		<< setw(STYLES::PADDING_SM) << ""
		<< setw(STYLES::PADDING_MD) << "Curvature center"s
		<< setw(STYLES::PADDING_LG) << posCenter
		<< " ("s + UNITS::DISTANCE << ")"s
		<< endl
		// Magnetic field
		<< setw(STYLES::PADDING_SM) << ""
		<< setw(STYLES::PADDING_MD) << "Magnetic field"s
		<< setw(STYLES::PADDING_LG) << getField(Vector3D(0, 0, 0))
		<< " ("s + UNITS::DISTANCE << ")"s
		<< endl;
	return stream.str();
}

bool Dipole::isOut(Particle const& p) const {
	return ((p.getPos() - 1 / abs(curvature) * (p.getPos() - p.getPos().getZ() * Vector3D(0, 0, 1))).norm() > getRadius());
}

bool Dipole::isInNext(Particle const& p) const {
	return (Vector3D::tripleProduct(Vector3D(0, 0, 1), p.getPos(), getPosOut()) > 0);
}

/****************************************************************
 * Operator overloading
 ****************************************************************/

ostream& operator << (ostream& stream, Dipole const& d) {
	return stream << d.to_string();
}
