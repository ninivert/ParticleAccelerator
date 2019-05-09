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
	exceptions.h \
	# Bundles
	# Physics simulation
	Vector3D.bundle.h \
	Particle.bundle.h \
	Element.bundle.h \
	Straight.bundle.h \
	Quadrupole.bundle.h \
	Frodo.bundle.h \
	Dipole.bundle.h \
	Accelerator.bundle.h \
	Beam.bundle.h \
	# Graphics
	Drawable.bundle.h \
	Renderer.bundle.h \
	TextRenderer.bundle.h \
	Camera3D.bundle.h \
	Transform3D.bundle.h \
	Input.bundle.h \
	OpenGLRenderer.bundle.h \
	Window.bundle.h \
	# Utility
	Convert.bundle.h \
	Test.bundle.h
