#include <iostream>

#include "globals.h"
#include "include/bundle/Vector3D.bundle.h"
#include "include/bundle/Straight.bundle.h"
#include "include/bundle/Dipole.bundle.h"
#include "include/bundle/Quadrupole.bundle.h"
#include "include/bundle/Frodo.bundle.h"
#include "include/bundle/Beam.bundle.h"
#include "include/bundle/Accelerator.bundle.h"
#include "include/bundle/TextRenderer.bundle.h"

using namespace std;

int main() {

	/****************************************************************
	 * See Beam::exertInteraction()
	 ****************************************************************/

	// Create the default TextRenderer engine which prints to std::cout
	TextRenderer engine;

	Accelerator acc(&engine, false);

	Dipole dipole_1(Vector3D(1, 0, 0), Vector3D(0, -1, 0), 0.1, 1, 7);
	acc.addElement(dipole_1);
	acc.addElement(Dipole(Vector3D(0, -1, 0), Vector3D(-1, 0, 0), 0.1, 1, 7));
	acc.addElement(Dipole(Vector3D(-1, 0, 0), Vector3D(0, 1, 0), 0.1, 1, 7));
	acc.addElement(Dipole(Vector3D(0, 1, 0), Vector3D(1, 0, 0), 0.1, 1, 7));

	acc.closeElementLoop();

	// acc.draw();

	Particle part_1(Vector3D(1.01, -0.01, -0.04), 2, Vector3D(-1, -0, 0.01), 0.938272);
	part_1.setElement(&dipole_1);

	Beam beam_1(part_1, 10000, 500, acc);

	// cout << beam_1;

	acc.addBeam(part_1, 10000, 500);

	// acc.drawBeams();

	acc.step();

	acc.clearBeams();
}
