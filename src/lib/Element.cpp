#include "src/include/bundle/Element.bundle.h"

using namespace std;

/****************************************************************
 * Constructors
 ****************************************************************/

Element::Element(Vector3D const& posIn, Vector3D const& posOut, double const& radius)
: posIn(posIn), posOut(posOut), radius(radius), next(nullptr), prev(nullptr)
{
	double orientation = Vector3D::tripleProduct(Vector3D(0, 0, 1), posIn, posOut);
	if (abs(orientation) < GLOBALS::DELTA) {
		ERROR(EXCEPTIONS::BAD_ORIENTATION);
	} else if (orientation > 0) {
		Vector3D tmp(this->posIn);
		this->posIn = this->posOut;
		this->posOut = tmp;
	}
}

Element::Element(Vector3D const& posIn, Vector3D const& posOut, double const& radius, Element & prev)
: posIn(posIn), posOut(posOut), radius(radius), next(nullptr), prev(&prev)
{
	double orientation = Vector3D::tripleProduct(Vector3D(0, 0, 1), posIn, posOut);
	if (abs(orientation) < GLOBALS::DELTA) {
		ERROR(EXCEPTIONS::BAD_ORIENTATION);
	} else if (orientation > 0) {
		Vector3D tmp(this->posIn);
		this->posIn = this->posOut;
		this->posOut = tmp;
	}

	prev.linkNext(*this);
}

/****************************************************************
 * Destructor
 ****************************************************************/

Element::~Element() {
	if (next != nullptr) {
		next->prev = nullptr;
		next = nullptr;
	}

	if (prev != nullptr) {
		prev->next = nullptr;
		prev = nullptr;
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
	next = &_next;
	_next.prev = this;
}

bool Element::isInNextElement(Particle const& p) const {
	return (Vector3D::tripleProduct(Vector3D(0, 0, 1), p.getPos(), getPosOut()) > 0);
}

void Element::updatePointedElement(Particle & p) const {
	// if both pointers are nullptr return without changing anything by CONVENTION
	if (next == nullptr and prev == nullptr) { return; }
	if (next == nullptr) {
		p.setElement(prev);
		return;
	}
	if (prev == nullptr) {
		p.setElement(next);
		return;
	}

	// now the 2 pointers are pointing to Element
	double diffNext((p.getPos() - next->getPosIn()).normSquared());
	double diffPrev((p.getPos() - prev->getPosOut()).normSquared());

	if (diffNext < diffPrev) {
		p.setElement(next);
	} else if (diffNext > diffPrev){
		p.setElement(prev);
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
