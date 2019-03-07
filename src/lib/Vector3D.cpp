#include "src/include/Vector3D.h"

using namespace std;
using namespace GLOBALS;

/****************************************************************
 * Constructors
 ****************************************************************/

Vector3D::Vector3D()
	: Vector3D(0.0, 0.0, 0.0)
	{}

Vector3D::Vector3D(double const& _x, double const& _y, double const& _z)
	: x(_x), y(_y), z(_z)
	{}

Vector3D::Vector3D(Vector3D const& v)
	: x(v.x), y(v.y), z(v.z)
	{}

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
 * Overloading operator
 ****************************************************************/

Vector3D Vector3D::operator + (Vector3D const& v) const {
	Vector3D res(*this);
	res.__add__(v);
	return res;
}

Vector3D& Vector3D::operator += (Vector3D const& v) {
	this->__add__(v);
	return (*this);
}

Vector3D Vector3D::operator - (Vector3D const& v) const {
	Vector3D res(*this);
	res.__sub__(v);
	return res;
}

Vector3D& Vector3D::operator -= (Vector3D const& v) {
	__sub__(v);
	return (*this);
}

Vector3D Vector3D::operator * (double const& lambda) const {
	Vector3D res(*this);
	res.__mult__(lambda);
	return res;
}

Vector3D& Vector3D::operator *= (double const& lambda) {
	__mult__(lambda);
	return (*this);
}

Vector3D Vector3D::operator / (double const& lambda) const {
	Vector3D res(*this);
	res.__div__(lambda);
	return res;
}

Vector3D& Vector3D::operator /= (double const& lambda) {
	__div__(lambda);
	return (*this);
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

Vector3D& Vector3D::operator ~ () {
	__normalize__();
	return (*this);
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
	return "("s + to_string(getX()) + ", "s + to_string(getY()) + ", "s + to_string(getZ()) + ")"s;
}

double Vector3D::norm() const {
	return sqrt(normSquared());
}

double Vector3D::normSquared() const {
	return pow(getX(), 2) + pow(getY(), 2) + pow(getZ(), 2);
}

Vector3D& Vector3D::rotate(Vector3D axis, double const& alpha ) {
	~axis;
	(*this) *= cos(alpha);
	(*this) += (axis ^ (*this)) * sin(alpha) + (axis * ((*this) * axis)) * (1 - cos(alpha));
	return (*this);
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
	double _x = getY() * v.getZ() - getZ() * v.getY();
	double _y = getZ() * v.getX() - getX() * v.getZ();
	double _z = getX() * v.getY() - getY() * v.getX();
	x = _x;
	y = _y;
	z = _z;
}

double Vector3D::__dot__(Vector3D const& v) const {
	return getX() * v.getX() + getY() * v.getY() + getZ() * v.getZ();
}

void Vector3D::__normalize__() {
	double n = norm();
	x /= n;
	y /= n;
	z /= n;
}

bool Vector3D::__eq__(Vector3D const& v) const {
	bool a = abs(getX() - v.getX()) < EPSILON;
	bool b = abs(getY() - v.getY()) < EPSILON;
	bool c = abs(getZ() - v.getZ()) < EPSILON;
	return a and b and c;
}

/****************************************************************
 * Cout overloading
 ****************************************************************/

ostream& operator<< (ostream& stream, Vector3D const& v) {
	stream << v.stringify();
	return stream;
}
