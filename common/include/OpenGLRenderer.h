#ifndef OPENGLRENDERER_H
#define OPENGLRENDERER_H

#pragma once

// Utility functions
#include <QOpenGLFunctions>
// Buffers and stuff
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
// Logging and debugging (print version and specs to console)
#include <QDebug>
// Shader program
#include <QOpenGLShaderProgram>
// Maths !!
#include <QMatrix4x4>

#include <vector>
#include <cmath>

class Vector3D;
class Particle;
class Element;
class Straight;
class Dipole;
class Quadrupole;
class Frodo;
class Beam;
class Accelerator;
class Renderer;

class Transform3D;
class Camera3D;

// Use class inheritance, needed where because we have 2 different circular definitions
// one with Window, one with Renderer and Drawable, and one with Accelerator and co.
#include "include/bundle/Renderer.bundle.h"
// Use class field size (otherwise compiler-chan in vewwy confusion)
#include "include/bundle/Transform3D.bundle.h"
#include "include/bundle/Camera3D.bundle.h"

#include "globals.h"

class OpenGLRenderer : public Renderer, protected QOpenGLFunctions {
public:
	OpenGLRenderer();
	virtual ~OpenGLRenderer();

	void init();
	void reset();
	void update();
	void clear();
	void begin();
	void end();
	void resize(int width, int height);

	virtual void draw(Accelerator const& acc) override;
	virtual void draw(Beam const& beam) override;
	virtual void draw(Dipole const& dipole) override;
	virtual void draw(Quadrupole const& quadrupole) override;
	virtual void draw(Straight const& straight) override;
	virtual void draw(Frodo const& frodo) override;
	virtual void draw(Particle const& particle) override;
	virtual void draw(Vector3D const& vec) override;

	void drawPoint(QVector3D const& pos);
	void drawAxes();
	void drawCylinder(QVector3D const& posIn, QVector3D const& posOut, double radius);
	void drawTorus(QVector3D const& center, double startAngle, double totalAngle, double curvature, double innerRadius);

private:
	// OpenGL state information (buffers and vertex array objects)
	QOpenGLBuffer buffer;
	QOpenGLVertexArrayObject object;
	QOpenGLShaderProgram * program;

	// Different offsets
	int offsetPea;
	int offsetSpaghetti;
	int offsetPenne;
	int offsetMacaroni;
	int offsetPancake;
	int offsetCube;

	// Model to world matrix
	Transform3D transform;
	// World to camera matrix
	Camera3D camera;
	// Camera to view matrix
	QMatrix4x4 projection;
};

#endif
