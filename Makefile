# To UPDATE :
# - vapth for executables
# - Compilation of SRC
# - Compilation of TESTS
# - Links editor and creation of executbles
# - Run tests
# - Run program


# =========================================
# =========================================
CXX = g++
CC = $(CXX)
CXXFLAGS = -std=c++11

# CXXFLAGS += -g
# For debugging

CXXFLAGS += -O2
# Speed optimisation


# =========================================
# To tell him where to search .o and exec files
OTESTPATH := ./test/build/
BTESTPATH := ./test/bin/
OPATH := ./build/
BPATH := ./bin/


# =========================================
# vpath to tell him where to search .h .cpp .o
# when he wants to (re)build
vpath %.h ./src/include ./test/lib/
vpath %.cpp ./src/lib ./test/lib/ ./test/src/
vpath %.o ./build ./test/build/


# =========================================
# vapth to tell him where to search executables
# vpath testVector3D ./test/bin/testVector3D


# =========================================
# all + .PHONY: clean, clean_all only when asked
# ->    make clean
all: ./test/bin/testVector3D

.PHONY: all clean cleanall

# =========================================
# Compilation SRC
Vector3D.o: Vector3D.cpp Vector3D.h
	g++ -c src/lib/Vector3D.cpp -o build/Vector3D.o -I ./


# =========================================
# Compilation of TESTS
Test.o: Test.cpp Test.h
	g++ -c test/lib/Test.cpp -o test/build/Test.o -I ./

testVector3D.o: testVector3D.cpp Vector3D.h
	g++ -c test/src/testVector3D.cpp -o test/build/testVector3D.o -I ./


# =========================================
# Links editor and creation of executbles
./test/bin/testVector3D:Vector3D.o testVector3D.o Test.o
	g++ test/build/testVector3D.o test/build/Test.o build/Vector3D.o -o test/bin/testVector3D


# =========================================
# Run tests
run_testVector3D: ./test/bin/testVector3D
	$(addprefix $(BTESTPATH), testVector3D)


# =========================================
# Run program
# "run_ExecutableName": "ExecutableName_Created"
# 	./../bin/ExecutableName_Created


# =========================================
# clean
clean:
	@rm -f $(OPATH)* $(OTESTPATH)*

cleanall: clean
	@rm -f $(BPATH)* $(BTESTPATH)*
