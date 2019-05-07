#include "include/Transform3D.h"

/****************************************************************
 * Constructor
 ****************************************************************/

Transform3D::Transform3D() : dirty(true), scaleVector(1.0, 1.0, 1.0) {}

/****************************************************************
 * Transform by
 ****************************************************************/

/**
 * Translations
 */

void Transform3D::translate(double dx, double dy, double dz) {
	translate(QVector3D(dx, dy, dz));
}

void Transform3D::translate(QVector3D const& dt) {
	dirty = true;
	translationVector += dt;
}

/**
 * Scale
 */

void Transform3D::scale(double dx, double dy, double dz) {
	scale(QVector3D(dx, dy, dz));
}

void Transform3D::scale(double k) {
	scale(QVector3D(k, k, k));
}

void Transform3D::scale(QVector3D const& ds) {
	dirty = true;
	scaleVector *= ds; // component-wise multiplication
}

/**
 * Rotation
 */

void Transform3D::rotate(double angle, QVector3D const& axis) {
	rotate(QQuaternion::fromAxisAndAngle(axis, angle));
}

void Transform3D::rotate(double angle, double ax, double ay, double az) {
	rotate(QQuaternion::fromAxisAndAngle(ax, ay, az, angle));
}

void Transform3D::rotate(QQuaternion const& dr) {
	dirty = true;
	rotationQuaternion = dr * rotationQuaternion;
}

/**
 * Grow
 */

void Transform3D::grow(double dx, double dy, double dz) {
	grow(QVector3D(dx, dy, dz));
}

void Transform3D::grow(double k) {
	grow(QVector3D(k, k, k));
}

void Transform3D::grow(QVector3D const& ds) {
	dirty = true;
	scaleVector += ds;
}

/****************************************************************
 * Setters
 ****************************************************************/

/**
 * Translation
 */

void Transform3D::setTranslation(double x, double y, double z) {
	setTranslation(QVector3D(x, y, z));
}

void Transform3D::setTranslation(QVector3D const& t) {
	dirty = true;
	translationVector = t;
}

/**
 * Scale
 */

void Transform3D::setScale(double x, double y, double z) {
	setScale(QVector3D(x, y, z));
}

void Transform3D::setScale(double k) {
	setScale(QVector3D(k, k, k));
}

void Transform3D::setScale(QVector3D const& s) {
	dirty = true;
	scaleVector = s;
}

/**
 * Rotation
 */

void Transform3D::setRotation(double angle, QVector3D const& axis) {
	setRotation(QQuaternion::fromAxisAndAngle(axis, angle));
}

void Transform3D::setRotation(double angle, double ax, double ay, double az) {
	setRotation(QQuaternion::fromAxisAndAngle(ax, ay, az, angle));
}

void Transform3D::setRotation(QQuaternion const& r) {
	dirty = true;
	rotationQuaternion = r;
}

/**
 * Reset
 */

void Transform3D::reset() {
	dirty = true;
	translationVector = QVector3D();
	scaleVector = QVector3D(1, 1, 1);
	rotationQuaternion = QQuaternion();
}

/****************************************************************
 * Getters
 ****************************************************************/

QVector3D const& Transform3D::getTranslation() const {
	return translationVector;
}

QVector3D const& Transform3D::getScale() const {
	return scaleVector;
}

QQuaternion const& Transform3D::getRotation() const {
	return rotationQuaternion;
}

QMatrix4x4 const& Transform3D::getMatrix() {
	if (dirty) {
		dirty = false;
		modelToWorld.setToIdentity();
		modelToWorld.translate(translationVector);
		modelToWorld.rotate(rotationQuaternion);
		modelToWorld.scale(scaleVector);
	}
	return modelToWorld;
}

QVector3D Transform3D::getForwardVector() const {
	return rotationQuaternion.rotatedVector(LocalForward);
}

QVector3D Transform3D::getUpVector() const {
	return rotationQuaternion.rotatedVector(LocalUp);
}

QVector3D Transform3D::getRightVector() const {
	return rotationQuaternion.rotatedVector(LocalRight);
}

/****************************************************************
 * Save and restore
 ****************************************************************/

void Transform3D::save() {
	savedTranslationVector = translationVector;
	savedScaleVector = scaleVector;
	savedRotationQuaternion = rotationQuaternion;
}

void Transform3D::restore() {
	dirty = true;
	translationVector = savedTranslationVector;
	scaleVector = savedScaleVector;
	rotationQuaternion = savedRotationQuaternion;
}
