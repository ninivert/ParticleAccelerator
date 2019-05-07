#include "include/bundle/Camera3D.bundle.h"

/****************************************************************
 * Constructor
 ****************************************************************/

Camera3D::Camera3D() : dirty(true) {}

/****************************************************************
 * Transform by
 ****************************************************************/

/**
 * Translations
 */

void Camera3D::translate(double dx, double dy, double dz) {
	translate(QVector3D(dx, dy, dz));
}

void Camera3D::translate(QVector3D const& dt) {
	dirty = true;
	translationVector += dt;
}

/**
 * Rotation
 */

void Camera3D::rotate(double angle, QVector3D const& axis) {
	rotate(QQuaternion::fromAxisAndAngle(axis, angle));
}

void Camera3D::rotate(double angle, double ax, double ay, double az) {
	rotate(QQuaternion::fromAxisAndAngle(ax, ay, az, angle));
}

void Camera3D::rotate(QQuaternion const& dr) {
	dirty = true;
	rotationQuaternion = dr * rotationQuaternion;
}

/****************************************************************
 * Setters
 ****************************************************************/

/**
 * Translation
 */

void Camera3D::setTranslation(double x, double y, double z) {
	setTranslation(QVector3D(x, y, z));
}

void Camera3D::setTranslation(QVector3D const& t) {
	dirty = true;
	translationVector = t;
}

/**
 * Rotation
 */

void Camera3D::setRotation(double angle, QVector3D const& axis) {
	setRotation(QQuaternion::fromAxisAndAngle(axis, angle));
}

void Camera3D::setRotation(double angle, double ax, double ay, double az) {
	setRotation(QQuaternion::fromAxisAndAngle(ax, ay, az, angle));
}

void Camera3D::setRotation(QQuaternion const& r) {
	dirty = true;
	rotationQuaternion = r;
}

/**
 * Reset
 */

void Camera3D::reset() {
	dirty = true;
	translationVector = QVector3D();
	rotationQuaternion = QQuaternion();
}

/****************************************************************
 * Getters
 ****************************************************************/

QVector3D const& Camera3D::getTranslation() const {
	return translationVector;
}

QQuaternion const& Camera3D::getRotation() const {
	return rotationQuaternion;
}

QMatrix4x4 const& Camera3D::getMatrix() {
	if (dirty) {
		dirty = false;
		// Here we are constructing an inverted transform3d
		// because we want the world wrt the camera
		// and not the camera wrt the world
		// (up until now, it was always model wrt world, world wrt screen, etc.)
		worldToCamera.setToIdentity();
		worldToCamera.rotate(rotationQuaternion.conjugate());
		worldToCamera.translate(-translationVector);
	}
	return worldToCamera;
}

QVector3D Camera3D::getForwardVector() const {
	return rotationQuaternion.rotatedVector(LocalForward);
}

QVector3D Camera3D::getUpVector() const {
	return rotationQuaternion.rotatedVector(LocalUp);
}

QVector3D Camera3D::getRightVector() const {
	return rotationQuaternion.rotatedVector(LocalRight);
}
