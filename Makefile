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
# Colors !
##################################################################

OK_STRING := "\033[32m"[OK]"\033[0m"
COMPILED_STRING := "\033[33m"Compiled"\033[0m"
LINKED_STRING := "\033[35m"Linked"\033[0m"
TESTED_STRING := "\033[36m"Tested"\033[0m"
WARNING_STRING := "\033[32m"WARNING"\033[0m"
ERROR_STRING := "\033[32m"ERROR"\033[0m"


##################################################################
# To tell him where to search .o and exec files
# and where to put exec files (TARGET)
##################################################################

TESTS := testVector3D testParticle testElement testAccelerator testConvert testException testRenderer exerciceP9
TARGET := $(addsuffix .bin, $(TESTS))
OPATH := build
BPATH := bin
DOXYPATH := doxydocs
LOGPATH := log


##################################################################
# vpath to tell him where to search .h .cpp .o
# when he wants to (re)build
##################################################################

vpath %.h src src/include src/include/bundle test/lib
vpath %.cpp src/lib test/lib test/src test/exercices
vpath %.o build
vpath %.bin bin


##################################################################
# .PHONY for all non file-creating commands
# ->    make clean
##################################################################

.PHONY: all clean cleanbuild cleanbin cleandocs cleanlogs dir docs
all: dir clean docs $(TARGET) $(TESTS)


##################################################################
# Compilation of source files and classes
##################################################################

%.o: %.cpp %.h
	@$(CXX) $(CXXFLAGS) -c $< -o $(OPATH)/$@ -I ./
	@echo $(OK_STRING) $(COMPILED_STRING) $<


##################################################################
# Compilation of tests and exercices
##################################################################

test%.o: test%.cpp %.h %.cpp
	@$(CXX) $(CXXFLAGS) -c $< -o $(OPATH)/$@ -I ./
	@echo $(OK_STRING) $(COMPILED_STRING) $<

testException.o: testException.cpp
	@$(CXX) $(CXXFLAGS) -c $< -o $(OPATH)/$@ -I ./
	@echo $(OK_STRING) $(COMPILED_STRING) $<

exerciceP9.o: exerciceP9.cpp
	@$(CXX) $(CXXFLAGS) -c $< -o $(OPATH)/$@ -I ./
	@echo $(OK_STRING) $(COMPILED_STRING) $<


##################################################################
# Links editor and creation of executables
##################################################################

testVector3D.bin: Vector3D.o Drawable.o Renderer.o testVector3D.o Test.o
	@$(CXX) $(CXXFLAGS) $(addprefix $(OPATH)/, $^) -o $(BPATH)/$@
	@echo $(OK_STRING) $(LINKED_STRING) $@

testParticle.bin: Vector3D.o Particle.o Convert.o Drawable.o Renderer.o testParticle.o Test.o
	@$(CXX) $(CXXFLAGS) $(addprefix $(OPATH)/, $^) -o $(BPATH)/$@
	@echo $(OK_STRING) $(LINKED_STRING) $@

testElement.bin: Vector3D.o Particle.o Convert.o Element.o Dipole.o Quadrupole.o Straight.o Drawable.o Renderer.o testElement.o Test.o
	@$(CXX) $(CXXFLAGS) $(addprefix $(OPATH)/, $^) -o $(BPATH)/$@
	@echo $(OK_STRING) $(LINKED_STRING) $@

testAccelerator.bin: Vector3D.o Particle.o Convert.o Element.o Dipole.o Quadrupole.o Straight.o Frodo.o Accelerator.o Drawable.o Renderer.o testAccelerator.o Test.o
	@$(CXX) $(CXXFLAGS) $(addprefix $(OPATH)/, $^) -o $(BPATH)/$@
	@echo $(OK_STRING) $(LINKED_STRING) $@

testConvert.bin: testConvert.o Convert.o Vector3D.o Drawable.o Renderer.o Test.o
	@$(CXX) $(CXXFLAGS) $(addprefix $(OPATH)/, $^) -o $(BPATH)/$@
	@echo $(OK_STRING) $(LINKED_STRING) $@

testException.bin: testException.o Test.o
	@$(CXX) $(CXXFLAGS) $(addprefix $(OPATH)/, $^) -o $(BPATH)/$@
	@echo $(OK_STRING) $(LINKED_STRING) $@

testRenderer.bin: Renderer.o TextRenderer.o Drawable.o Accelerator.o Element.o Dipole.o Particle.o Convert.o Quadrupole.o Straight.o Frodo.o Vector3D.o testRenderer.o Test.o
	@$(CXX) $(CXXFLAGS) $(addprefix $(OPATH)/, $^) -o $(BPATH)/$@
	@echo $(OK_STRING) $(LINKED_STRING) $@

exerciceP9.bin: Vector3D.o Particle.o Convert.o Element.o Dipole.o Quadrupole.o Straight.o Accelerator.o Drawable.o Renderer.o TextRenderer.o exerciceP9.o
	@$(CXX) $(CXXFLAGS) $(addprefix $(OPATH)/, $^) -o $(BPATH)/$@
	@echo $(OK_STRING) $(LINKED_STRING) $@


##################################################################
# Run tests and exercices from Makefile
# To run from terminal, type bin/test%.bin
##################################################################

%: %.bin
	@$(BPATH)/$<
	@echo $(OK_STRING) $(TESTED_STRING) $<


##################################################################
# Clean output and build files
##################################################################

clean: cleanbin cleanbuild cleandocs cleanlogs

cleanbin:
	@rm -f $(BPATH)/*
	@echo $(OK_STRING) Bin files removed correctly

cleanbuild:
	@rm -f $(OPATH)/*
	@echo $(OK_STRING) Build files removed correctly

cleandocs:
	@rm -f -r $(DOXYPATH)/*
	@echo $(OK_STRING) Docs files removed correctly

cleanlogs:
	@rm -f -r $(LOGPATH)/*
	@echo $(OK_STRING) Log files removed correctly


##################################################################
# dir: make necessary directories for the code to compile
##################################################################

dir:
	@mkdir $(OPATH) -p
	@mkdir $(BPATH) -p
	@mkdir $(LOGPATH) -p
	@echo $(OK_STRING) created necessary directories


##################################################################
# doc: generate documentation index.html
##################################################################

docs: cleandocs
	@doxygen Doxyfile > /dev/null 2>&1
	@echo $(OK_STRING) generated documentation


##################################################################
# open_docs: run index.html
##################################################################

open_docs: docs
	@xdg-open $(DOXYPATH)/html/index.html
