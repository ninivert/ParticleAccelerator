#include "src/include/bundle/Element.bundle.h"

using namespace std;

/****************************************************************
 * Constructors
 ****************************************************************/

Element::Element(Vector3D const& posIn, Vector3D const& posOut, double const& radius, Renderer * engine_ptr)
: Drawable(engine_ptr), posIn(posIn), posOut(posOut), radius(radius), next_ptr(nullptr), prev_ptr(nullptr)
{
	double orientation = Vector3D::tripleProduct(Vector3D(0, 0, 1), posIn, posOut);
	if (abs(orientation) < GLOBALS::DELTA) {
		ERROR(EXCEPTIONS::BAD_ORIENTATION);
	} else if (orientation > 0) {
		ERROR(EXCEPTIONS::BAD_DIRECTION);
		// Vector3D tmp(this->posIn);
		// this->posIn = this->posOut;
		// this->posOut = tmp;
	}
}

/****************************************************************
 * Destructor
 ****************************************************************/

Element::~Element() {
	if (next_ptr != nullptr) {
		next_ptr->prev_ptr = nullptr;
		next_ptr = nullptr;
	}

	if (prev_ptr != nullptr) {
		prev_ptr->next_ptr = nullptr;
		prev_ptr = nullptr;
	}
}

/****************************************************************
 * Getters
 ****************************************************************/

Vector3D Element::getPosIn() const { return posIn; }
Vector3D Element::getPosOut() const { return posOut; }
double Element::getRadius() const { return radius; }

/****************************************************************
 * Methods
 ****************************************************************/

void Element::linkNext(Element & _next) {
	next_ptr = &_next;
	_next.prev_ptr = this;
}

bool Element::isInNextElement(Particle const& p) const {
	return (Vector3D::tripleProduct(Vector3D(0, 0, 1), p.getPos(), getPosOut()) > 0);
}

void Element::updatePointedElement(Particle & p) const {
	// if both pointers are nullptr return without changing anything by CONVENTION
	if (next_ptr == nullptr and prev_ptr == nullptr) { return; }
	if (next_ptr == nullptr) {
		p.setElement(prev_ptr);
		return;
	}
	if (prev_ptr == nullptr) {
		p.setElement(next_ptr);
		return;
	}

	// now the 2 pointers are pointing to Element
	// which one are we closer to ?

	double diffNext((p.getPos() - next_ptr->getPosIn()).normSquared());
	double diffPrev((p.getPos() - prev_ptr->getPosOut()).normSquared());

	if (diffNext < diffPrev) {
		p.setElement(next_ptr);
	} else if (diffNext > diffPrev){
		p.setElement(prev_ptr);
	}

	// If same distance we will return without changing anything by CONVENTION
	// but it should never happen normaly
}

string Element::to_string() const {
	stringstream stream;
	stream << setprecision(STYLES::PRECISION);
	stream << left;
	stream
		// // Adress
		// << setw(STYLES::PADDING_XSM) << ""
		// << setw(STYLES::PADDING_MD) << "Adress"
		// << setw(STYLES::PADDING_LG) << this
		// << endl
		// Entry position
		<< setw(STYLES::PADDING_XSM) << ""
		<< setw(STYLES::PADDING_MD) << "Input pos"
		<< setw(STYLES::PADDING_LG) << getPosIn()
		<< " (" << UNITS::DISTANCE << ")"
		<< endl
		// Release position
		<< setw(STYLES::PADDING_XSM) << ""
		<< setw(STYLES::PADDING_MD) << "Release pos"
		<< setw(STYLES::PADDING_LG) << getPosOut()
		<< " (" << UNITS::DISTANCE << ")"
		<< endl
		// Radius
		<< setw(STYLES::PADDING_XSM) << ""
		<< setw(STYLES::PADDING_MD) << "Radius"
		<< setw(STYLES::PADDING_LG) << getRadius()
		<< " (" << UNITS::DISTANCE << ")"
		<< endl;

	return stream.str();
}

/****************************************************************
 * Operator overloading
 ****************************************************************/

ostream& operator << (ostream& stream, Element const& e) {
	return stream << e.to_string();
}
