# Execute clean, clean_all only when asked
# ->    make clean

.PHONY: clean clean_all

CXX = g++
CC = $(CXX)
CXXFLAGS = -std=c++11

# CXXFLAGS += -g
# For debugging

CXXFLAGS += -O2
# Speed optimisation

# The :: tells Makefile that
# there won't be any shell cmd afterwards
all:: testVector3D

# =========================================
# Compilation of Vector3D
Vector3D.o: ./src/lib/Vector3D.cpp ./src/include/Vector3D.h
	g++ -c src/lib/Vector3D.cpp -o build/Vector3D.o -I ./





# =========================================
# Compilation of tests
Test.o: ./test/lib/Test.cpp ./test/lib/Test.h
	g++ -c test/lib/Test.cpp -o test/build/Test.o -I ./

testVector3D.o: ./test/src/testVector3D.cpp ./src/include/Vector3D.h
	g++ -c test/src/testVector3D.cpp -o test/build/testVector3D.o -I ./




# =========================================
# Compilation of all .o
.o:: Vector3D.o testVector3D.o Test.o


# =========================================
# Links editor and creation of executbles
testVector3D: .o
	g++ test/build/testVector3D.o test/build/Test.o build/Vector3D.o  -o test/bin/testVector3D

# =========================================
# Run tests
run_testVector3D: testVector3D
	./test/bin/testVector3D

# =========================================
# Run program
"run_ExecutableName": "ExecutableName_Created"


# =========================================
# clean
clean:
	rm ./build/*.o; \
		rm ./test/build/*.o

clean_all: clean
	rm ./bin/*; \
		rm ./test/bin/*
