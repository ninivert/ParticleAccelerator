#include <QGuiApplication>
#include "include/bundle/Window.bundle.h"

/**
 * Following this tutorial
 * https://www.trentreed.net/topics/qt-framework/
 * which I refactored (to follow OOP guidelines), expanded and added to
 */

int main(int argc, char *argv[]) {
	QGuiApplication app(argc, argv);

	// Set OpenGL Version information
	// Note: This format must be set before show() is called.
	QSurfaceFormat format;
	format.setRenderableType(QSurfaceFormat::OpenGL);
	format.setProfile(QSurfaceFormat::CoreProfile);
	format.setVersion(3, 3);
	format.setSamples(4); // antialising, 4 passes seems nice

	// Set the window up (QWidget)
	Window window;
	window.setFormat(format);
	window.resize(QSize(800, 600));
	window.show();

	return app.exec();
}
