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

	/****************************************************************
	 * Constructors
	 ****************************************************************/

	/**
	 * Null vertex constructor
	 */

	SimpleVertex() {}

	/**
	 * Construct a vertex from position
	 */

	explicit SimpleVertex(QVector3D const& position) : position(position) {}

	/****************************************************************
	 * Getters and setters
	 ****************************************************************/

	/**
	 * Returns position stored in vertex
	 */

	const QVector3D& getPosition() const { return position; }

	/**
	 * Sets position of vertex
	 */

	void setPosition(const QVector3D& _position) { position = _position; }

	/****************************************************************
	 * OpenGL Helpers
	 ****************************************************************/

	/**
	 * 3 coordinates encode position
	 */

	static const int PositionTupleSize = 3;

	/**
	 * Returns the offset value in bytes of member member in the data structure or union type type
	 *
	 * Useful for shader initialization for determining "where" to find the info
	 */

	static int positionOffset() { return offsetof(SimpleVertex, position); }

	/**
	 * Stride indicates the number of bytes between vertices, aka the size of a SimpleVertex instance
	 */

	static int stride() { return sizeof(SimpleVertex); }

protected:

	/****************************************************************
	 * Attributes
	 ****************************************************************/

	/**
	 * Position stored in the vertex
	 */

	QVector3D position;
};

/**
 * Normal vertex, positon and color
 *
 * No inheritance because offsetof cannot be used on non-standard-layout classes aka we can't inherit
 */

class Vertex {
public:

	/****************************************************************
	 * Constructors
	 ****************************************************************/

	/**
	 * Null vertex constructor
	 */

	Vertex() {}

	/**
	 * Construct a vertex from position, black color
	 */

	explicit Vertex(QVector3D const& position) : position(position) {}

	/**
	 * Construct a vertex from position and color
	 */

	explicit Vertex(QVector3D const& position, QVector3D const& color) : position(position), color(color) {}

	/****************************************************************
	 * Getters and setters
	 ****************************************************************/

	/**
	 * Returns position stored in vertex
	 */

	const QVector3D& getPosition() const { return position; }

	/**
	 * Returns color stored in vertex
	 */

	const QVector3D& getColor() const { return color; }

	/**
	 * Sets position of vertex
	 */

	void setPosition(const QVector3D& _position) { position = _position; }

	/**
	 * Sets color of vertex
	 */

	void setColor(QVector3D const& _color) { color = _color; }

	/****************************************************************
	 * OpenGL Helpers
	 ****************************************************************/

	/**
	 * 3 coordinates encode position
	 */

	static const int PositionTupleSize = 3;

	/**
	 * 3 channels encode position
	 */

	static const int ColorTupleSize = 3;

	/**
	 * Returns the offset value in bytes of member member in the data structure or union type type
	 *
	 * Useful for shader initialization for determining "where" to find the info
	 */

	static int positionOffset() { return offsetof(Vertex, position); }

	/**
	 * Returns the offset value in bytes of member member in the data structure or union type type
	 *
	 * Useful for shader initialization for determining "where" to find the info
	 */

	static int colorOffset() { return offsetof(Vertex, color); }

	/**
	 * Stride indicates the number of bytes between vertices, aka the size of a SimpleVertex instance
	 */

	static int stride() { return sizeof(Vertex); }

private:

	/****************************************************************
	 * Attributes
	 ****************************************************************/

	/**
	 * Position stored in the vertex
	 */

	QVector3D position;

	/**
	 * Color stored in the vertex
	 */

	QVector3D color;
};

// Note: Q_MOVABLE_TYPE means it can be memcpy'd.
Q_DECLARE_TYPEINFO(Vertex, Q_MOVABLE_TYPE);
Q_DECLARE_TYPEINFO(SimpleVertex, Q_MOVABLE_TYPE);

#endif
