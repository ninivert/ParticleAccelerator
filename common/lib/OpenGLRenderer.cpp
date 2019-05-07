#include "include/Drawable.h"
#include "include/Renderer.h"

#include "include/Vector3D.h"
#include "include/Particle.h"
#include "include/Element.h"
#include "include/Straight.h"
#include "include/Dipole.h"
#include "include/Quadrupole.h"
#include "include/Beam.h"
#include "include/Accelerator.h"

#include "include/OpenGLRenderer.h"

/****************************************************************
 * Constructor
 ****************************************************************/

OpenGLRenderer::OpenGLRenderer() {}

OpenGLRenderer::~OpenGLRenderer() {
	// Actually destroy our OpenGL information
	object.destroy();
	buffer.destroy();
	delete program;
	qDebug() << "OpenGLRenderer destroyed";
}

/****************************************************************
 * Methods
 ****************************************************************/

/**
 * Initialization
 */

void OpenGLRenderer::init() {
	initializeOpenGLFunctions();

	// Tell OpenGL that we will only draw faces which wind counter-clockwise
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	// Set global information
	glClearColor(236/256.0, 240/256.0, 241/256.0, 1.0);

	// Shader stuffs
	// Create Shader (Do not release until VAO is created)
	program = new QOpenGLShaderProgram();
	program->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/common/shaders/vertex.glsl");
	program->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/common/shaders/fragment.glsl");
	program->link();
	program->bind(); // Bind the shader so that it is the current active shader.

	// Cache uniform locations
	// modelToWorldLocation = program->uniformLocation("modelToWorld");
	// worldToCameraLocation = program->uniformLocation("worldToCamera");
	// cameraToViewLocation = program->uniformLocation("cameraToView");
	// colorLocation = program->uniformLocation("color");

	// Create Buffer (VBO) (Do not release until VAO is created)
	buffer.create();
	buffer.bind();
	buffer.setUsagePattern(QOpenGLBuffer::StaticDraw); // We never change the data => static
	int macaroniBytes(sizeof(GEOMETRY::MACARONI[0]) * GEOMETRY::MACARONI.size());
	int spaghettiBytes(sizeof(GEOMETRY::SPAGHETTI[0]) * GEOMETRY::SPAGHETTI.size());
	buffer.allocate(macaroniBytes + spaghettiBytes);
	buffer.write(0, &GEOMETRY::MACARONI.front(), macaroniBytes);
	buffer.write(macaroniBytes, &GEOMETRY::SPAGHETTI.front(), spaghettiBytes);

	// Create Vertex Array Object (VAO)
	object.create();
	object.bind();

	// Enable positions, colors are set during the call
	program->enableAttributeArray("position");
	program->setAttributeBuffer("position", GL_FLOAT, SimpleVertex::positionOffset(), SimpleVertex::PositionTupleSize, SimpleVertex::stride());

	// Release (unbind) all
	object.release();
	buffer.release();
	program->release();

	reset();
}

/**
 * Reset
 */

void OpenGLRenderer::reset() {
	camera.reset();
	camera.translate(0, 0, 5);
}

/**
 * Update
 */

void OpenGLRenderer::update() {
	double coef = Input::isKeyPressed(Qt::Key_Shift) ? CONTROLS::SLOWMO : 1;

	// Camera rotations
	// Rotate the camera around its (here absolute) up axis
	camera.rotate(-CONTROLS::ROTATION_SPEED * Input::getMouseDelta().x() * coef, Camera3D::LocalUp);
	// Rotate the camera around its (here relative) right axis
	camera.rotate(-CONTROLS::ROTATION_SPEED * Input::getMouseDelta().y() * coef, camera.getRightVector());

	// Camera Translations
	QVector3D translation;
	if (Input::isKeyPressed(Qt::Key_W)) translation += camera.getForwardVector();
	if (Input::isKeyPressed(Qt::Key_S)) translation -= camera.getForwardVector();
	if (Input::isKeyPressed(Qt::Key_D)) translation += camera.getRightVector();
	if (Input::isKeyPressed(Qt::Key_A)) translation -= camera.getRightVector();
	if (Input::isKeyPressed(Qt::Key_E)) translation += camera.getUpVector();
	if (Input::isKeyPressed(Qt::Key_Q)) translation -= camera.getUpVector();
	camera.translate(CONTROLS::TRANSLATION_SPEED * translation * coef);

	// Reset if backspace is pressed
	if (Input::isKeyPressed(Qt::Key_Backspace)) reset();
}

/****************************************************************
 * Drawing
 ****************************************************************/

void OpenGLRenderer::draw(Accelerator const& acc) {
	Q_UNUSED(acc);

	// Clear the background color we declared in initializeGL
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Render using our shader
	program->bind();
	program->setUniformValue("worldToCamera", camera.getMatrix());
	program->setUniformValue("cameraToView", projection);
	program->setUniformValue("modelToWorld", transform.getMatrix());
	program->setUniformValue("color", 0, 0, 0);

	object.bind();
	transform.rotate(1, 0, 1, 0);
	program->setUniformValue("modelToWorld", transform.getMatrix());
	glDrawArrays(GL_LINES, 0, GEOMETRY::MACARONI.size() / 4);

	drawAxes();

	object.release();
	program->release();
}

void OpenGLRenderer::draw(Beam const& beam) {
	Q_UNUSED(beam);
}

void OpenGLRenderer::draw(Dipole const& dipole) {
	Q_UNUSED(dipole);
}

void OpenGLRenderer::draw(Quadrupole const& quadrupole) {
	Q_UNUSED(quadrupole);
}

void OpenGLRenderer::draw(Straight const& straight) {
	Q_UNUSED(straight);
}

void OpenGLRenderer::draw(Particle const& particle) {
	Q_UNUSED(particle);
}

void OpenGLRenderer::draw(Vector3D const& vec) {
	Q_UNUSED(vec);
}


/**
 * Drawing axes
 */

void OpenGLRenderer::drawAxes() {
	transform.save();
	transform.reset();
	// X axis
	program->setUniformValue("color", 1.0, 0.0, 0.0);
	program->setUniformValue("modelToWorld", transform.getMatrix());
	object.bind();
	glDrawArrays(GL_LINES, GEOMETRY::MACARONI.size(), GEOMETRY::SPAGHETTI.size());
	// Y axis
	transform.rotate(90, 0, 0, 1);
	program->setUniformValue("color", 0.0, 1.0, 0.0);
	program->setUniformValue("modelToWorld", transform.getMatrix());
	object.bind();
	glDrawArrays(GL_LINES, GEOMETRY::MACARONI.size(), GEOMETRY::SPAGHETTI.size());
	// Z axis
	transform.rotate(90, 1, 0, 0);
	program->setUniformValue("color", 0.0, 0.0, 1.0);
	program->setUniformValue("modelToWorld", transform.getMatrix());
	object.bind();
	glDrawArrays(GL_LINES, GEOMETRY::MACARONI.size(), GEOMETRY::SPAGHETTI.size());
	transform.restore();
}

/**
 * Resize event
 */

void OpenGLRenderer::resize(int width, int height) {
	projection.setToIdentity();
	// WARNING: camera near plane needs to be strictly bigger than 0 for the depth test to work !
	projection.perspective(GRAPHICS::FOV, width / double(height), GRAPHICS::CLOSE_PLANE, GRAPHICS::FAR_PLANE);
}
