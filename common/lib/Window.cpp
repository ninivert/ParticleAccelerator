#include "globals.h"

#include "include/Drawable.h"
#include "include/Renderer.h"

#include "include/Vector3D.h"
#include "include/Particle.h"
#include "include/Element.h"
#include "include/Beam.h"

#include "include/Accelerator.h"

#include "include/Vertex.h"
#include "include/Transform3D.h"
#include "include/Camera3D.h"
#include "include/Input.h"
#include "include/Geometry.h"

#include "include/OpenGLRenderer.h"

#include "include/Window.h"

/****************************************************************
 * General stuffs
 ****************************************************************/

Window::Window() : focus(true), acc(&engine) {
	QCursor c;
	c.setPos(mapToGlobal(QPoint(width() / 2, height() / 2)));
	setCursor(c);
	Input::resetMouseDelta();
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
	acc.draw();
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
