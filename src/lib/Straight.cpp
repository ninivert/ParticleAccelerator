#include "src/include/bundle/Straight.bundle.h"

using namespace std;

/****************************************************************
 * Constructors
 ****************************************************************/

Straight::Straight(Vector3D const& posIn, Vector3D const& posOut, double const& radius, Renderer * engine_ptr)
: Element(posIn, posOut, radius, engine_ptr)
{}

Straight::Straight(Vector3D const& posIn, double const& length, Vector3D direction, double const& radius, Renderer * engine_ptr)
: Element(posIn, posIn + length * ~direction, radius, engine_ptr)
{}

/****************************************************************
 * Polymorphic copy for Accelerator
 ****************************************************************/

shared_ptr<Element> Straight::copy() const { return cloneThis(); }

shared_ptr<Straight> Straight::cloneThis() const {
	return shared_ptr<Straight>(new Straight(*this));
}

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
	if (engine_ptr == nullptr) ERROR(EXCEPTIONS::NULLPTR);
	engine_ptr->draw(*this);
}

void Straight::drawTo(Renderer * engine_ptr) const {
	if (engine_ptr == nullptr) ERROR(EXCEPTIONS::NULLPTR);
	engine_ptr->draw(*this);
}
