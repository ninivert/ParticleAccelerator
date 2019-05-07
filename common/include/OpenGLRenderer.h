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

class Accelerator;
class Beam;
class Accelerator;
class Element;
class Dipole;
class Quadrupole;
class Straight;
class Particle;
class Vector3D;
class Renderer;

#include "globals.h"
#include "include/Vertex.h"
#include "include/Transform3D.h"
#include "include/Camera3D.h"
#include "include/Input.h"
#include "include/Geometry.h"
#include "include/Renderer.h"

class OpenGLRenderer : public Renderer, protected QOpenGLFunctions {
public:
	OpenGLRenderer();
	virtual ~OpenGLRenderer();

	void init();
	void reset();
	void update();
	void resize(int width, int height);

	virtual void draw(Accelerator const& acc) override;
	virtual void draw(Beam const& beam) override;
	virtual void draw(Dipole const& dipole) override;
	virtual void draw(Quadrupole const& quadrupole) override;
	virtual void draw(Straight const& straight) override;
	virtual void draw(Particle const& particle) override;
	virtual void draw(Vector3D const& vec) override;

	void drawAxes();

private:
	// OpenGL state information (buffers and vertex array objects)
	QOpenGLBuffer buffer;
	QOpenGLVertexArrayObject object;
	QOpenGLShaderProgram * program;

	// Model to world matrix
	Transform3D transform;
	// World to camera matrix
	Camera3D camera;
	// Camera to view matrix
	QMatrix4x4 projection;
};

#endif
