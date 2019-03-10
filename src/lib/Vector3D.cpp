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
 * Internal overloading operator
 ****************************************************************/

Vector3D& Vector3D::operator += (Vector3D const& v) {
	x += v.getX();
	y += v.getY();
	z += v.getZ();
	return *this;
}

Vector3D& Vector3D::operator -= (Vector3D const& v) {
	x -= v.getX();
	y -= v.getY();
	z -= v.getZ();
	return *this;
}

Vector3D& Vector3D::operator ^= (Vector3D const& v) {
	double _x = getY() * v.getZ() - getZ() * v.getY();
	double _y = getZ() * v.getX() - getX() * v.getZ();
	double _z = getX() * v.getY() - getY() * v.getX();
	x = _x;
	y = _y;
	z = _z;
	return *this;
}

Vector3D& Vector3D::operator *= (double const& lambda) {
	x *= lambda;
	y *= lambda;
	z *= lambda;
	return *this;
}

Vector3D& Vector3D::operator /= (double const& lambda) {
	x /= lambda;
	y /= lambda;
	z /= lambda;
	return *this;
}

Vector3D& Vector3D::operator ~ () {
	double n = norm();
	x /= n;
	y /= n;
	z /= n;
	return *this;
}

/****************************************************************
 * External operator overloading
 ****************************************************************/

Vector3D const& operator + (Vector3D v1, Vector3D const& v2) {
	return (v1 += v2);
}

Vector3D const& operator - (Vector3D v1, Vector3D const& v2) {
	return (v1 -= v2);
}

Vector3D const& operator * (Vector3D v, double const& lambda) {
	return (v *= lambda);
}

Vector3D const& operator / (Vector3D v, double const& lambda) {
	return (v /= lambda);
}

Vector3D const& operator ^ (Vector3D v1, Vector3D const& v2) {
	return (v1 ^= v2);
}

double const operator * (Vector3D const& v1, Vector3D const& v2) {
	return Vector3D::dot(v1, v2);
}

bool const operator == (Vector3D const& v1, Vector3D const& v2) {
	return Vector3D::eq(v1, v2);
}


/****************************************************************
 * Methods
 ****************************************************************/

string Vector3D::to_string() const {
	return "("s + std::to_string(getX()) + ", "s + std::to_string(getY()) + ", "s + std::to_string(getZ()) + ")"s;
}

double Vector3D::norm() const {
	return sqrt(normSquared());
}

double Vector3D::normSquared() const {
	return pow(getX(), 2) + pow(getY(), 2) + pow(getZ(), 2);
}

Vector3D& Vector3D::rotate(Vector3D axis, double const& alpha) {
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

double Vector3D::dot(Vector3D const& v1, Vector3D const& v2) {
	return v1.getX() * v2.getX() + v1.getY() * v2.getY() + v1.getZ() * v2.getZ();
}

bool Vector3D::eq(Vector3D const& v1, Vector3D const& v2) {
	bool a = abs(v1.getX() - v2.getX()) < EPSILON;
	bool b = abs(v1.getY() - v2.getY()) < EPSILON;
	bool c = abs(v1.getZ() - v2.getZ()) < EPSILON;
	return a and b and c;
}

/****************************************************************
 * Cout overloading
 ****************************************************************/

ostream& operator<< (ostream& stream, Vector3D const& v) {
	stream << v.to_string();
	return stream;
}
