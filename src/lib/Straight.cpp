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

Vector3D Straight::getField(Vector3D const& pos, bool const& methodChapi) const { return Vector3D(0, 0, 0); }

double Straight::getLength() const {
	return (getPosOut() - getPosIn()).norm();
}

Vector3D Straight::getPosAtProgress(double const& progress) const {
	return ((getPosOut() - getPosIn()) * progress + getPosIn());
}

Vector3D Straight::getVelAtProgress(double const& progress, bool const& clockwise) const {
	Vector3D direction(getPosOut() - getPosIn());
	~direction;
	if (not clockwise) {
		direction *= -1;
	}
	return direction;
}

/****************************************************************
 * Virtual methods
 ****************************************************************/

bool Straight::isInWall(Particle const& p) const {
	Vector3D X(p.getPos() - getPosIn());
	Vector3D d(getPosOut() - getPosIn());
	~d;
	return ((X - (X * d) * d).norm() > getRadius());
}

double Straight::getParticleProgress(Vector3D const& pos, bool const& methodChapi) const {
	if (methodChapi) {
		bool const isInNextElement(Vector3D::tripleProduct(Vector3D(0, 0, 1), pos, getPosOut()) >= 0);
		if (isInNextElement) {
			return 2;
		} else {
			return 0.5;
		}
	} else {
		Vector3D relativePos(pos - getPosIn());
		Vector3D directionElement(getPosOut() - getPosIn());
		return (relativePos * directionElement) / directionElement.normSquared();
	}
}

Vector3D const Straight::getNormalDirection(Vector3D const& pos) const {
	Vector3D d(getPosOut() - getPosIn());
	~d;
	return (Vector3D(0, 0, 1) ^ d);
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

void Straight::draw(Renderer * engine_ptr) const {
	// No engine specified, try to substitute it ?
	if (engine_ptr == nullptr) {
		// Do we have another engine ?
		if (this->engine_ptr == nullptr) {
			ERROR(EXCEPTIONS::NULLPTR);
		} else {
			engine_ptr = this->engine_ptr;
		}
	}
	engine_ptr->draw(*this);
}
