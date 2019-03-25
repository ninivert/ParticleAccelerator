#ifndef VECTOR3D_H
#define VECTOR3D_H

#pragma once

#include <string>
#include <sstream>
#include <iomanip>
#include <cmath>
#include "src/globals.h"
#include "src/exceptions.h"

/**
 * The `Vector3D` class represents a vector in a 3D carthesian space.
 */

class Vector3D {
public:
	/****************************************************************
	 * Constructors
	 ****************************************************************/

	/**
	 * Default behavior: initialization with `(0.0, 0.0, 0.0)`
	 *
	 * The constructor is explicit to prevent accidental type casting.
	 */

	explicit Vector3D();

	/**
	 * Initialises the vector with a triplet of `double`s representing the vector parameters
	 *
	 * The constructor is explicit to prevent accidental type casting.
	 */

	explicit Vector3D(double const& _x, double const& _y, double const& _z);

	/****************************************************************
	 * Getters
	 ****************************************************************/

	/**
	 * Returns the private x attribute
	 */

	double getX() const;

	/**
	 * Returns the private y attribute
	 */

	double getY() const;

	/**
	 * Returns the private z attribute
	 */

	double getZ() const;

	/****************************************************************
	 * Setters
	 ****************************************************************/

	/**
	 * Sets private x to the given parameter
	 */

	void setX(double const& _x);

	/**
	 * Sets private y to the given parameter
	 */

	void setY(double const& _y);

	/**
	 * Sets private z to the given parameter
	 */

	void setZ(double const& _z);

	/**
	 * Sets all coordinates (x, y, z) to 0
	 */

	void setNull();

	/****************************************************************
	 * Internal overloading
	 ****************************************************************/

	/**
	 * Adds a given vector to *this
	 */

	Vector3D& operator += (Vector3D const& v);

	/**
	 * Subtracts a given vector to *this
	 */

	Vector3D& operator -= (Vector3D const& v);

	/**
	 * Vector product of *this with a given vector.
	 *
	 * The vector product results in a vector which is normal to both input vectors.
	 *
	 * Its direction is such that vectors v1_in, v2_in, v_out is a normal oriented base.
	 *
	 * WARNING: changes *this to the result of the product
	 */

	Vector3D& operator ^= (Vector3D const& v);

	/**
	 * Multiplies *this by a given scalar (double or int)
	 */

	Vector3D& operator *= (double const& lambda);

	/**
	 * Divides *this by a given scalar (double or int)
	 *
	 * If you try to divide by 0 (aka abs(lambda) < GLOBALS::DELTA), we _will_ yell at you
	 */

	Vector3D& operator /= (double const& lambda);

	/**
	 * Normalizes *this such that its norm becomes 1, but its direction remains unchanged
	 */

	Vector3D& operator ~ ();

	/****************************************************************
	 * Methods
	 ****************************************************************/

	/**
	 * Returns a string representation of the vector
	 */

	std::string to_string() const;

	/**
	 * Returns the norm of the vector, using the square root of `Vector3D::normSquared()`
	 */

	double norm() const;

	/**
	 * Returns the squared norm of the vector.
	 *
	 * Prefer using this method rather than `pow(norm(), 2)` for better performance.
	 */

	double normSquared() const;

	/**
	 * Rotates the vector by `alpha` around a given `axis` vector.
	 *
	 * WARNING: the angles are given in radians
	 */

	Vector3D& rotate(Vector3D axis, double const& alpha);

	/****************************************************************
	 * Static methods
	 ****************************************************************/

	/**
	 * Returns the triple product (volume of the spanned parallepiped) of v1, v2, v3; i.e. v1 * (v2 ^ v3)
	 */

	static double tripleProduct(Vector3D const& v1, Vector3D const& v2, Vector3D const& v3);

private:
	// Attributes

	double x;
	double y;
	double z;
};

/****************************************************************
 * External overloading
 ****************************************************************/

/**
 * Adds two vectors
 */

Vector3D const operator + (Vector3D v1, Vector3D const& v2);

/**
 * Subtracts two vectors
 */

Vector3D const operator - (Vector3D v1, Vector3D const& v2);

/**
 * Returns the vector product of the lhs and rhs
 */

Vector3D const operator ^ (Vector3D v1, Vector3D const& v2);

/**
 * Multiplies a vector by a scalar.
 *
 * Note that this operation is commutative.
 */

Vector3D const operator * (Vector3D v, double const& lambda);

/**
 * Multiplies a vector by a scalar.
 *
 * Note that this operation is commutative.
 */

Vector3D const operator * (double const& lambda, Vector3D v);

/**
 * Divides a vector by a scalar.
 *
 * Again, if you try to divide by 0, we _will_ yell at you.
 */

Vector3D const operator / (Vector3D v, double const& lambda);

/**
 * Returns the dot product of the lhs and the rhs
 */

double const operator * (Vector3D const& v1, Vector3D const& v2);

/**
 * Returns whether two vectors are identical, within the error range of `GLOBALS::EPSILON`
 */

bool const operator == (Vector3D const& v1, Vector3D const& v2);

/**
 * Returns whether two vectors are different, within the error range of `GLOBALS::EPSILON`
 */

bool const operator != (Vector3D const& v1, Vector3D const& v2);

/****************************************************************
 * Cout overloading
 ****************************************************************/

/**
 * Streams the `Vector3D::to_string()` representation to a given stream
 */

std::ostream& operator<< (std::ostream& stream, Vector3D const& v);

#endif
