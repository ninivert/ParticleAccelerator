#include "src/include/bundle/Vector3D.bundle.h"

using namespace std;

/****************************************************************
 * Constructors
 ****************************************************************/

Vector3D::Vector3D(Renderer * engine)
	: Vector3D(0.0, 0.0, 0.0, engine)
	{}

Vector3D::Vector3D(double const& _x, double const& _y, double const& _z, Renderer * engine)
	: Drawable(engine), x(_x), y(_y), z(_z)
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
void Vector3D::setNull() { x = 0; y = 0; z = 0; }

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
	if (abs(lambda) < GLOBALS::DELTA) {
		ERROR(EXCEPTIONS::DIV_0);
	}
	x /= lambda;
	y /= lambda;
	z /= lambda;
	return *this;
}

Vector3D& Vector3D::operator ~ () {
	double n = norm();
	*this /= n;
	return *this;
}

/****************************************************************
 * External operator overloading
 ****************************************************************/

Vector3D const operator + (Vector3D v1, Vector3D const& v2) {
	return (v1 += v2);
}

Vector3D const operator - (Vector3D v1, Vector3D const& v2) {
	return (v1 -= v2);
}

Vector3D const operator * (Vector3D v, double const& lambda) {
	return (v *= lambda);
}
Vector3D const operator * (double const& lambda, Vector3D v) {
	return (v *= lambda);
}

Vector3D const operator / (Vector3D v, double const& lambda) {
	return (v /= lambda);
}

Vector3D const operator ^ (Vector3D v1, Vector3D const& v2) {
	return (v1 ^= v2);
}

double const operator * (Vector3D const& v1, Vector3D const& v2) {
	return v1.getX() * v2.getX() +
		   v1.getY() * v2.getY() +
		   v1.getZ() * v2.getZ();
}

bool const operator == (Vector3D const& v1, Vector3D const& v2) {
	bool a = abs(v1.getX() - v2.getX()) < GLOBALS::EPSILON;
	bool b = abs(v1.getY() - v2.getY()) < GLOBALS::EPSILON;
	bool c = abs(v1.getZ() - v2.getZ()) < GLOBALS::EPSILON;
	return a and b and c;
}

bool const operator != (Vector3D const& v1, Vector3D const& v2) {
	return !(v1 == v2);
}

/****************************************************************
 * Methods
 ****************************************************************/

string Vector3D::to_string() const {
	stringstream stream;
	stream << setprecision(STYLES::PRECISION);
	stream
		// x
		<< "(" << getX()
		// y
		<< ", " << getY()
		// z
		<< ", " << getZ() << ")";
	return stream.str();
}

double Vector3D::norm() const {
	return sqrt(normSquared());
}

double Vector3D::normSquared() const {
	return getX() * getX() + getY() * getY() + getZ() * getZ();
}

Vector3D& Vector3D::rotate(Vector3D axis, double const& alpha) {
	~axis;
	(*this) *= cos(alpha);
	(*this) += (axis ^ (*this)) * sin(alpha) + (axis * ((*this) * axis)) * (1 - cos(alpha));
	return (*this);
}

/****************************************************************
 * Static method
 ****************************************************************/

double Vector3D::tripleProduct(Vector3D const& v1, Vector3D const& v2, Vector3D const& v3) {
	return v1 * (v2 ^ v3);
}

/****************************************************************
 * Cout overloading
 ****************************************************************/

ostream& operator << (ostream& stream, Vector3D const& v) {
	return stream << v.to_string();
}

/****************************************************************
 * Drawing
 ****************************************************************/

void Vector3D::draw() const {
	if (engine == nullptr) ERROR(EXCEPTIONS::NULLPTR);
	engine->draw(*this);
}

void Vector3D::drawTo(Renderer * engine) const {
	if (engine == nullptr) ERROR(EXCEPTIONS::NULLPTR);
	engine->draw(*this);
}
