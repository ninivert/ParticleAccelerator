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

TARGET := testVector3D.bin testParticle.bin
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
# Compilation of source files and classes
##################################################################

Vector3D.o: Vector3D.cpp Vector3D.h
	@echo [$@] Compiling...
	@$(CXX) $(CXXFLAGS) -c src/lib/Vector3D.cpp -o $(OPATH)$@ -I ./

Particle.o: Particle.cpp Particle.h
	@echo [$@] Compiling...
	@$(CXX) $(CXXFLAGS) -c src/lib/Particle.cpp -o $(OPATH)$@ -I ./


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


##################################################################
# Links editor and creation of executables
##################################################################

testVector3D.bin: Vector3D.o testVector3D.o Test.o
	@echo [$@] Linking...
	@$(CXX) $(CXXFLAGS) test/build/testVector3D.o test/build/Test.o build/Vector3D.o -o $(BTESTPATH)$@

testParticle.bin: Vector3D.o Particle.o testParticle.o Test.o
	@echo [$@] Linking...
	@$(CXX) $(CXXFLAGS) test/build/testParticle.o test/build/Test.o build/Particle.o build/Vector3D.o -o $(BTESTPATH)$@


##################################################################
# Run tests
##################################################################

run_testVector3D: testVector3D.bin
	@echo Running [$@]
	@$(BTESTPATH)/testVector3D.bin

run_testParticle: testParticle.bin
	@echo Running [$@]
	@$(BTESTPATH)/testParticle.bin


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
run_docs:
	@xdg-open docs/index.html

