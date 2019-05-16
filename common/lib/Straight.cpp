#include "include/bundle/Straight.bundle.h"

using namespace std;

/****************************************************************
 * Constructors
 ****************************************************************/

Straight::Straight(Vector3D const& posIn, Vector3D const& posOut, double radius, Renderer * engine_ptr)
: Element(posIn, posOut, radius, engine_ptr)
{}

Straight::Straight(Vector3D const& posIn, double length, Vector3D direction, double radius, Renderer * engine_ptr)
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

Vector3D Straight::getField(Vector3D const& pos, bool methodChapi) const {
	// We don't use arguments in this overidden function
	(void) pos;
	(void) methodChapi;
	return Vector3D(0, 0, 0);
}

Vector3D const Straight::getNormalDirection(Vector3D const& pos) const {
	// We don't use pos in this overidden function
	(void) pos;
	Vector3D d(getPosOut() - getPosIn());
	~d;
	return (Vector3D(0, 0, 1) ^ d);
}

double Straight::getParticleProgress(Vector3D const& pos, bool methodChapi) const {
	if (methodChapi) {
		bool const isInNextElement(Vector3D::tripleProduct(Vector3D(0, 0, 1), pos, getPosOut()) >= 0);
		if (isInNextElement) {
			return 2;
		} else {
			bool const isInPrevElement(Vector3D::tripleProduct(Vector3D(0, 0, 1), pos, getPosIn()) < 0);
			if (isInPrevElement) {
				return -2;
			} else {
				return 0;
			}
		}
	} else {
		Vector3D relativePos(pos - getPosIn());
		Vector3D directionElement(getPosOut() - getPosIn());
		return (relativePos * directionElement) / directionElement.normSquared();
	}
}

double Straight::getLength() const {
	return (getPosOut() - getPosIn()).norm();
}

Vector3D Straight::getPosAtProgress(double progress) const {
	if (progress < 0 or progress > 1) { ERROR(EXCEPTIONS::BAD_PROGRESS); }

	return ((getPosOut() - getPosIn()) * progress + getPosIn());
}

Vector3D Straight::getVelAtProgress(double progress, bool clockwise) const {
	if (progress < 0 or progress > 1) { ERROR(EXCEPTIONS::BAD_PROGRESS); }

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
