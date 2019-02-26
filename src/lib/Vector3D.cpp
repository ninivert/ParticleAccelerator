#include <string>
#include <cmath>
#include "../constants.cpp"

using namespace std;

/**
 * Vector3D
 */

class Vector3D {
public:
	// Constructor

	Vector3D(const double& _x, const double& _y, const double& _z) {
		x = _x;
		y = _y;
		z = _z;
	}

	Vector3D(const Vector3D& v) {
		x = v.getX();
		y = v.getY();
		z = v.getZ();
	}

	// Getters

	double getX() const { return x; }
	double getY() const { return y; }
	double getZ() const { return z; }

	// Setters

	void setX(const double& _x) { x = _x; }
	void setY(const double& _y) { y = _y; }
	void setZ(const double& _z) { z = _z; }

	// Overloading

	Vector3D operator + (const Vector3D& v) const {
		Vector3D res(*this);
		res.__add__(v);
		return res;
	}

	Vector3D operator - (const Vector3D& v) const {
		Vector3D res(*this);
		res.__sub__(v);
		return res;
	}

	Vector3D operator * (const double& lambda) const {
		Vector3D res(*this);
		res.__mult__(lambda);
		return res;
	}

	Vector3D operator / (const double& lambda) const {
		Vector3D res(*this);
		res.__div__(lambda);
		return res;
	}

	Vector3D operator ^ (const Vector3D& v) const {
		Vector3D res(*this);
		res.__cross__(v);
		return res;
	}

	double operator * (const Vector3D& v) const {
		Vector3D res(*this);
		return res.__dot__(v);
	}

	bool operator == (const Vector3D& v) const {
		return __eq__(v);
	}

	void operator = (const Vector3D& v) {
		x = v.getX();
		y = v.getY();
		z = v.getZ();
	}

	// Methods

	string stringify() const {
		return "("s + to_string(x) + ", "s + to_string(y) + ", "s + to_string(z) + ")"s;
	}

	double norm() const {
		return sqrt(normSquared());
	}

	double normSquared() const {
		return pow(x, 2) + pow(y, 2) + pow(z, 2);
	}

	void normalize() {
		double n = norm();
		x /= n;
		y /= n;
		z /= n;
	}

	// Static methods

	static double tripleProduct(const Vector3D& v1, const Vector3D& v2, const Vector3D& v3) {
		return v1 * (v2 ^ v3);
	}


private:
	// Attributes

	double x;
	double y;
	double z;

	// Overloading methods

	void __add__(const Vector3D& v) {
		x += v.getX();
		y += v.getY();
		z += v.getZ();
	}

	void __sub__(const Vector3D& v) {
		x -= v.getX();
		y -= v.getY();
		z -= v.getZ();
	}

	void __mult__(const double& lambda) {
		x *= lambda;
		y *= lambda;
		z *= lambda;
	}

	void __div__(const double& lambda) {
		x /= lambda;
		y /= lambda;
		z /= lambda;
	}

	void __cross__(const Vector3D& v) {
		double _x = y*v.getZ() - z*v.getY();
		double _y = z*v.getX() - x*v.getZ();
		double _z = x*v.getY() - y*v.getX();
		x = _x;
		y = _y;
		z = _z;
	}

	double __dot__(const Vector3D& v) const {
		return x*v.getX() + y*v.getY() + z*v.getZ();
	}

	bool __eq__(const Vector3D& v) const {
		bool a = abs(x - v.getX()) < EPSILON;
		bool b = abs(y - v.getY()) < EPSILON;
		bool c = abs(z - v.getZ()) < EPSILON;
		return a and b and c;
	}

};

/**
 * Cout overloading
 */

ostream& operator<< (ostream& stream, const Vector3D& v) {
	string x = v.stringify();
	stream << x;
	return stream;
}