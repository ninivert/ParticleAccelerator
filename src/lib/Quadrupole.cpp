#include "src/include/bundle/Quadrupole.bundle.h"

using namespace std;

/****************************************************************
 * Constructors
 ****************************************************************/

Quadrupole::Quadrupole(Vector3D const& posIn, Vector3D const& posOut, double const& radius, double const& B)
: Element(posIn, posOut, radius), B(B)
{}

Quadrupole::Quadrupole(Vector3D const& posIn, double const& length, Vector3D direction, double const& radius, double const& B)
: Element(posIn, posIn + length * ~direction, radius), B(B)
{}

Quadrupole::Quadrupole(Vector3D const& posIn, Vector3D const& posOut, double const& radius, double const& B, Element & prev)
: Element(posIn, posOut, radius, prev), B(B)
{}

Quadrupole::Quadrupole(Vector3D const& posIn, double const& length, Vector3D direction, double const& radius, double const& B, Element & prev)
: Element(posIn, posIn + length * ~direction, radius, prev), B(B)
{}

/****************************************************************
 * Getter (virtual)
 ****************************************************************/

Vector3D Quadrupole::getField(Vector3D const& pos) const {
	Vector3D Jean_Albert(pos - getPosIn());				// X
	Vector3D Gertrude(getPosOut() - getPosIn());		// d
	~Gertrude;
	Vector3D Maurice(Jean_Albert - (Jean_Albert * Gertrude) * Gertrude); // y

	Vector3D e3(0, 0, 1);
	Vector3D u(e3 ^ Gertrude);

	return B * ((Maurice * u) * e3 + pos.getZ() * u);
}

/****************************************************************
 * Virtual methods
 ****************************************************************/

bool Quadrupole::isInWall(Particle const& p) const {
	Vector3D X(p.getPos() - getPosIn());
	Vector3D d(getPosOut() - getPosIn());
	~d;
	return ((X - (X * d) * d).norm() > getRadius());
}

string Quadrupole::to_string() const {
	stringstream stream;
	stream << "Quadrupole : " << endl;
	stream << Element::to_string();
	stream << setprecision(STYLES::PRECISION);
	stream << left;
	stream
		// Magnetic intensity B
		<< setw(STYLES::PADDING_SM) << ""
		<< setw(STYLES::PADDING_MD) << "Magnet. intens."
		<< setw(STYLES::PADDING_LG) << B
		<< " (" << UNITS::MAGNETIC_FIELD << ")"
		<< endl;
	return stream.str();
}

/****************************************************************
 * Drawing
 ****************************************************************/

void Quadrupole::draw() const {
	engine->draw(*this);
}
