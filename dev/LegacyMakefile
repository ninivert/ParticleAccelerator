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

TARGETS := testVector3D testParticle testElement testAccelerator testConvert testException testRenderer testFrodo testBeam exerciceP9 exerciceP10
OPATH := ../build
BPATH := ../bin
DOXYPATH := ../doxydocs
LOGPATH := ../log


##################################################################
# vpath to tell him where to search .h .cpp .o
# when he wants to (re)build
##################################################################

vpath %.h ../src ../src/include ../src/include/bundle ../test/lib
vpath %.cpp ../src/lib ../test/lib ../test/src ../test/exercices
vpath %.o ../build
vpath %.bin ../bin


##################################################################
# .PHONY for all non file-creating commands
# ->    make clean
##################################################################

.PHONY: all clean cleanbuild cleanbin cleandocs cleanlogs dir docs %
all: dir docs $(TARGETS)


##################################################################
# Compilation of source files and classes
##################################################################

%.o: %.cpp %.h
	@$(CXX) $(CXXFLAGS) -c $< -o $(OPATH)/$@ -I ../
	@echo $(OK_STRING) $(COMPILED_STRING) $<


##################################################################
# Compilation of tests and exercices
##################################################################

test%.o: test%.cpp %.h %.cpp
	@$(CXX) $(CXXFLAGS) -c $< -o $(OPATH)/$@ -I ../
	@echo $(OK_STRING) $(COMPILED_STRING) $<

testException.o: testException.cpp
	@$(CXX) $(CXXFLAGS) -c $< -o $(OPATH)/$@ -I ../
	@echo $(OK_STRING) $(COMPILED_STRING) $<

testCircular.o: testCircular.cpp
	@$(CXX) $(CXXFLAGS) -c $< -o $(OPATH)/$@ -I ../
	@echo $(OK_STRING) $(COMPILED_STRING) $<

exerciceP9.o: exerciceP9.cpp
	@$(CXX) $(CXXFLAGS) -c $< -o $(OPATH)/$@ -I ../
	@echo $(OK_STRING) $(COMPILED_STRING) $<

exerciceP10.o: exerciceP10.cpp
	@$(CXX) $(CXXFLAGS) -c $< -o $(OPATH)/$@ -I ../
	@echo $(OK_STRING) $(COMPILED_STRING) $<


##################################################################
# Links editor and creation of executables
##################################################################

testVector3D.bin: testVector3D.o Test.o Vector3D.o Drawable.o Renderer.o
	@$(CXX) $(CXXFLAGS) $(addprefix $(OPATH)/, $(notdir $^)) -o $(BPATH)/$@
	@echo $(OK_STRING) $(LINKED_STRING) $@

testParticle.bin: testParticle.o Test.o Vector3D.o Particle.o Convert.o Drawable.o Renderer.o
	@$(CXX) $(CXXFLAGS) $(addprefix $(OPATH)/, $(notdir $^)) -o $(BPATH)/$@
	@echo $(OK_STRING) $(LINKED_STRING) $@

testElement.bin: testElement.o Test.o Vector3D.o Particle.o Convert.o Element.o Dipole.o Quadrupole.o Straight.o Drawable.o Renderer.o
	@$(CXX) $(CXXFLAGS) $(addprefix $(OPATH)/, $(notdir $^)) -o $(BPATH)/$@
	@echo $(OK_STRING) $(LINKED_STRING) $@

testAccelerator.bin: testAccelerator.o Test.o Vector3D.o Particle.o Convert.o Element.o Dipole.o Quadrupole.o Straight.o Frodo.o Accelerator.o Beam.o Drawable.o Renderer.o
	@$(CXX) $(CXXFLAGS) $(addprefix $(OPATH)/, $(notdir $^)) -o $(BPATH)/$@
	@echo $(OK_STRING) $(LINKED_STRING) $@

testBeam.bin: testBeam.o Test.o Vector3D.o Particle.o Convert.o Element.o Dipole.o Quadrupole.o Straight.o Frodo.o Beam.o Accelerator.o Drawable.o Renderer.o TextRenderer.o
	@$(CXX) $(CXXFLAGS) $(addprefix $(OPATH)/, $(notdir $^)) -o $(BPATH)/$@
	@echo $(OK_STRING) $(LINKED_STRING) $@

testFrodo.bin: testFrodo.o Test.o Vector3D.o Particle.o Convert.o Element.o Dipole.o Quadrupole.o Straight.o Frodo.o Accelerator.o Drawable.o Renderer.o TextRenderer.o Beam.o
	@$(CXX) $(CXXFLAGS) $(addprefix $(OPATH)/, $(notdir $^)) -o $(BPATH)/$@
	@echo $(OK_STRING) $(LINKED_STRING) $@

testConvert.bin: testConvert.o Test.o Convert.o Vector3D.o Drawable.o Renderer.o
	@$(CXX) $(CXXFLAGS) $(addprefix $(OPATH)/, $(notdir $^)) -o $(BPATH)/$@
	@echo $(OK_STRING) $(LINKED_STRING) $@

testException.bin: testException.o Test.o
	@$(CXX) $(CXXFLAGS) $(addprefix $(OPATH)/, $(notdir $^)) -o $(BPATH)/$@
	@echo $(OK_STRING) $(LINKED_STRING) $@

testRenderer.bin: testRenderer.o Test.o Renderer.o TextRenderer.o Beam.o Drawable.o Accelerator.o Element.o Dipole.o Particle.o Convert.o Quadrupole.o Straight.o Frodo.o Vector3D.o
	@$(CXX) $(CXXFLAGS) $(addprefix $(OPATH)/, $(notdir $^)) -o $(BPATH)/$@
	@echo $(OK_STRING) $(LINKED_STRING) $@

testCircular.bin: testCircular.o Test.o Renderer.o TextRenderer.o Beam.o Drawable.o Accelerator.o Element.o Dipole.o Particle.o Convert.o Quadrupole.o Straight.o Frodo.o Vector3D.o
	@$(CXX) $(CXXFLAGS) $(addprefix $(OPATH)/, $(notdir $^)) -o $(BPATH)/$@
	@echo $(OK_STRING) $(LINKED_STRING) $@

exerciceP9.bin: Vector3D.o Particle.o Convert.o Element.o Dipole.o Quadrupole.o Straight.o Accelerator.o Drawable.o Renderer.o TextRenderer.o Beam.o exerciceP9.o
	@$(CXX) $(CXXFLAGS) $(addprefix $(OPATH)/, $(notdir $^)) -o $(BPATH)/$@
	@echo $(OK_STRING) $(LINKED_STRING) $@

exerciceP10.bin: Vector3D.o Particle.o Convert.o Element.o Dipole.o Quadrupole.o Straight.o Frodo.o Accelerator.o Drawable.o Renderer.o TextRenderer.o Beam.o exerciceP10.o
	@$(CXX) $(CXXFLAGS) $(addprefix $(OPATH)/, $(notdir $^)) -o $(BPATH)/$@
	@echo $(OK_STRING) $(LINKED_STRING) $@


##################################################################
# Run tests and exercices from Makefile
# To run from terminal, type bin/test%.bin
##################################################################

%: %.bin
	@$(BPATH)/$*.bin
	@echo $(OK_STRING) $(TESTED_STRING) $*


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
	@echo $(OK_STRING) Greated necessary directories


##################################################################
# doc: generate documentation index.html
##################################################################

docs: cleandocs
	@doxygen ../Doxyfile > /dev/null 2>&1
	@echo $(OK_STRING) Generated documentation


##################################################################
# open_docs: run index.html
##################################################################

open_docs: docs
	@xdg-open $(DOXYPATH)/html/index.html
