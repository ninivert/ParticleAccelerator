TEMPLATE = lib
CONFIG += staticlib
CONFIG += c++1z
LIBS += -lcommon
QT += core gui

OBJECTS_DIR += ../build
MOC_DIR += ../moc
VPATH += include include/bundle lib shaders

SOURCES += \
	# Physics simulation
	Vector3D.cpp \
	Particle.cpp \
	Element.cpp \
	Straight.cpp \
	Quadrupole.cpp \
	Frodo.cpp \
	Dipole.cpp \
	Accelerator.cpp \
	Beam.cpp \
	# Graphics
	Drawable.cpp \
	Renderer.cpp \
	TextRenderer.cpp \
	Camera3D.cpp \
	Transform3D.cpp \
	Input.cpp \
	OpenGLRenderer.cpp \
	Window.cpp \
	# Utility
	Convert.cpp \
	Test.cpp

HEADERS += \
	# Physics simulation
	Vector3D.h \
	Particle.h \
	Element.h \
	Straight.h \
	Quadrupole.h \
	Frodo.h \
	Dipole.h \
	Accelerator.h \
	Beam.h \
	# Graphics
	Drawable.h \
	Renderer.h \
	TextRenderer.h \
	Vertex.h \
	Geometry.h \
	Camera3D.h \
	Transform3D.h \
	Input.h \
	OpenGLRenderer.h \
	Window.h \
	# Utility
	Convert.h \
	Test.h \
	globals.h \
	exceptions.h
