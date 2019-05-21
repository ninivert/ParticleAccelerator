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
// Timer
#include <QTime>

#include <vector>
#include <cmath>

class Vector3D;
class Particle;
class Proton;
class AntiProton;
class Electron;
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

	/****************************************************************
	 * Normal OpenGL stuffs
	 ****************************************************************/

	/**
	 * Constructor for OpenGLRenderer
	 */

	OpenGLRenderer();

	/**
	 * Virtual destructor
	 */

	virtual ~OpenGLRenderer() override;

	/**
	 * Initializer: sets openGL globals and prepares buffer and vertex array object (VAO)
	 */

	void init();

	/**
	 * Reset the camera
	 */

	void reset();

	/**
	 * Update the controls and Input manager
	 */

	void update();

	/**
	 * Clear color and depth buffer bits
	 */

	void clear();

	/**
	 * Prepare the openGL context for drawing
	 */

	void begin();

	/**
	 * Release openGL context
	 */

	void end();

	/**
	 * Resize the renderer
	 */

	void resize(int width, int height);

	/****************************************************************
	 * Inherited from Renderer
	 ****************************************************************/

	/**
	 * Draw an Accelerator element
	 */

	virtual void draw(Accelerator const& acc) override;

	/**
	 * Draw a Beam
	 */

	virtual void draw(Beam const& beam) override;

	/**
	 * Draw a Dipole element
	 */

	virtual void draw(Dipole const& dipole) override;

	/**
	 * Draw a Quadrupole element
	 */

	virtual void draw(Quadrupole const& quadrupole) override;

	/**
	 * Draw a Straight element
	 */

	virtual void draw(Straight const& straight) override;

	/**
	 * Draw a Frodo element
	 */

	virtual void draw(Frodo const& frodo) override;

	/**
	 * Draw a Particle
	 */

	virtual void draw(Particle const& particle) override;

	/**
	 * Draw a Proton
	 */

	virtual void draw(Proton const& proton) override;

	/**
	 * Draw an AntiProton
	 */

	virtual void draw(AntiProton const& antiproton) override;

	/**
	 * Draw an Electron
	 */

	virtual void draw(Electron const& electron) override;

	/**
	 * Draw a Vector3D
	 */

	virtual void draw(Vector3D const& vec) override;

	/****************************************************************
	 * General geometry
	 ****************************************************************/

	/**
	 * Draw a generalized point (Geometry::Pea) at pos
	 */

	void drawPoint(QVector3D const& pos);

	/**
	 * Draw the carthesian coordinate system axes
	 */

	void drawAxes();

	/**
	 * Draw a generalized cylinder (Geometry::Penne)
	 */

	void drawCylinder(QVector3D const& posIn, QVector3D const& posOut, double radius);

	/**
	 * Draw a generalized torus (Geometry::Macaroni)
	 */

	void drawTorus(QVector3D const& center, double startAngle, double totalAngle, double curvature, double innerRadius);

private:
	/****************************************************************
	  * OpenGL state information (buffers and vertex array objects)
	  ****************************************************************/

	/**
	 * Vertex buffer object
	 */

	QOpenGLBuffer buffer;

	/**
	 * Vertex array object
	 */

	QOpenGLVertexArrayObject object;

	/**
	 * OpenGL shader program
	 */

	QOpenGLShaderProgram * program;

	/****************************************************************
	 * Buffer offsets
	 ****************************************************************/

	/**
	 * Pea geometry offset in buffer
	 */

	int offsetPea;

	/**
	 * Spaghetti geometry offset in buffer
	 */

	int offsetSpaghetti;

	/**
	 * Penne geometry offset in buffer
	 */

	int offsetPenne;

	/**
	 * Macaroni geometry offset in buffer
	 */

	int offsetMacaroni;

	/**
	 * Pancake geometry offset in buffer
	 */

	int offsetPancake;

	/**
	 * Pea geometry offset in buffer
	 */

	int offsetCube;

	/****************************************************************
	 * Matrices and transforms
	 ****************************************************************/

	/**
	 * Model to world matrix
	 */

	Transform3D transform;

	/**
	 * World to camera matrix
	 */

	Camera3D camera;

	/**
	 * Camera to view matrix
	 */

	QMatrix4x4 projection;

	/****************************************************************
	 * Timer
	 ****************************************************************/

	QTime time;
};

#endif
