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

TARGET := run_testVector3D run_testParticle run_testAccelerator run_testConverter run_testException
OTESTPATH := ./test/build/
BTESTPATH := ./test/bin/
OPATH := ./build/
BPATH := ./bin/
DOXYPATH := ./doxydocs/


##################################################################
# vpath to tell him where to search .h .cpp .o
# when he wants to (re)build
##################################################################

vpath %.h ./src ./src/include ./test/lib
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
# Compilation of source files and classes
##################################################################

Vector3D.o: Vector3D.cpp Vector3D.h
	@echo [$@] Compiling...
	@$(CXX) $(CXXFLAGS) -c src/lib/Vector3D.cpp -o $(OPATH)$@ -I ./

Particle.o: Particle.cpp Particle.h
	@echo [$@] Compiling...
	@$(CXX) $(CXXFLAGS) -c src/lib/Particle.cpp -o $(OPATH)$@ -I ./

Element.o: Element.cpp Element.h
	@echo [$@] Compiling...
	@$(CXX) $(CXXFLAGS) -c src/lib/Element.cpp -o $(OPATH)$@ -I ./

Dipole.o: Dipole.cpp Dipole.h
	@echo [$@] Compiling...
	@$(CXX) $(CXXFLAGS) -c src/lib/Dipole.cpp -o $(OPATH)$@ -I ./

Quadrupole.o: Quadrupole.cpp Quadrupole.h
	@echo [$@] Compiling...
	@$(CXX) $(CXXFLAGS) -c src/lib/Quadrupole.cpp -o $(OPATH)$@ -I ./

Accelerator.o: Accelerator.cpp Accelerator.h
	@echo [$@] Compiling...
	@$(CXX) $(CXXFLAGS) -c src/lib/Accelerator.cpp -o $(OPATH)$@ -I ./


##################################################################
# Compilation of tests
##################################################################

Test.o: Test.cpp Test.h
	@echo [$@] Compiling...
	@$(CXX) $(CXXFLAGS) -c test/lib/Test.cpp -o $(OTESTPATH)$@ -I ./

testVector3D.o: testVector3D.cpp Vector3D.h Vector3D.cpp
	@echo [$@] Compiling...
	@$(CXX) $(CXXFLAGS) -c test/src/testVector3D.cpp -o $(OTESTPATH)$@ -I ./

testParticle.o: testParticle.cpp Particle.h Particle.cpp
	@echo [$@] Compiling...
	@$(CXX) $(CXXFLAGS) -c test/src/testParticle.cpp -o $(OTESTPATH)$@ -I ./

testAccelerator.o: testAccelerator.cpp Accelerator.h Accelerator.cpp
	@echo [$@] Compiling...
	@$(CXX) $(CXXFLAGS) -c test/src/testAccelerator.cpp -o $(OTESTPATH)$@ -I ./

testConverter.o: testConverter.cpp
	@echo [$@] Compiling...
	@$(CXX) $(CXXFLAGS) -c test/src/testConverter.cpp -o $(OTESTPATH)$@ -I ./

testException.o: testException.cpp
	@echo [$@] Compiling...
	@$(CXX) $(CXXFLAGS) -c test/src/testException.cpp -o $(OTESTPATH)$@ -I ./


##################################################################
# Links editor and creation of executables
##################################################################

testVector3D.bin: Vector3D.o testVector3D.o Test.o
	@echo [$@] Linking...
	@$(CXX) $(CXXFLAGS) test/build/testVector3D.o test/build/Test.o build/Vector3D.o -o $(BTESTPATH)$@

testParticle.bin: Vector3D.o Particle.o testParticle.o Test.o
	@echo [$@] Linking...
	@$(CXX) $(CXXFLAGS) test/build/testParticle.o test/build/Test.o build/Particle.o build/Vector3D.o -o $(BTESTPATH)$@

testAccelerator.bin: Vector3D.o Particle.o Element.o Dipole.o Quadrupole.o Accelerator.o testAccelerator.o Test.o
	@echo [$@] Linking...
	@$(CXX) $(CXXFLAGS) test/build/testAccelerator.o test/build/Test.o build/Accelerator.o build/Element.o build/Dipole.o build/Quadrupole.o build/Particle.o build/Vector3D.o -o $(BTESTPATH)$@

testConverter.bin: testConverter.o Test.o Vector3D.o
	@echo [$@] Linking...
	@$(CXX) $(CXXFLAGS) test/build/testConverter.o test/build/Test.o build/Vector3D.o -o $(BTESTPATH)$@

testException.bin: testException.o
	@echo [$@] Linking...
	@$(CXX) $(CXXFLAGS) test/build/testException.o -o $(BTESTPATH)$@


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

run_testAccelerator: testAccelerator.bin
	@echo [$@] Running tests...
	@$(BTESTPATH)/testAccelerator.bin
	@echo [$@] Success !

run_testConverter: testConverter.bin
	@echo [$@] Running tests...
	@$(BTESTPATH)/testConverter.bin
	@echo [$@] Success !

run_testException: testException.bin
	@echo [$@] Running tests...
	@$(BTESTPATH)/testException.bin
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

cleandocs:
	@rm -f -r $(DOXYPATH)*
	@echo Docs files removed correctly

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

docs: cleandocs
	@doxygen Doxyfile > /dev/null 2>&1
	@echo [$@] generated documentation

# docs:
# 	@pandoc docs/Index.md \
# 			docs/FolderStructure.md \
# 			docs/Conception.md \
# 			docs/Speedtests.md \
# 			docs/Journal.md \
# 			docs/Réponses.md \
# 			docs/Makefile.md \
# 			docs/Classes/* \
# 			-o docs/index.html \
# 			--columns 1000 \
# 			--include-in-header=docs/Pandoc/gh-pandoc.css.html \
# 			--include-in-header=docs/Pandoc/custom.css.html \
# 			--toc \
# 			--highlight-style pygments \
# 			--standalone
# 	@echo [$@] generated documentation

##################################################################
# doc: run index.html
##################################################################

run_docs: docs
	@xdg-open $(DOXYPATH)/html/index.html

