QT += core gui

TARGET = app.bin

DESTDIR = bin
OBJECTS_DIR += build
MOC_DIR += moc

CONFIG -= app_bundle
VPATH += src/include src/include/bundle src/lib src/shaders src

TEMPLATE = app

CONFIG += c++1z

SOURCES += \
	main.cpp \
	Vector3D.cpp \
	Particle.cpp \
	Element.cpp \
	Straight.cpp \
	Quadrupole.cpp \
	Frodo.cpp \
	Dipole.cpp \
	Accelerator.cpp \
	Drawable.cpp \
	Renderer.cpp \
	TextRenderer.cpp \
	Beam.cpp \
	Convert.cpp

HEADERS += \
	Vector3D.h \
	Particle.h \
	Element.h \
	Straight.h \
	Quadrupole.h \
	Frodo.h \
	Dipole.h \
	Accelerator.h \
	Drawable.h \
	Renderer.h \
	TextRenderer.h \
	Beam.h \
	Convert.h \
	globals.h \
	exceptions.h

RESOURCES += \
	resources.qrc
