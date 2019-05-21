#ifndef VECTOR3D_H
#define VECTOR3D_H

#pragma once

#include <string>
#include <sstream>
#include <iomanip>
#include <cmath>
#include <QVector3D>

// Forward declaration
class Drawable;
class Renderer;

#include "globals.h"
#include "exceptions.h"

/**
 * The `Vector3D` class represents a vector in a 3D carthesian space.
 */

class Vector3D : public Drawable {
public:

	/****************************************************************
	 * Constructors
	 ****************************************************************/

	/**
	 * Default behavior: initialization with `(0.0, 0.0, 0.0)`
	 *
	 * Initialization of the engine (if given), nullptr by default
	 *
	 * The constructor is explicit to prevent accidental type casting.
	 */

	explicit Vector3D(Renderer * engine_ptr = nullptr);

	/**
	 * Initialises the vector with a triplet of `double`s representing the vector parameters
	 *
	 * Initialization of the engine (if given), nullptr by default
	 *
	 * The constructor is explicit to prevent accidental type casting.
	 */

	explicit Vector3D(double _x, double _y, double _z, Renderer * engine_ptr = nullptr);

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
	 * Queries
	 ****************************************************************/

	/**
	 * Returns QVector3D suitable for graphics (x, z, y)
	 */

	QVector3D toQVector3D() const;

	/****************************************************************
	 * Setters
	 ****************************************************************/

	/**
	 * Sets private x to the given parameter
	 */

	void setX(double _x);

	/**
	 * Sets private y to the given parameter
	 */

	void setY(double _y);

	/**
	 * Sets private z to the given parameter
	 */

	void setZ(double _z);

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
	 * Cross product of *this with a given vector.
	 *
	 * The cross product results in a vector which is normal to both input vectors.
	 *
	 * Its direction is such that vectors v1_in, v2_in, v_out is a normal oriented base.
	 *
	 * WARNING: changes *this to the result of the product
	 */

	Vector3D& operator ^= (Vector3D const& v);

	/**
	 * Multiplies *this by a given scalar (double or int)
	 */

	Vector3D& operator *= (double lambda);

	/**
	 * Divides *this by a given scalar (double or int)
	 *
	 * If you try to divide by 0 (aka abs(lambda) < GLOBALS::DELTA_DIV0), we _will_ yell at you
	 */

	Vector3D& operator /= (double lambda);

	/**
	 * Normalizes *this such that its norm becomes 1, but its direction remains unchanged
	 *
	 * If you try to normalize the null vector (aka this->norm() < GLOBALS::DELTA_DIV0), we _will_ yell at you
	 */

	Vector3D& operator ~ ();

	/****************************************************************
	 * Methods
	 ****************************************************************/

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
	 * WARNING: the angles are given in __radians__
	 */

	Vector3D& rotate(Vector3D axis, double alpha);

	/**
	 * Returns a string representation of the vector
	 */

	std::string to_string() const;

	/****************************************************************
	 * Static methods
	 ****************************************************************/

	/**
	 * Returns the triple product (oriented volume of the spanned parallepiped) of v1, v2, v3; i.e. v1 * (v2 ^ v3)
	 */

	static double tripleProduct(Vector3D const& v1, Vector3D const& v2, Vector3D const& v3);

	/****************************************************************
	 * Rendering engine
	 ****************************************************************/

	/**
	 * Reroute the drawing call (double dispatching)
	 *
	 * - Use renderer in argument if given
	 * - Else use class renderer
	 * - Else throw EXCEPTIONS::NULLPTR
	 */

	virtual void draw(Renderer * engine_ptr = nullptr) const override;

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
 * Multiplies a vector by a scalar.
 *
 * Note that this operation is commutative.
 */

Vector3D const operator * (Vector3D v, double lambda);

/**
 * Multiplies a vector by a scalar.
 *
 * Note that this operation is commutative.
 */

Vector3D const operator * (double lambda, Vector3D v);

/**
 * Divides a vector by a scalar.
 *
 * Again, if you try to divide by 0, we _will_ yell at you.
 */

Vector3D const operator / (Vector3D v, double lambda);

/**
 * Returns the vector product of the lhs and rhs
 *
 * This operator has a low priority and is evaluated after relational operators.
 * Use parantheses to prioritize the evaluation of `^`
 *
 * See [the reference](https://en.cppreference.com/w/cpp/language/operator_precedence) for more information.
 */

Vector3D const operator ^ (Vector3D v1, Vector3D const& v2);

/**
 * Returns the opposite of the vector
 */

Vector3D const operator - (Vector3D v);

/**
 * Returns the dot product of the lhs and the rhs
 */

double operator * (Vector3D const& v1, Vector3D const& v2);

/**
 * Returns whether two vectors are identical, within the error range of `GLOBALS::EPSILON`
 */

bool operator == (Vector3D const& v1, Vector3D const& v2);

/**
 * Returns whether two vectors are different, within the error range of `GLOBALS::EPSILON`
 */

bool operator != (Vector3D const& v1, Vector3D const& v2);

/****************************************************************
 * Cout overloading
 ****************************************************************/

/**
 * Overloads ostream operator << for Vector3D
 */

std::ostream& operator<< (std::ostream& stream, Vector3D const& v);

#endif
