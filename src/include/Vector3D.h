#pragma once

#include <string>
#include <cmath>
#include "src/globals.h"

/**
 * Vector3D
 */

class Vector3D {
public:
	// Constructors

	explicit Vector3D();
	explicit Vector3D(double const& _x, double const& _y, double const& _z);
	Vector3D(Vector3D const& v);

	// Getters

	double getX() const;
	double getY() const;
	double getZ() const;

	// Setters

	void setX(double const& _x);
	void setY(double const& _y);
	void setZ(double const& _z);
	void setNull();

	// Internal Overloading

	Vector3D& operator += (Vector3D const& v);
	Vector3D& operator -= (Vector3D const& v);
	Vector3D& operator ^= (Vector3D const& v);
	Vector3D& operator *= (double const& lambda);
	Vector3D& operator /= (double const& lambda);
	Vector3D& operator ~ ();
	void operator = (Vector3D const& v);

	// Methods

	std::ostream& stream(std::ostream& stream) const;
	double norm() const;
	double normSquared() const;
	Vector3D& rotate(Vector3D axis, double const& alpha);

	// Static method

	static double tripleProduct(Vector3D const& v1, Vector3D const& v2, Vector3D const& v3);

private:
	// Attributes

	double x;
	double y;
	double z;
};

/**
 * External overloading
 */

Vector3D const& operator + (Vector3D v1, Vector3D const& v2);
Vector3D const& operator - (Vector3D v1, Vector3D const& v2);
Vector3D const& operator ^ (Vector3D v1, Vector3D const& v2);
Vector3D const& operator * (Vector3D v, double const& lambda);
Vector3D const& operator * (double const& lambda, Vector3D v);
Vector3D const& operator / (Vector3D v, double const& lambda);
double const operator * (Vector3D const& v1, Vector3D const& v2);
bool const operator == (Vector3D const& v1, Vector3D const& v2);
bool const operator != (Vector3D const& v1, Vector3D const& v2);


/**
 * Cout overloading
 */

std::ostream& operator<< (std::ostream& stream, Vector3D const& v);
