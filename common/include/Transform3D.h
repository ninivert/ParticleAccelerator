#ifndef TRANSFORM3D_H
#define TRANSFORM3D_H

#pragma once

#include <QVector3D>
#include <QQuaternion>
#include <QMatrix4x4>

class Transform3D {
public:
	/**
	 * Constructor
	 */

	Transform3D();

	/****************************************************************
	 * Transform By (Add/Scale)
	 ****************************************************************/

	/**
	 * Translate by vector
	 */

	void translate(QVector3D const& dt);

	/**
	 * Translate by vector
	 */

	void translate(double dx, double dy, double dz);

	/**
	 * Scale by a component-wise vector
	 */

	void scale(QVector3D const& ds);

	/**
	 * Scale by a component-wise vector
	 */

	void scale(double dx, double dy, double dz);

	/**
	 * Scale each component by scalar
	 */

	void scale(double k);

	/**
	 * Rotate by quaternion
	 */

	void rotate(QQuaternion const& dr);

	/**
	 * Rotate by angle around axis
	 */

	void rotate(double angle, QVector3D const& axis);

	/**
	 * Rotate by angle around axis
	 */

	void rotate(double angle, double ax, double ay, double az);

	/**
	 * Grow by a component-wise vector
	 */

	void grow(QVector3D const& ds);

	/**
	 * Grow by a component-wise vector
	 */

	void grow(double dx, double dy, double dz);

	/**
	 * Grow each component by a scalar
	 */

	void grow(double k);

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
	 * Set scale factor to component-wise vector
	 */

	void setScale(QVector3D const& s);

	/**
	 * Set scale factor to component-wise vector
	 */

	void setScale(double x, double y, double z);

	/**
	 * Set scale factor to scalar
	 */

	void setScale(double k);

	/**
	 * Set rotation to quaternion
	 */

	void setRotation(QQuaternion const& r);

	/**
	 * Set rotation of sclar around axis vector
	 */

	void setRotation(double angle, QVector3D const& axis);

	/**
	 * Set rotation of sclar around axis vector
	 */

	void setRotation(double angle, double ax, double ay, double az);

	/**
	 * Reset transformation to identity
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
	 * Get scaling component-wise vector
	 */

	QVector3D const& getScale() const;

	/**
	 * Get rotation quaternion
	 */

	QQuaternion const& getRotation() const;

	/**
	 * Get matrix reprensentation of the transform
	 */

	QMatrix4x4 const& getMatrix();

	/****************************************************************
	 * Queries
	 ****************************************************************/

	/**
	 * Get forward vector relative to transform (no const& because we are returning reference to temporary object)
	 */

	QVector3D getForwardVector() const;

	/**
	 * Get up vector relative to transform (no const& because we are returning reference to temporary object)
	 */

	QVector3D getUpVector() const;

	/**
	 * Get right vector relative to transform (no const& because we are returning reference to temporary object)
	 */

	QVector3D getRightVector() const;

	/****************************************************************
	 * Save and reset system
	 ****************************************************************/

	/**
	 * Store state of transform
	 */

	void save();

	/**
	 * Restore saved state
	 */

	void restore();

	/****************************************************************
	 * Local coordinate system
	 ****************************************************************/

	/**
	 * Get forward vector in transform's right-handed coordinate system (no const& because we are returning reference to temporary object)
	 */

	static inline const QVector3D LocalForward = QVector3D(0.0, 0.0, 1.0);

	/**
	 * Get up vector in transform's right-handed coordinate system (no const& because we are returning reference to temporary object)
	 */

	static inline const QVector3D LocalUp = QVector3D(0.0, 1.0, 0.0);

	/**
	 * Get right vector in transform's right-handed coordinate system (no const& because we are returning reference to temporary object)
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
	 * Transform translation vector
	 */

	QVector3D translationVector;

	/**
	 * Transform scale vector
	 */

	QVector3D scaleVector;

	/**
	 * Transform rotation quaternion
	 *
	 * The QQuaternion class represents a quaternion consisting of a vector and scalar.
	 *
	 * Quaternions are used to represent rotations in 3D space,
	 * and consist of a 3D rotation axis specified by the x, y,
	 * and z coordinates, and a scalar representing the rotation angle.
	 */

	QQuaternion rotationQuaternion;

	/**
	 * Model to world matrix
	 */

	QMatrix4x4 modelToWorld;

	/****************************************************************
	 * Temporary saved states
	 ****************************************************************/

	/**
	 * Stores saved translation vector
	 */

	QVector3D savedTranslationVector;

	/**
	 * Stores saved scale vector
	 */

	QVector3D savedScaleVector;

	/**
	 * Stores saved rotation quaternion
	 */

	QQuaternion savedRotationQuaternion;
};

Q_DECLARE_TYPEINFO(Transform3D, Q_MOVABLE_TYPE);

#endif
