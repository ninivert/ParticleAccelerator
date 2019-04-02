#include "src/include/bundle/Straight.bundle.h"

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

/****************************************************************
 * Getter (virtual)
 ****************************************************************/

Vector3D Straight::getField(Vector3D const& pos) const { return Vector3D(0, 0, 0); }

/****************************************************************
 * Virtual methods
 ****************************************************************/

bool Straight::isInWall(Particle const& p) const {
	Vector3D X(p.getPos() - getPosIn());
	Vector3D d(getPosOut() - getPosIn());
	~d;
	return ((X - (X * d) * d).norm() > getRadius());
}

string Straight::to_string() const {
	stringstream stream;
	stream
		<< STYLES::COLOR_CYAN
		<< "Straight"
		<< STYLES::NONE
		<< endl;
	stream << Element::to_string();
	return stream.str();
}

/****************************************************************
 * Drawing
 ****************************************************************/

void Straight::draw() const {
	if (engine == nullptr) ERROR(EXCEPTIONS::NULLPTR);
	engine->draw(*this);
}

void Straight::drawTo(Renderer * engine) const {
	if (engine == nullptr) ERROR(EXCEPTIONS::NULLPTR);
	engine->draw(*this);
}
