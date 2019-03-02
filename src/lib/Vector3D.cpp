#include "src/include/Vector3D.h"

using namespace std;
using namespace GLOBALS;

/****************************************************************
 * Constructor
 ****************************************************************/

Vector3D::Vector3D(double const& _x, double const& _y, double const& _z) {
	x = _x;
	y = _y;
	z = _z;
}

Vector3D::Vector3D(Vector3D const& v) {
	x = v.getX();
	y = v.getY();
	z = v.getZ();
}

/****************************************************************
 * Getters
 ****************************************************************/

double Vector3D::getX() const { return x; }
double Vector3D::getY() const { return y; }
double Vector3D::getZ() const { return z; }

/****************************************************************
 * Setters
 ****************************************************************/

void Vector3D::setX(double const& _x) { x = _x; }
void Vector3D::setY(double const& _y) { y = _y; }
void Vector3D::setZ(double const& _z) { z = _z; }

/****************************************************************
 * Overloading
 ****************************************************************/

Vector3D Vector3D::operator + (Vector3D const& v) const {
	Vector3D res(*this);
	res.__add__(v);
	return res;
}

Vector3D Vector3D::operator - (Vector3D const& v) const {
	Vector3D res(*this);
	res.__sub__(v);
	return res;
}

Vector3D Vector3D::operator * (double const& lambda) const {
	Vector3D res(*this);
	res.__mult__(lambda);
	return res;
}

Vector3D Vector3D::operator / (double const& lambda) const {
	Vector3D res(*this);
	res.__div__(lambda);
	return res;
}

Vector3D Vector3D::operator ^ (Vector3D const& v) const {
	Vector3D res(*this);
	res.__cross__(v);
	return res;
}

double Vector3D::operator * (Vector3D const& v) const {
	Vector3D res(*this);
	return res.__dot__(v);
}

bool Vector3D::operator == (Vector3D const& v) const {
	return __eq__(v);
}

void Vector3D::operator = (Vector3D const& v) {
	x = v.getX();
	y = v.getY();
	z = v.getZ();
}

/****************************************************************
 * Methods
 ****************************************************************/

string Vector3D::stringify() const {
	return "("s + to_string(x) + ", "s + to_string(y) + ", "s + to_string(z) + ")"s;
}

double Vector3D::norm() const {
	return sqrt(normSquared());
}

double Vector3D::normSquared() const {
	return pow(x, 2) + pow(y, 2) + pow(z, 2);
}

void Vector3D::normalize() {
	double n = norm();
	x /= n;
	y /= n;
	z /= n;
}

/****************************************************************
 * Static methods
 ****************************************************************/

double Vector3D::tripleProduct(Vector3D const& v1, Vector3D const& v2, Vector3D const& v3) {
	return v1 * (v2 ^ v3);
}

/****************************************************************
 * Overloding methods
 ****************************************************************/

void Vector3D::__add__(Vector3D const& v) {
	x += v.getX();
	y += v.getY();
	z += v.getZ();
}

void Vector3D::__sub__(Vector3D const& v) {
	x -= v.getX();
	y -= v.getY();
	z -= v.getZ();
}

void Vector3D::__mult__(double const& lambda) {
	x *= lambda;
	y *= lambda;
	z *= lambda;
}

void Vector3D::__div__(double const& lambda) {
	x /= lambda;
	y /= lambda;
	z /= lambda;
}

void Vector3D::__cross__(Vector3D const& v) {
	double _x = y*v.getZ() - z*v.getY();
	double _y = z*v.getX() - x*v.getZ();
	double _z = x*v.getY() - y*v.getX();
	x = _x;
	y = _y;
	z = _z;
}

double Vector3D::__dot__(Vector3D const& v) const {
	return x*v.getX() + y*v.getY() + z*v.getZ();
}

bool Vector3D::__eq__(Vector3D const& v) const {
	bool a = abs(x - v.getX()) < EPSILON;
	bool b = abs(y - v.getY()) < EPSILON;
	bool c = abs(z - v.getZ()) < EPSILON;
	return a and b and c;
}

/****************************************************************
 * Cout overloading
 ****************************************************************/

ostream& operator<< (ostream& stream, Vector3D const& v) {
	stream << v.stringify();
	return stream;
}