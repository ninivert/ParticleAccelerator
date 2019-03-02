#include <string>
#include <cmath>
#include "src/globals.h"


/**
 * Vector3D
 */

class Vector3D {
public:
	// Constructors

	Vector3D(double const& _x, double const& _y, double const& _z);
	Vector3D(Vector3D const& v);

	// Getters

	double getX() const;
	double getY() const;
	double getZ() const;

	// Setters

	void setX(double const& _x);
	void setY(double const& _y);
	void setZ(double const& _z);

	// Overloading

	Vector3D operator + (Vector3D const& v) const;
	Vector3D operator - (Vector3D const& v) const;
	Vector3D operator * (double const& lambda) const;
	Vector3D operator / (double const& lambda) const;
	Vector3D operator ^ (Vector3D const& v) const;
	double operator * (Vector3D const& v) const;
	bool operator == (Vector3D const& v) const;
	void operator = (Vector3D const& v);

	// Methods

	std::string stringify() const;
	double norm() const;
	double normSquared() const;

	void normalize();

	// Static methods

	static double tripleProduct(Vector3D const& v1, Vector3D const& v2, Vector3D const& v3);


private:
	// Attributes

	double x;
	double y;
	double z;

	// Overloading methods

	void __add__(Vector3D const& v);
	void __sub__(Vector3D const& v);
	void __mult__(double const& lambda);
	void __div__(double const& lambda);
	void __cross__(Vector3D const& v);
	double __dot__(Vector3D const& v) const;
	bool __eq__(Vector3D const& v) const;
};

/**
 * Cout overloading
 */

std::ostream& operator<< (std::ostream& stream, Vector3D const& v);
