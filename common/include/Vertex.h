#ifndef VERTEX_H
#define VERTEX_H

#pragma once

// Yes, we have our own Vector3D implementation,
// but here we are trying to keep things coherent
#include <QVector3D>

/**
 * Vertex with no color
 */

class SimpleVertex {
public:
	// Constructors
	SimpleVertex() {}
	explicit SimpleVertex(QVector3D const& position) : position(position) {}

	// Accessors / Mutators
	const QVector3D& getPosition() const { return position; }
	void setPosition(const QVector3D& _position) { position = _position; }

	// OpenGL Helpers
	static const int PositionTupleSize = 3; // 3 doubles to store position
	// Returns the offset value in bytes of member member in the data structure or union type type
	// Useful for shader initialization for determining "where" to find the info
	static int positionOffset() { return offsetof(SimpleVertex, position); }
	// stride indicates the number of bytes between vertices
	static int stride() { return sizeof(SimpleVertex); }

protected:
	QVector3D position;
};

/**
 * Normal vertex, positon and color
 *
 * No inheritance because offsetof cannot be used on non-standard-layout classes aka we can't inherit
 */

class Vertex {
public:
	// Constructors
	Vertex() {}
	explicit Vertex(QVector3D const& position) : position(position) {}
	explicit Vertex(QVector3D const& position, QVector3D const& color) : position(position), color(color) {}

	// Accessors / Mutators
	const QVector3D& getPosition() const { return position; }
	const QVector3D& getColor() const { return color; }
	void setPosition(const QVector3D& _position) { position = _position; }
	void setColor(QVector3D const& _color) { color = _color; }

	// OpenGL Helpers
	static const int PositionTupleSize = 3;
	static const int ColorTupleSize = 3;
	// Returns the offset value in bytes of member member in the data structure or union type type
	// Useful for shader initialization for determining "where" to find the info
	static int positionOffset() { return offsetof(Vertex, position); }
	static int colorOffset() { return offsetof(Vertex, color); }
	// stride indicates the number of bytes between vertices
	static int stride() { return sizeof(Vertex); }

private:
	QVector3D position;
	QVector3D color;
};

// Note: Q_MOVABLE_TYPE means it can be memcpy'd.
Q_DECLARE_TYPEINFO(Vertex, Q_MOVABLE_TYPE);
Q_DECLARE_TYPEINFO(SimpleVertex, Q_MOVABLE_TYPE);

#endif
