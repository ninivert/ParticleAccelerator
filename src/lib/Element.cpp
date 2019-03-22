#include "src/include/Element.h"

using namespace std;

/****************************************************************
 * Constructors
 ****************************************************************/

Element::Element(Vector3D const& posIn, Vector3D const& posOut, double const& radius)
: posIn(posIn), posOut(posOut), radius(radius), next(nullptr), prev(nullptr)
{}

Element::Element(Vector3D const& posIn, Vector3D const& posOut, double const& radius, Element & prev)
: posIn(posIn), posOut(posOut), radius(radius), next(nullptr), prev(&prev)
{
	prev.setNext(*this);
}

/****************************************************************
 * Getters
 ****************************************************************/

Vector3D Element::getPosIn() const { return posIn; }
Vector3D Element::getPosOut() const { return posOut; }
double Element::getRadius() const { return radius; }

/****************************************************************
 * Setters
 ****************************************************************/

void Element::setNext(Element & _next) {
	next = &_next;
	_next.prev = this;
}

/****************************************************************
 * Methods
 ****************************************************************/

string Element::to_string() const {
	stringstream stream;
	stream << setprecision(STYLES::PRECISION);
	stream << left;
	stream
		// Entry position
		<< setw(STYLES::PADDING_SM) << ""
		<< setw(STYLES::PADDING_MD) << "Entry position"s
		<< setw(STYLES::PADDING_LG) << getPosIn()
		<< " ("s + UNITS::DISTANCE << ")"s
		<< endl
		// Release position
		<< setw(STYLES::PADDING_SM) << ""
		<< setw(STYLES::PADDING_MD) << "Release position"s
		<< setw(STYLES::PADDING_LG) << getPosOut()
		<< " ("s + UNITS::DISTANCE << ")"s
		<< endl
		// Radius
		<< setw(STYLES::PADDING_SM) << ""
		<< setw(STYLES::PADDING_MD) << "Radius"s
		<< setw(STYLES::PADDING_LG) << getRadius()
		<< " ("s + UNITS::DISTANCE << ")"s
		<< endl;
	return stream.str();
}

/****************************************************************
 * Operator overloading
 ****************************************************************/

ostream& operator << (ostream& stream, Element const& e) {
	return stream << e.to_string();
}