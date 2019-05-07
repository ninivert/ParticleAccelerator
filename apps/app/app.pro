QT += core gui
TEMPLATE = app
CONFIG -= app_bundle

TARGET = app.bin
DESTDIR = ../../bin
OBJECTS_DIR += ../../build
MOC_DIR += ../../moc
INCLUDEPATH += ../../common
LIBS += -L../../common -lcommon
VPATH += include include/bundle lib shaders

CONFIG += c++1z
SOURCES = app.cpp

RESOURCES += \
	../../resources.qrc
