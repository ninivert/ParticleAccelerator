#ifndef CAMERA3D_H
#define CAMERA3D_H

#pragma once

#include <QVector3D>
#include <QQuaternion>
#include <QMatrix4x4>

class Camera3D {
public:
	// Constructors
	Camera3D();

	// Transform By (Add/Scale)
	void translate(QVector3D const& dt);
	void translate(double dx, double dy, double dz);
	void rotate(QQuaternion const& dr);
	void rotate(double angle, QVector3D const& axis);
	void rotate(double angle, double ax, double ay, double az);

	// Transform To (Setters)
	void setTranslation(QVector3D const& t);
	void setTranslation(double x, double y, double z);
	void setRotation(QQuaternion const& r);
	void setRotation(double angle, QVector3D const& axis);
	void setRotation(double angle, double ax, double ay, double az);
	void reset();

	// Getters
	QVector3D const& getTranslation() const;
	QQuaternion const& getRotation() const;
	QMatrix4x4 const& getMatrix();

	// Queries (no const& because we are returning reference to temporary object)
	QVector3D getForwardVector() const;
	QVector3D getUpVector() const;
	QVector3D getRightVector() const;

	// Local coordinate system (left handed)
	static inline const QVector3D LocalForward = QVector3D(0.0, 0.0, -1.0);
	static inline const QVector3D LocalUp = QVector3D(0.0, 1.0, 0.0);
	static inline const QVector3D LocalRight = QVector3D(1.0, 0.0, 0.0);

private:
	// Mark that changes have been made
	bool dirty;
	// Transformation vectors
	QVector3D translationVector;
	// The QQuaternion class represents a quaternion consisting of a vector and scalar.
	// Quaternions are used to represent rotations in 3D space,
	// and consist of a 3D rotation axis specified by the x, y,
	// and z coordinates, and a scalar representing the rotation angle.
	QQuaternion rotationQuaternion;
	// Model to world matrix
	QMatrix4x4 worldToCamera;
};

Q_DECLARE_TYPEINFO(Camera3D, Q_MOVABLE_TYPE);

#endif
