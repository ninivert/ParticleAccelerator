##################################################################
# Flags
##################################################################

CXX = g++
CC = $(CXX)
CXXFLAGS = -std=c++17

# For debugging
# CXXFLAGS += -g

# Speed optimisation
CXXFLAGS += -O2


##################################################################
# To tell him where to search .o and exec files
# and where to put exec files (TARGET)
##################################################################

TARGET := testVector3D.bin testParticle.bin testAccelerator1.bin
OTESTPATH := ./test/build/
BTESTPATH := ./test/bin/
OPATH := ./build/
BPATH := ./bin/


##################################################################
# vpath to tell him where to search .h .cpp .o
# when he wants to (re)build
##################################################################

vpath %.h ./src/include ./test/lib
vpath %.cpp ./src/lib ./test/lib/ ./test/src
vpath %.o ./build ./test/build
vpath %.bin ./bin ./test/bin


##################################################################
# .PHONY for all non file-creating commands
# ->    make clean
##################################################################

.PHONY: all clean cleanbuild cleanbin dir docs
all: dir docs $(TARGET)


##################################################################
# Track updates in header files
##################################################################

globals.h:
	@echo [$@] Updates tracked...

Converter.h:
	@echo [$@] Updates tracked...


##################################################################
# Compilation of source files and classes
##################################################################

Vector3D.o: Vector3D.cpp Vector3D.h globals.h
	@echo [$@] Compiling...
	@$(CXX) $(CXXFLAGS) -c src/lib/Vector3D.cpp -o $(OPATH)$@ -I ./

Particle.o: Particle.cpp Particle.h Converter.h globals.h
	@echo [$@] Compiling...
	@$(CXX) $(CXXFLAGS) -c src/lib/Particle.cpp -o $(OPATH)$@ -I ./

Element.o: Element.cpp Element.h globals.h
	@echo [$@] Compiling...
	@$(CXX) $(CXXFLAGS) -c src/lib/Element.cpp -o $(OPATH)$@ -I ./

MagnetElement.o: MagnetElement.cpp MagnetElement.h globals.h
	@echo [$@] Compiling...
	@$(CXX) $(CXXFLAGS) -c src/lib/MagnetElement.cpp -o $(OPATH)$@ -I ./

ElectrElement.o: ElectrElement.cpp ElectrElement.h globals.h
	@echo [$@] Compiling...
	@$(CXX) $(CXXFLAGS) -c src/lib/ElectrElement.cpp -o $(OPATH)$@ -I ./

Accelerator.o: Accelerator.cpp Accelerator.h globals.h
	@echo [$@] Compiling...
	@$(CXX) $(CXXFLAGS) -c src/lib/Accelerator.cpp -o $(OPATH)$@ -I ./


##################################################################
# Compilation of tests
##################################################################

Test.o: Test.cpp Test.h globals.h
	@echo [$@] Compiling...
	@$(CXX) $(CXXFLAGS) -c test/lib/Test.cpp -o $(OTESTPATH)$@ -I ./

testVector3D.o: testVector3D.cpp Vector3D.h Vector3D.cpp
	@echo [$@] Compiling...
	@$(CXX) $(CXXFLAGS) -c test/src/testVector3D.cpp -o $(OTESTPATH)$@ -I ./

testParticle.o: testParticle.cpp Particle.h Particle.cpp Converter.h
	@echo [$@] Compiling...
	@$(CXX) $(CXXFLAGS) -c test/src/testParticle.cpp -o $(OTESTPATH)$@ -I ./

testAccelerator1.o: testAccelerator1.cpp Accelerator.h Accelerator.cpp Converter.h
	@echo [$@] Compiling...
	@$(CXX) $(CXXFLAGS) -c test/src/testAccelerator1.cpp -o $(OTESTPATH)$@ -I ./

testConverter.o: testConverter.cpp Converter.h
	@echo [$@] Compiling...
	@$(CXX) $(CXXFLAGS) -c test/src/testConverter.cpp -o $(OTESTPATH)$@ -I ./


##################################################################
# Links editor and creation of executables
##################################################################

testVector3D.bin: Vector3D.o testVector3D.o Test.o
	@echo [$@] Linking...
	@$(CXX) $(CXXFLAGS) test/build/testVector3D.o test/build/Test.o build/Vector3D.o -o $(BTESTPATH)$@

testParticle.bin: Vector3D.o Particle.o testParticle.o Test.o
	@echo [$@] Linking...
	@$(CXX) $(CXXFLAGS) test/build/testParticle.o test/build/Test.o build/Particle.o build/Vector3D.o -o $(BTESTPATH)$@

testAccelerator1.bin: Vector3D.o Particle.o Element.o MagnetElement.o ElectrElement.o testAccelerator1.o Test.o
	@echo [$@] Linking...
	@$(CXX) $(CXXFLAGS) test/build/testAccelerator1.o test/build/Test.o build/Element.o build/MagnetElement.o build/ElectrElement.o build/Particle.o build/Vector3D.o -o $(BTESTPATH)$@

testConverter.bin: testConverter.o Test.o Vector3D.o
	@echo [$@] Linking...
	@$(CXX) $(CXXFLAGS) test/build/testConverter.o test/build/Test.o build/Vector3D.o -o $(BTESTPATH)$@


##################################################################
# Run tests
##################################################################

run_testVector3D: testVector3D.bin
	@echo [$@] Running tests...
	@$(BTESTPATH)/testVector3D.bin
	@echo [$@] Success !

run_testParticle: testParticle.bin
	@echo [$@] Running tests...
	@$(BTESTPATH)/testParticle.bin
	@echo [$@] Success !

run_testAccelerator1: testAccelerator1.bin
	@echo [$@] Running tests...
	@$(BTESTPATH)/testAccelerator1.bin
	@echo [$@] Success !

run_testConverter: testConverter.bin
	@echo [$@] Running tests...
	@$(BTESTPATH)/testConverter.bin
	@echo [$@] Success !


##################################################################
# clean output and build files
##################################################################

clean: cleanbin cleanbuild

cleanbin:
	@rm -f $(BPATH)* $(BTESTPATH)*
	@echo Bin files removed correctly

cleanbuild:
	@rm -f $(OPATH)* $(OTESTPATH)*
	@echo Build files removed correctly


##################################################################
# dir: make necessary directories for the code to compile
##################################################################

dir:
	@mkdir $(OTESTPATH) -p
	@mkdir $(BTESTPATH) -p
	@mkdir $(OPATH) -p
	@mkdir $(BPATH) -p
	@echo [$@] created necessary directories

##################################################################
# doc: generate documentation index.html
##################################################################

docs:
	@pandoc docs/Index.md \
			docs/FolderStructure.md \
			docs/Conception.md \
			docs/Speedtests.md \
			docs/Journal.md \
			docs/Réponses.md \
			docs/Makefile.md \
			docs/Classes/* \
			-o docs/index.html \
			--columns 1000 \
			--include-in-header=docs/Pandoc/gh-pandoc.css.html \
			--include-in-header=docs/Pandoc/custom.css.html \
			--toc \
			--highlight-style pygments \
			--standalone
	@echo [$@] generated documentation

##################################################################
# doc: run index.html
##################################################################

run_docs: docs
	@xdg-open docs/index.html

