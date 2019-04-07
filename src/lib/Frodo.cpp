#include "src/include/bundle/Frodo.bundle.h"

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
  firstStraight(intersect1, intersect2, radius, engine_ptr),
  defocalizer(intersect2, intersect3, radius, -b, engine_ptr),
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
  firstStraight(intersect1, intersect2, radius, engine_ptr),
  defocalizer(intersect2, intersect3, radius, -b, engine_ptr),
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

Vector3D Frodo::getField(Vector3D const& pos) const {
	if (not focalizer.isInNextElement(pos)) {
		return focalizer.getField(pos);
	} else if (firstStraight.isInNextElement(pos)) {
		return Vector3D();
	} else if (not defocalizer.isInNextElement(pos)) {
		return defocalizer.getField(pos);
	} else {
		return Vector3D();
	}

	// double dist(getParticleProgress(pos));	// Linear for straight
	// double length(2 * (lensLength + straightLength));
	// if (dist >= 0 and dist <= lensLength / length) {
	// 	return focalizer.getField(pos);
	// } else if (dist >= (lensLength + straightLength) / length and (dist <= 2 * lensLength + straightLength) / length) {
	// 	return defocalizer.getField(pos);
	// }

	// cout << "Particle is at " << l << endl;
	// cout << "Field is " << field << endl;

	// return Vector3D();
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

void Frodo::draw() const {
	if (engine_ptr == nullptr) ERROR(EXCEPTIONS::NULLPTR);
	engine_ptr->draw(*this);
}

void Frodo::drawTo(Renderer * engine_ptr) const {
	if (engine_ptr == nullptr) ERROR(EXCEPTIONS::NULLPTR);
	engine_ptr->draw(*this);
}
