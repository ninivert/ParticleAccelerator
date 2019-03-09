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
CXXFLAGS = -std=c++17

# CXXFLAGS += -g
# For debugging

CXXFLAGS += -O2
# Speed optimisation


# =========================================
# To tell him where to search .o and exec files
# and where to put exec files (TARGET)
TARGET := testVector3D.bin
OTESTPATH := ./test/build/
BTESTPATH := ./test/bin/
OPATH := ./build/
BPATH := ./bin/


# =========================================
# vpath to tell him where to search .h .cpp .o
# when he wants to (re)build
vpath %.h ./src/include ./test/lib
vpath %.cpp ./src/lib ./test/lib/ ./test/src
vpath %.o ./build ./test/build
vpath %.bin ./bin ./test/bin


# =========================================
# .PHONY for all non file-creating commands
# ->    make clean
.PHONY: all clean cleanbuild cleanbin
all: $(TARGET)


# =========================================
# Compilation SRC
Vector3D.o: Vector3D.cpp Vector3D.h
	@echo [$@] Compiling...
	@$(CXX) $(CXXFLAGS) -c src/lib/Vector3D.cpp -o $(OPATH)$@ -I ./


# =========================================
# Compilation of TESTS
Test.o: Test.cpp Test.h
	@echo [$@] Compiling...
	@$(CXX) $(CXXFLAGS) -c test/lib/Test.cpp -o $(OTESTPATH)$@ -I ./

testVector3D.o: testVector3D.cpp Vector3D.h
	@echo [$@] Compiling...
	@$(CXX) $(CXXFLAGS) -c test/src/testVector3D.cpp -o $(OTESTPATH)$@ -I ./


# =========================================
# Links editor and creation of executbles
testVector3D.bin:Vector3D.o testVector3D.o Test.o
	@echo [$@] Linking...
	@$(CXX) $(CXXFLAGS) test/build/testVector3D.o test/build/Test.o build/Vector3D.o -o $(BTESTPATH)$@


# =========================================
# Run tests
run_testVector3D: testVector3D.bin
	@echo Running [$@]
	@$(BTESTPATH)/testVector3D.bin


# =========================================
# Run program
# "run_ExecutableName": "ExecutableName_Created.bin"
#	@echo Running [$@]
# 	@$<


# =========================================
# clean
clean: cleanbin cleanbuild

cleanbin:
	@rm -f $(BPATH)* $(BTESTPATH)*
	@echo Bin files removed correctly

cleanbuild:
	@rm -f $(OPATH)* $(OTESTPATH)*
	@echo Build files removed correctly
