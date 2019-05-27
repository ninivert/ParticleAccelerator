#ifndef WINDOW_H
#define WINDOW_H

#pragma once

// Allows us to provide OpenGL abstractions without the need for the Qt5Widgets module.
#include <QOpenGLWindow>
#include <QDebug>
#include <QString>
// Key strokes
#include <QKeyEvent>
// Timer
#include <QTime>

// Title generation
#include <string>

class OpenGLRenderer;
class Accelerator;

// Needed because the compiler needs to know the size of the class
#include "include/bundle/OpenGLRenderer.bundle.h"
#include "include/bundle/Accelerator.bundle.h"

#include "globals.h"

/**
 * Manages the display of the OpenGL context
 */

class Window : public QOpenGLWindow {
	// If it finds one or more class declarations that contain the Q_OBJECT macro, it produces a C++ source file containing the meta-object code for those classes.
	// Among other things, meta-object code is required for the signals and slots mechanism, the run-time type information, and the dynamic property system.
	Q_OBJECT

public:
	// General constructor
	Window();

	/**
	 * Qt constructor
	 */

	virtual void initializeGL() override;

	/**
	 * Qt Resize event
	 */

	virtual void resizeGL(int width, int height) override;

	/**
	 * Qt paint event
	 */

	virtual void paintGL() override;

	/**
	 * Qt windows focus gained event
	 */

	virtual void focusInEvent(QFocusEvent * ev) override;

	/**
	 * Qt window focus lost event
	 */

	virtual void focusOutEvent(QFocusEvent * ev) override;

protected slots:
	// https://doc.qt.io/qt-5/signalsandslots.html
	// TL;DR: slots are used as an alternative to a callback
	// Qt's widgets have many predefined signals, but we can always subclass widgets to add our own signals to them.
	// A slot is a function that is called in response to a particular signal.

	/**
	 * Destructor for OpenGL elements
	 */

	void teardownGL();

	// General update function
	// Many tutorials talk about doing this with QTimer,
	// which is possible. However, it’s more common in modern graphics programming
	// to schedule a redraw immediately after VSync,
	// and by default Qt5 starts up with VSync enabled.

	/**
	 * VSync update function, called by the system whenever the frame needs to be redrawn
	 */

	void update();

protected:
	virtual void keyPressEvent(QKeyEvent * event) override;
	virtual void keyReleaseEvent(QKeyEvent * event) override;
	virtual void mousePressEvent(QMouseEvent * event) override;
	virtual void mouseReleaseEvent(QMouseEvent * event) override;

private:
	/**
	 * This helper function will print information about the OpenGL Context we have acquired, for debugging purposes.
	 */

	void printContextInformation();

	/**
	 * Does the window have focus ?
	 */

	bool focus;

	/**
	 * Is the physics simulation paused ?
	 */

	bool pause;

	/**
	 * Actual rendering and OpenGL stuffs is handed off to the separate OpenGLRenderer class
	 */

	OpenGLRenderer engine;

	/**
	 * Content to draw
	 */

	Accelerator acc;

	/**
	 * Keep track of the time between two frames (updates)
	 */

	QTime timer;

	/**
	 * Frames since the last FPS counter refresh
	 */

	unsigned int frames;

	/**
	 * Iterations per second for the physics engine
	 */

	double engineSpeed;
};

#endif
