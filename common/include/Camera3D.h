#ifndef CAMERA3D_H
#define CAMERA3D_H

#pragma once

#include <QVector3D>
#include <QQuaternion>
#include <QMatrix4x4>

class Camera3D {
public:

	/****************************************************************
	 * Constructors and stuffs
	 ****************************************************************/

	/**
	 * Constructor
	 */

	Camera3D();

	/****************************************************************
	 * Transform By (Add/Scale)
	 ****************************************************************/

	/**
	 * Translate camera by vector
	 */

	void translate(QVector3D const& dt);

	/**
	 * Translate camera by scalars representing a vector
	 */

	void translate(double dx, double dy, double dz);

	/**
	 * Rotate camera by quaternion
	 */

	void rotate(QQuaternion const& dr);

	/**
	 * Rotate camera by angle around axis
	 */

	void rotate(double angle, QVector3D const& axis);

	/**
	 * Rotate camera by angle around axis
	 */

	void rotate(double angle, double ax, double ay, double az);

	/****************************************************************
	 * Transform To (Setters)
	 ****************************************************************/

	/**
	 * Set translation to vector
	 */

	void setTranslation(QVector3D const& t);

	/**
	 * Set translation to vector
	 */

	void setTranslation(double x, double y, double z);

	/**
	 * Set rotation to quaternion
	 */

	void setRotation(QQuaternion const& r);

	/**
	 * Set rotation to an angle around an axis
	 */

	void setRotation(double angle, QVector3D const& axis);

	/**
	 * Set rotation to an angle around an axis
	 */

	void setRotation(double angle, double ax, double ay, double az);

	/**
	 * Reset the camera to identity matrix
	 */

	void reset();

	/****************************************************************
	 * Getters
	 ****************************************************************/

	/**
	 * Get translation vector
	 */

	QVector3D const& getTranslation() const;

	/**
	 * Get rotation vector
	 */

	QQuaternion const& getRotation() const;

	/**
	 * Get camera matrix representation
	 */

	QMatrix4x4 const& getMatrix();

	/****************************************************************
	 * Queries
	 ****************************************************************/

	/**
	 * Get forward facing vector relative to camera (no const& because we are returning reference to temporary object)
	 */

	QVector3D getForwardVector() const;

	/**
	 * Get up facing vector relative to camera (no const& because we are returning reference to temporary object)
	 */

	QVector3D getUpVector() const;

	/**
	 * Get right facing vector relative to camera (no const& because we are returning reference to temporary object)
	 */

	QVector3D getRightVector() const;

	/****************************************************************
	 * Static constants
	 ****************************************************************/

	/**
	 * Forward vector in the camera's left-handed coordinate system
	 */

	static inline const QVector3D LocalForward = QVector3D(0.0, 0.0, -1.0);

	/**
	 * Up vector in the camera's left-handed coordinate system
	 */

	static inline const QVector3D LocalUp = QVector3D(0.0, 1.0, 0.0);

	/**
	 * Right vector in the camera's left-handed coordinate system
	 */

	static inline const QVector3D LocalRight = QVector3D(1.0, 0.0, 0.0);

private:

	/****************************************************************
	 * Attributes
	 ****************************************************************/

	/**
	 * Mark that changes have been made
	 */

	bool dirty;

	/**
	 * Camera translation vector
	 */

	QVector3D translationVector;

	/**
	 * Camera rotation quaternion
	 *
	 * The QQuaternion class represents a quaternion consisting of a vector and scalar.
	 *
	 * Quaternions are used to represent rotations in 3D space,
	 * and consist of a 3D rotation axis specified by the x, y,
	 * and z coordinates, and a scalar representing the rotation angle.
	 */

	QQuaternion rotationQuaternion;

	/**
	 * World to camera matrix
	 */

	QMatrix4x4 worldToCamera;
};

Q_DECLARE_TYPEINFO(Camera3D, Q_MOVABLE_TYPE);

#endif
