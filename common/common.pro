TEMPLATE = lib
CONFIG = staticlib
CONFIG += c++1z
OBJECTS_DIR += ../build
MOC_DIR += ../moc
VPATH += include include/bundle lib shaders

SOURCES += \
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
	Convert.cpp \
	Test.cpp

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
	Test.h \
	globals.h \
	exceptions.h
