TARGET = exerciceP13.bin
DESTDIR = ../../../bin
OBJECTS_DIR += ../../../build
MOC_DIR += ../../../moc
INCLUDEPATH += ../../../common
LIBS += -L../../../common -lcommon
VPATH += include include/bundle lib shaders

CONFIG += c++1z
SOURCES = exerciceP13.cpp
