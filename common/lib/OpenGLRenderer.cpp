#include "include/bundle/OpenGLRenderer.bundle.h"

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
	glEnable(GL_LINE_SMOOTH);
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
	// Take a byte out of every dish !
	int spaghettiBytes(sizeof(GEOMETRY::SPAGHETTI[0]) * GEOMETRY::SPAGHETTI.size());
	int penneBytes(sizeof(GEOMETRY::PENNE[0]) * GEOMETRY::PENNE.size());
	int macaroniBytes(sizeof(GEOMETRY::MACARONI[0]) * GEOMETRY::MACARONI.size());
	int pancakeBytes(sizeof(GEOMETRY::PANCAKE[0]) * GEOMETRY::PANCAKE.size());
	int cubeBytes(sizeof(GEOMETRY::CUBE[0]) * GEOMETRY::CUBE.size());
	int offsetBytes(0), offsetSlots(0);
	buffer.allocate(spaghettiBytes + penneBytes + macaroniBytes + pancakeBytes + cubeBytes);
	buffer.write(offsetBytes, &GEOMETRY::SPAGHETTI.front(), spaghettiBytes);
	offsetSpaghetti = offsetSlots;
	offsetBytes += spaghettiBytes;
	offsetSlots += GEOMETRY::SPAGHETTI.size();
	buffer.write(offsetBytes, &GEOMETRY::PENNE.front(), penneBytes);
	offsetPenne = offsetSlots;
	offsetBytes += penneBytes;
	offsetSlots += GEOMETRY::PENNE.size();
	buffer.write(offsetBytes, &GEOMETRY::MACARONI.front(), macaroniBytes);
	offsetMacaroni = offsetSlots;
	offsetBytes += macaroniBytes;
	offsetSlots += GEOMETRY::MACARONI.size();
	buffer.write(offsetBytes, &GEOMETRY::PANCAKE.front(), pancakeBytes);
	offsetPancake = offsetSlots;
	offsetBytes += pancakeBytes;
	offsetSlots += GEOMETRY::PANCAKE.size();
	buffer.write(offsetBytes, &GEOMETRY::CUBE.front(), cubeBytes);
	offsetCube = offsetSlots;

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
	if (Input::isKeyPressed(Qt::Key_S)) translation -= camera.getForwardVector();
	if (Input::isKeyPressed(Qt::Key_W)) translation += camera.getForwardVector();
	if (Input::isKeyPressed(Qt::Key_D)) translation += camera.getRightVector();
	if (Input::isKeyPressed(Qt::Key_A)) translation -= camera.getRightVector();
	if (Input::isKeyPressed(Qt::Key_E)) translation += camera.getUpVector();
	if (Input::isKeyPressed(Qt::Key_Q)) translation -= camera.getUpVector();
	camera.translate(CONTROLS::TRANSLATION_SPEED * translation * coef);

	// Reset if backspace is pressed
	if (Input::isKeyPressed(Qt::Key_Backspace)) reset();
}

/**
 * Clearing
 */

void OpenGLRenderer::clear() {
	// Clear the background color we declared in initializeGL
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

/**
 * Begin drawing call
 */

void OpenGLRenderer::begin() {
	program->bind();
	object.bind();

	program->setUniformValue("worldToCamera", camera.getMatrix());
	program->setUniformValue("cameraToView", projection);
	program->setUniformValue("modelToWorld", transform.getMatrix());
	program->setUniformValue("color", 0, 0, 0);

	qDebug() << "============================================= REDRAW =============================================";
}

/**
 * Stop drawing call
 */

void OpenGLRenderer::end() {
	object.release();
	program->release();
}

/****************************************************************
 * Drawing
 ****************************************************************/

void OpenGLRenderer::draw(Accelerator const& acc) {
	drawAxes();

	acc.drawElements();
	acc.drawBeams();
}

void OpenGLRenderer::draw(Beam const& beam) {
	Q_UNUSED(beam);
}

void OpenGLRenderer::draw(Dipole const& dipole) {

	program->setUniformValue("color", 0.5, 1.0, 0.5);

	// drawTorus(center.toQVector3D(), posIn.toQVector3D(), posOut.toQVector3D(), totalAngle, curvature, innerRadius);

	transform.save();
	transform.reset();

	QVector3D posIn(dipole.getPosIn().toQVector3D());
	QVector3D posOut(dipole.getPosOut().toQVector3D());
	QVector3D center(dipole.getCenter().toQVector3D());
	double totalAngle(dipole.getTotalAngle());
	double inAngle(dipole.getInAngle());
	double outAngle(dipole.getOutAngle());
	double innerRadius(dipole.getRadius());
	double curvature(dipole.getCurvature());

	drawTorus(center, inAngle, outAngle, totalAngle, curvature, innerRadius);
}

void OpenGLRenderer::draw(Quadrupole const& quadrupole) {
	Vector3D posIn(quadrupole.getPosIn());
	Vector3D posOut(quadrupole.getPosOut());
	double radius(quadrupole.getRadius());

	program->setUniformValue("color", 1.0, 0.5, 0.5);

	drawCylinder(posIn.toQVector3D(), posOut.toQVector3D(), radius);
}

void OpenGLRenderer::draw(Straight const& straight) {
	Vector3D posIn(straight.getPosIn());
	Vector3D posOut(straight.getPosOut());
	double radius(straight.getRadius());

	program->setUniformValue("color", 0.5, 0.5, 1.0);

	drawCylinder(posIn.toQVector3D(), posOut.toQVector3D(), radius);
}

void OpenGLRenderer::draw(Frodo const& frodo) {
	frodo.drawElements();
}

void OpenGLRenderer::draw(Particle const& particle) {
	Q_UNUSED(particle);
}

void OpenGLRenderer::draw(Vector3D const& vec) {
	Q_UNUSED(vec);
}


/****************************************************************
 * Drawing figures
 ****************************************************************/

/**
 * Drawing axes
 */

void OpenGLRenderer::drawAxes() {
	transform.save();
	// X axis
	glLineWidth(10.0);
	program->setUniformValue("color", 1.0, 0.5, 0.5);
	program->setUniformValue("modelToWorld", transform.getMatrix());
	object.bind();
	glDrawArrays(GL_LINES, offsetSpaghetti, GEOMETRY::SPAGHETTI.size());
	// Y axis
	transform.rotate(90, 0, 0, 1);
	program->setUniformValue("color", 0.0, 0.8, 0.0);
	program->setUniformValue("modelToWorld", transform.getMatrix());
	object.bind();
	glDrawArrays(GL_LINES, offsetSpaghetti, GEOMETRY::SPAGHETTI.size());
	// Z axis
	transform.rotate(90, 1, 0, 0);
	program->setUniformValue("color", 0.5, 0.5, 1.0);
	program->setUniformValue("modelToWorld", transform.getMatrix());
	object.bind();
	glDrawArrays(GL_LINES, offsetSpaghetti, GEOMETRY::SPAGHETTI.size());
	transform.restore();
}

void OpenGLRenderer::drawCylinder(QVector3D const& posIn, QVector3D const& posOut, double radius) {
	transform.save();

	transform.rotate(QQuaternion::rotationTo(posIn - posOut, Transform3D::LocalRight));
	transform.scale((posIn - posOut).length(), radius, radius);
	transform.translate((posIn + posOut) / 2);

	program->setUniformValue("modelToWorld", transform.getMatrix());
	object.bind();
	glDrawArrays(GL_TRIANGLES, offsetPenne, GEOMETRY::PENNE.size());

	transform.restore();
}

void OpenGLRenderer::drawTorus(QVector3D const& center, double inAngle, double outAngle, double totalAngle, double curvature, double innerRadius) {
	transform.save();

	// TORUS NEEDS TO TAKE CURVATURE INTO ACCOUNT

	qDebug() << "\nTORUS BEGIN";

	qDebug() << "inAngle " << inAngle;
	qDebug() << "outAngle " << outAngle;
	qDebug() << "totalAngle " << totalAngle;

	qDebug() << transform.getMatrix();
	QQuaternion quat(QQuaternion::fromAxisAndAngle(Transform3D::LocalUp, outAngle * 180 / M_PI));
	qDebug() << "quat " << quat;
	transform.rotate(quat);
	qDebug() << transform.getMatrix();

	// Here we assume that the curvature is non-zero,
	// because otherwise the physics engine would have already died
	double radius(std::abs(1/curvature));

	transform.scale(radius, innerRadius/0.1, radius);
	transform.translate(center);

	double lambda(std::abs(totalAngle/(2*M_PI)));

	program->setUniformValue("modelToWorld", transform.getMatrix());
	object.bind();
	glDrawArrays(GL_TRIANGLES, offsetMacaroni, int(GEOMETRY::MACARONI.size() * lambda));

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
