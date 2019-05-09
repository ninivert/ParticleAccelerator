#include "include/bundle/Window.bundle.h"

/****************************************************************
 * General stuffs
 ****************************************************************/

Window::Window() : focus(true), acc(&engine) {
	// Cursor
	QCursor c;
	c.setPos(mapToGlobal(QPoint(width() / 2, height() / 2)));
	setCursor(c);
	Input::resetMouseDelta();

	// Accelerator initialization
	Vector3D pos_dep(3, 2, 0);
	Vector3D dir_frodo(0, -1, 0);
	Vector3D pos_fin;
	Vector3D dir_dipole(-1, -1, 0);

	for (int i = 0; i < 4; ++i) {

		pos_fin = pos_dep + 4 * dir_frodo;
		acc.addElement(Frodo(
			pos_dep, pos_fin,
			0.1, 1.2, 1,
			&engine
		));

		pos_dep = pos_fin;
		pos_fin += dir_dipole;

		acc.addElement(Dipole(
			pos_dep,
			pos_fin,
			0.1, 1, 5.89158,
			&engine
		));

		pos_dep = pos_fin;

		// -90° rotation
		dir_frodo ^= Vector3D(0, 0, 1);
		dir_dipole ^= Vector3D(0, 0, 1);
	}

	acc.closeElementLoop();

	acc.addParticle(Particle(
		Vector3D(3.01, 0, 0), 2,
		Vector3D(0, -2.64754e+08, 0),
		CONSTANTS::M_PROTON
	));

	acc.addParticle(Particle(
		Vector3D(2.99, 0, 0), 2,
		Vector3D(0, -2.64754e+08, 0),
		CONSTANTS::M_PROTON
	));
}

void Window::update() {
	if (focus) {
		Input::update();
		engine.update();

		// Cursor position
		QCursor c = cursor();
		c.setPos(mapToGlobal(QPoint(width() / 2, height() / 2)));
		c.setShape(Qt::BlankCursor);
		setCursor(c);
		Input::resetMouseDelta();

		// Schedule a redraw (VSync)
		QOpenGLWindow::update();
	}
}

void Window::teardownGL() {
	// engine destructor is invoked automatically
	// content destructor is invoked automatically
}

/****************************************************************
 * OpenGL stuffs
 ****************************************************************/

/**
 * Init
 */

void Window::initializeGL() {
	// Connect signals and slots
	connect(context(), SIGNAL(aboutToBeDestroyed()), this, SLOT(teardownGL()), Qt::DirectConnection);
	connect(this, SIGNAL(frameSwapped()), this, SLOT(update()));
	// Print info to the console
	printContextInformation();

	engine.init();
}

/**
 * Resize
 */

void Window::resizeGL(int width, int height) {
	engine.resize(width, height);
}

/**
 * Paint
 */

void Window::paintGL() {
	engine.begin();
	engine.clear();
	acc.draw();
	engine.end();
}

/****************************************************************
 * Focus
 ****************************************************************/

void Window::focusInEvent(QFocusEvent * ev) {
	focus = ev->gotFocus();
	Input::resetMouseDelta();
	// Schedule a redraw (VSync) (unpause)
	QOpenGLWindow::update();
}

void Window::focusOutEvent(QFocusEvent * ev) {
	focus = ev->gotFocus();
	QCursor c;
	c.setShape(Qt::ArrowCursor);
	setCursor(c);
	// pause because we are not calling QOpenGLWindow::update() when not focused
}

/****************************************************************
 * Qt Key stuffs
 ****************************************************************/

void Window::keyPressEvent(QKeyEvent * event) {
	if (event->isAutoRepeat()) event->ignore();
	else Input::registerKeyPress(event->key());
}

void Window::keyReleaseEvent(QKeyEvent * event) {
	if (event->isAutoRepeat()) event->ignore();
	else Input::registerKeyRelease(event->key());
}

void Window::mousePressEvent(QMouseEvent * event) {
	Input::registerMousePress(event->button());
}

void Window::mouseReleaseEvent(QMouseEvent * event) {
	Input::registerMouseRelease(event->button());
}

/****************************************************************
 * Context information
 ****************************************************************/

void Window::printContextInformation() {
	QString glType;
	QString glVersion;
	QString glProfile;

	// Get Version Information
	glType = (context()->isOpenGLES()) ? "OpenGL ES" : "OpenGL";
	// Get and cast GL Version to c-style string
	// glVersion = (const char*)(glGetString(GL_VERSION));
	glVersion = reinterpret_cast<const char*>(glGetString(GL_VERSION));

	// Get Profile Information
#define CASE(c) case QSurfaceFormat::c: glProfile = #c; break
	switch (format().profile()) {
		CASE(NoProfile);
		CASE(CoreProfile);
		CASE(CompatibilityProfile);
	}
#undef CASE

	// qPrintable() will print our QString w/o quotes around it.
	qDebug() << qPrintable(glType) << qPrintable(glVersion) << "(" << qPrintable(glProfile) << ")";
}
