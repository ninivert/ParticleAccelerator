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

TARGET := run_testVector3D run_testParticle run_testElement run_testAccelerator run_testConvert run_testException run_testRenderer
OTESTPATH := ./test/build/
BTESTPATH := ./test/bin/
OPATH := ./build/
BPATH := ./bin/
DOXYPATH := ./doxydocs/


##################################################################
# vpath to tell him where to search .h .cpp .o
# when he wants to (re)build
##################################################################

vpath %.h ./src ./src/include ./src/include/bundle ./test/lib
vpath %.cpp ./src/lib ./test/lib/ ./test/src ./test/exercices
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

Straight.o: Straight.cpp Straight.h
	@echo [$@] Compiling...
	@$(CXX) $(CXXFLAGS) -c src/lib/Straight.cpp -o $(OPATH)$@ -I ./

Accelerator.o: Accelerator.cpp Accelerator.h
	@echo [$@] Compiling...
	@$(CXX) $(CXXFLAGS) -c src/lib/Accelerator.cpp -o $(OPATH)$@ -I ./

Drawable.o: Drawable.cpp Drawable.h
	@echo [$@] Compiling...
	@$(CXX) $(CXXFLAGS) -c src/lib/Drawable.cpp -o $(OPATH)$@ -I ./

Renderer.o: Renderer.cpp Renderer.h
	@echo [$@] Compiling...
	@$(CXX) $(CXXFLAGS) -c src/lib/Renderer.cpp -o $(OPATH)$@ -I ./

TextRenderer.o: TextRenderer.cpp TextRenderer.h
	@echo [$@] Compiling...
	@$(CXX) $(CXXFLAGS) -c src/lib/TextRenderer.cpp -o $(OPATH)$@ -I ./

Convert.o: Convert.cpp Convert.h
	@echo [$@] Compiling...
	@$(CXX) $(CXXFLAGS) -c src/lib/Convert.cpp -o $(OPATH)$@ -I ./


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

testElement.o: testElement.cpp Element.h Element.cpp
	@echo [$@] Compiling...
	@$(CXX) $(CXXFLAGS) -c test/src/testElement.cpp -o $(OTESTPATH)$@ -I ./

testAccelerator.o: testAccelerator.cpp Accelerator.h Accelerator.cpp
	@echo [$@] Compiling...
	@$(CXX) $(CXXFLAGS) -c test/src/testAccelerator.cpp -o $(OTESTPATH)$@ -I ./

testConvert.o: testConvert.cpp Convert.h Convert.cpp
	@echo [$@] Compiling...
	@$(CXX) $(CXXFLAGS) -c test/src/testConvert.cpp -o $(OTESTPATH)$@ -I ./

testException.o: testException.cpp
	@echo [$@] Compiling...
	@$(CXX) $(CXXFLAGS) -c test/src/testException.cpp -o $(OTESTPATH)$@ -I ./

testRenderer.o: testRenderer.cpp
	@echo [$@] Compiling...
	@$(CXX) $(CXXFLAGS) -c test/src/testRenderer.cpp -o $(OTESTPATH)$@ -I ./

##################################################################
# Exercices
##################################################################

exerciceP9.o: exerciceP9.cpp
	@echo [$@] Compiling...
	@$(CXX) $(CXXFLAGS) -c test/exercices/exerciceP9.cpp -o $(OPATH)$@ -I ./


##################################################################
# Links editor and creation of executables
##################################################################

testVector3D.bin: Vector3D.o Drawable.o Renderer.o testVector3D.o Test.o
	@echo [$@] Linking...
	@$(CXX) $(CXXFLAGS) build/Vector3D.o build/Drawable.o build/Renderer.o test/build/testVector3D.o test/build/Test.o -o $(BTESTPATH)$@

testParticle.bin: Vector3D.o Particle.o Convert.o Drawable.o Renderer.o testParticle.o Test.o
	@echo [$@] Linking...
	@$(CXX) $(CXXFLAGS) build/Particle.o build/Convert.o build/Vector3D.o build/Drawable.o build/Renderer.o test/build/testParticle.o test/build/Test.o -o $(BTESTPATH)$@

testElement.bin: Vector3D.o Particle.o Convert.o Element.o Dipole.o Quadrupole.o Straight.o Drawable.o Renderer.o testElement.o Test.o
	@echo [$@] Linking...
	@$(CXX) $(CXXFLAGS) build/Element.o build/Convert.o build/Dipole.o build/Quadrupole.o build/Straight.o build/Particle.o build/Vector3D.o build/Drawable.o build/Renderer.o test/build/testElement.o test/build/Test.o -o $(BTESTPATH)$@

testAccelerator.bin: Vector3D.o Particle.o Convert.o Element.o Dipole.o Quadrupole.o Straight.o Accelerator.o Drawable.o Renderer.o testAccelerator.o Test.o
	@echo [$@] Linking...
	@$(CXX) $(CXXFLAGS) build/Accelerator.o build/Element.o build/Dipole.o build/Quadrupole.o build/Straight.o build/Particle.o build/Convert.o build/Vector3D.o build/Drawable.o build/Renderer.o test/build/testAccelerator.o test/build/Test.o -o $(BTESTPATH)$@

testConvert.bin: testConvert.o Convert.o Vector3D.o Drawable.o Renderer.o Test.o
	@echo [$@] Linking...
	@$(CXX) $(CXXFLAGS) build/Convert.o build/Vector3D.o build/Drawable.o build/Renderer.o test/build/testConvert.o test/build/Test.o -o $(BTESTPATH)$@

testException.bin: testException.o Test.o
	@echo [$@] Linking...
	@$(CXX) $(CXXFLAGS) test/build/testException.o test/build/Test.o -o $(BTESTPATH)$@

testRenderer.bin: Renderer.o TextRenderer.o Drawable.o Accelerator.o Element.o Dipole.o Particle.o Convert.o Quadrupole.o Straight.o Vector3D.o testRenderer.o Test.o
	@echo [$@] Linking...
	@$(CXX) $(CXXFLAGS) build/Renderer.o build/TextRenderer.o build/Drawable.o build/Accelerator.o build/Element.o build/Dipole.o build/Particle.o build/Convert.o build/Quadrupole.o build/Straight.o build/Vector3D.o test/build/testRenderer.o test/build/Test.o -o $(BTESTPATH)$@

exerciceP9.bin: Vector3D.o Particle.o Convert.o Element.o Dipole.o Quadrupole.o Straight.o Accelerator.o Drawable.o Renderer.o exerciceP9.o
	@echo [$@] Linking...
	@$(CXX) $(CXXFLAGS) build/Accelerator.o build/Element.o build/Dipole.o build/Quadrupole.o build/Straight.o build/Particle.o build/Convert.o build/Vector3D.o build/Drawable.o build/Renderer.o build/exerciceP9.o -o $(BPATH)$@


##################################################################
# Run tests
##################################################################

run_testVector3D: testVector3D.bin
	@echo [$@] Running tests...
	@$(BTESTPATH)/testVector3D.bin
	@echo [$@] -------------- Success !

run_testParticle: testParticle.bin
	@echo [$@] Running tests...
	@$(BTESTPATH)/testParticle.bin
	@echo [$@] -------------- Success !

run_testElement: testElement.bin
	@echo [$@] Running tests...
	@$(BTESTPATH)/testElement.bin
	@echo [$@] -------------- Success !

run_testAccelerator: testAccelerator.bin
	@echo [$@] Running tests...
	@$(BTESTPATH)/testAccelerator.bin
	@echo [$@] -------------- Success !

run_testConvert: testConvert.bin
	@echo [$@] Running tests...
	@$(BTESTPATH)/testConvert.bin
	@echo [$@] -------------- Success !

run_testException: testException.bin
	@echo [$@] Running tests...
	@$(BTESTPATH)/testException.bin
	@echo [$@] -------------- Success !

run_testRenderer: testRenderer.bin
	@echo [$@] Running tests...
	@$(BTESTPATH)/testRenderer.bin
	@echo [$@] -------------- Success !


##################################################################
# Exercices
##################################################################

run_exerciceP9: exerciceP9.bin
	@$(BPATH)/exerciceP9.bin


##################################################################
# clean output and build files
##################################################################

clean: cleanbin cleanbuild cleandocs

cleanbin:
	@rm -f $(BPATH)* $(BTESTPATH)*
	@echo [$@] Bin files removed correctly

cleanbuild:
	@rm -f $(OPATH)* $(OTESTPATH)*
	@echo [$@] Build files removed correctly

cleandocs:
	@rm -f -r $(DOXYPATH)*
	@echo [$@] Docs files removed correctly

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

