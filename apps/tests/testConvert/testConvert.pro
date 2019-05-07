TARGET = testConvert.bin
DESTDIR = ../../../bin
OBJECTS_DIR += ../../../build
MOC_DIR += ../../../moc
INCLUDEPATH += ../../../common
LIBS += -L../../../common -lcommon
VPATH += include include/bundle lib shaders

CONFIG += c++1z
SOURCES = testConvert.cpp
