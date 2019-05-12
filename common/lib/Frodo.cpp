#include "include/bundle/Frodo.bundle.h"

using namespace std;

/****************************************************************
 * Constructors
 ****************************************************************/

Frodo::Frodo(Vector3D const& posIn, Vector3D const& posOut, double const& radius, double const& b, double const& straightLength, Renderer * engine_ptr)
: Straight(posIn, posOut, radius, engine_ptr), b(b), straightLength(straightLength),
  lensLength((posOut - posIn).norm() / 2 - straightLength),
  direction((posOut - posIn) / (posIn - posOut).norm()),
  intersect1(posIn + direction * (lensLength)),
  intersect2(posIn + direction * (lensLength + straightLength)),
  intersect3(posIn + direction * (2*lensLength + straightLength)),
  focalizer(posIn, intersect1, radius, b, engine_ptr),
  defocalizer(intersect2, intersect3, radius, -b, engine_ptr),
  firstStraight(intersect1, intersect2, radius, engine_ptr),
  lastStraight(intersect3, posOut, radius, engine_ptr)
{}

Frodo::Frodo(Vector3D const& posIn, double const& totalLength, Vector3D direction, double const& radius, double const& b, double const& straightLength, Renderer * engine_ptr)
: Straight(posIn, totalLength, direction, radius, engine_ptr), b(b), straightLength(straightLength),
  lensLength(totalLength / 2 - straightLength),
  direction(~direction),
  intersect1(posIn + direction * (lensLength)),
  intersect2(posIn + direction * (lensLength + straightLength)),
  intersect3(posIn + direction * (2*lensLength + straightLength)),
  focalizer(posIn, intersect1, radius, b, engine_ptr),
  defocalizer(intersect2, intersect3, radius, -b, engine_ptr),
  firstStraight(intersect1, intersect2, radius, engine_ptr),
  lastStraight(intersect3, posOut, radius, engine_ptr)
{}

/****************************************************************
 * Polymorphic copy for Accelerator
 ****************************************************************/

shared_ptr<Element> Frodo::copy() const { return cloneThis(); }

shared_ptr<Frodo> Frodo::cloneThis() const {
	return shared_ptr<Frodo>(new Frodo(*this));
}

/****************************************************************
 * Getter (virtual)
 ****************************************************************/

#include <iostream>

using namespace std;

Vector3D Frodo::getField(Vector3D const& pos, bool const& methodChapi) const {
	if (methodChapi) {
		if (focalizer.getParticleProgress(pos, methodChapi) < 1) {
			return focalizer.getField(pos);
		} else if (firstStraight.getParticleProgress(pos, methodChapi) < 1) {
			return Vector3D();
		} else if (defocalizer.getParticleProgress(pos, methodChapi) < 1) {
			return defocalizer.getField(pos);
		}
	} else {
		double totLength(2 * (lensLength + straightLength));
		double dist(getParticleProgress(pos, methodChapi) * totLength);	// Linear for straight

		if (dist >= 0 and dist <= lensLength) {
			return focalizer.getField(pos, methodChapi);
		} else if (dist >= lensLength + straightLength and dist <= 2 * lensLength + straightLength) {
			return defocalizer.getField(pos, methodChapi);
		}
	}
	return Vector3D();
}

/****************************************************************
 * Virtual methods
 ****************************************************************/

string Frodo::to_string() const {
	stringstream stream;
	stream << setprecision(STYLES::PRECISION);
	stream << left;

	stream
		<< STYLES::COLOR_CYAN
		<< "FODO"
		<< STYLES::NONE
		<< endl;

	// Display in, out, radius
	stream << Element::to_string();

	stream
		// Magnetic field
		<< setw(STYLES::PADDING_XSM) << ""
		<< setw(STYLES::PADDING_MD) << "Magnet. intens."
		<< setw(STYLES::PADDING_LG) << b
		<< " (" << UNITS::MAGNETIC_FIELD << ")"
		<< endl;
	stream
		// Straight length
		<< setw(STYLES::PADDING_XSM) << ""
		<< setw(STYLES::PADDING_MD) << "Straight length"
		<< setw(STYLES::PADDING_LG) << straightLength
		<< " (" << UNITS::DISTANCE << ")"
		<< endl;

	stream << endl;

	// Focalizer
	stream
		<< setw(STYLES::PADDING_XSM) << ""
		<< focalizer
		<< endl;

	// First straight
	stream
		<< setw(STYLES::PADDING_XSM) << ""
		<< firstStraight
		<< endl;

	// Defocalizer
	stream
		<< setw(STYLES::PADDING_XSM) << ""
		<< defocalizer
		<< endl;

	// Last straight
	stream
		<< setw(STYLES::PADDING_XSM) << ""
		<< lastStraight
		<< endl;

	return stream.str();
}

/****************************************************************
 * Drawing
 ****************************************************************/

void Frodo::draw(Renderer * engine_ptr) const {
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

void Frodo::drawElements() const {
	if (engine_ptr == nullptr) ERROR(EXCEPTIONS::NULLPTR);
	focalizer.draw(engine_ptr);
	defocalizer.draw(engine_ptr);
	firstStraight.draw(engine_ptr);
	lastStraight.draw(engine_ptr);
}
