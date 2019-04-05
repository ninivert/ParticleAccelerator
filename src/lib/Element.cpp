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

double Element::getParticleProgress(Vector3D const& pos) const {
	return 1;
}


void Element::updatePointedElement(Particle & p) const {
	double dist(getParticleProgress(p.getPos()));

	if (dist < 0) {
		if (prev_ptr != nullptr) {
			p.setElement(prev_ptr);
		} else {
			EXCEPTIONS::OUTSIDE_ACCELERATOR;
		}
	} else if (dist > 1) {
		if (next_ptr != nullptr) {
			p.setElement(next_ptr);
		} else {
			EXCEPTIONS::OUTSIDE_ACCELERATOR;
		}
	}
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
