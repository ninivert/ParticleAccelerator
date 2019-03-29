#include "src/include/bundle/Quadrupole.bundle.h"

using namespace std;

/****************************************************************
 * Constructors
 ****************************************************************/

Quadrupole::Quadrupole(Vector3D const& posIn, Vector3D const& posOut, double const& radius, double const& b)
: Element(posIn, posOut, radius), b(b)
{}

Quadrupole::Quadrupole(Vector3D const& posIn, double const& length, Vector3D direction, double const& radius, double const& b)
: Element(posIn, posIn + length * ~direction, radius), b(b)
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

	return b * ((Maurice * u) * e3 + pos.getZ() * u);
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
		// Magnetic intensity b
		<< setw(STYLES::PADDING_XSM) << ""
		<< setw(STYLES::PADDING_MD) << "Magnet. intens."
		<< setw(STYLES::PADDING_LG) << b
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
