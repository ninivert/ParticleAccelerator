#include <string>
#include <cmath>
#include "src/constants.h"


/**
 * Vector3D
 */

class Vector3D {
public:
	// Constructor

	Vector3D(const double& _x, const double& _y, const double& _z);
	Vector3D(const Vector3D& v);

	// Getters

	double getX() const;
	double getY() const;
	double getZ() const;

	// Setters

	void setX(const double& _x);
	void setY(const double& _y);
	void setZ(const double& _z);

	// Overloading

	Vector3D operator + (const Vector3D& v) const;
	Vector3D operator - (const Vector3D& v) const;
	Vector3D operator * (const double& lambda) const;
	Vector3D operator / (const double& lambda) const;
	Vector3D operator ^ (const Vector3D& v) const;
	double operator * (const Vector3D& v) const;
	bool operator == (const Vector3D& v) const;
	void operator = (const Vector3D& v);

	// Methods

	std::string stringify() const;
	double norm() const;
	double normSquared() const;

	void normalize();

	// Static methods

	static double tripleProduct(const Vector3D& v1, const Vector3D& v2, const Vector3D& v3);


private:
	// Attributes

	double x;
	double y;
	double z;

	// Overloading methods

	void __add__(const Vector3D& v);
	void __sub__(const Vector3D& v);
	void __mult__(const double& lambda);
	void __div__(const double& lambda);
	void __cross__(const Vector3D& v);
	double __dot__(const Vector3D& v) const;
	bool __eq__(const Vector3D& v) const;
};

/**
 * Cout overloading
 */

std::ostream& operator<< (std::ostream& stream, const Vector3D& v);
