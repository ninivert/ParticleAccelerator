#ifndef TRANSFORM3D_H
#define TRANSFORM3D_H

#pragma once

#include <QVector3D>
#include <QQuaternion>
#include <QMatrix4x4>

class Transform3D {
public:
	// Constructors
	Transform3D();

	// Transform By (Add/Scale)
	void translate(QVector3D const& dt);
	void translate(double dx, double dy, double dz);
	void scale(QVector3D const& ds);
	void scale(double dx, double dy, double dz);
	void scale(double k);
	void rotate(QQuaternion const& dr);
	void rotate(double angle, QVector3D const& axis);
	void rotate(double angle, double ax, double ay, double az);
	void grow(QVector3D const& ds);
	void grow(double dx, double dy, double dz);
	void grow(double k);

	// Transform To (Setters)
	void setTranslation(QVector3D const& t);
	void setTranslation(double x, double y, double z);
	void setScale(QVector3D const& s);
	void setScale(double x, double y, double z);
	void setScale(double k);
	void setRotation(QQuaternion const& r);
	void setRotation(double angle, QVector3D const& axis);
	void setRotation(double angle, double ax, double ay, double az);
	void reset();

	// Getters
	QVector3D const& getTranslation() const;
	QVector3D const& getScale() const;
	QQuaternion const& getRotation() const;
	QMatrix4x4 const& getMatrix();

	// Queries (no const& because we are returning reference to temporary object)
	QVector3D getForwardVector() const;
	QVector3D getUpVector() const;
	QVector3D getRightVector() const;

	// Save and restore
	void save();
	void restore();

	// Local coordinate system (right handed)
	static inline const QVector3D LocalForward = QVector3D(0.0, 0.0, 1.0);
	static inline const QVector3D LocalUp = QVector3D(0.0, 1.0, 0.0);
	static inline const QVector3D LocalRight = QVector3D(1.0, 0.0, 0.0);

private:
	// Mark that changes have been made
	bool dirty;
	// Transformation vectors
	QVector3D translationVector;
	QVector3D scaleVector;
	// The QQuaternion class represents a quaternion consisting of a vector and scalar.
	// Quaternions are used to represent rotations in 3D space,
	// and consist of a 3D rotation axis specified by the x, y,
	// and z coordinates, and a scalar representing the rotation angle.
	QQuaternion rotationQuaternion;
	// Model to world matrix
	QMatrix4x4 modelToWorld;
	// Saved states
	QVector3D savedTranslationVector;
	QVector3D savedScaleVector;
	QQuaternion savedRotationQuaternion;
};

Q_DECLARE_TYPEINFO(Transform3D, Q_MOVABLE_TYPE);

#endif
