#include "src/include/Vector3D.h"
#include "src/include/Particle.h"
#include "src/include/Element.h"
#include "src/include/Straight.h"

using namespace std;

/****************************************************************
 * Constructors
 ****************************************************************/

Straight::Straight(Vector3D const& posIn, Vector3D const& posOut, double const& radius)
: Element(posIn, posOut, radius)
{}

Straight::Straight(Vector3D const& posIn, double const& length, Vector3D direction, double const& radius)
: Element(posIn, posIn + length * ~direction, radius)
{}

Straight::Straight(Vector3D const& posIn, Vector3D const& posOut, double const& radius, Element & prev)
: Element(posIn, posOut, radius, prev)
{}

Straight::Straight(Vector3D const& posIn, double const& length, Vector3D direction, double const& radius, Element & prev)
: Element(posIn, posIn + length * ~direction, radius, prev)
{}

/****************************************************************
 * Getter (virtual)
 ****************************************************************/

Vector3D Straight::getField(Vector3D const& pos) const { return Vector3D(0, 0, 0); }

/****************************************************************
 * Virtual methods
 ****************************************************************/

bool Straight::isOut(Particle const& p) const {
	Vector3D X(p.getPos() - getPosIn());
	Vector3D d(getPosOut() - getPosIn());
	~d;
	return ((X - (X * d) * d).norm() > getRadius());
}

string Straight::to_string() const {
	stringstream stream;
	stream << "Straight : " << endl;
	stream << Element::to_string();
	return stream.str();
}
