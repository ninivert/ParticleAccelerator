#include <iostream>

#include "src/globals.h"
#include "src/include/bundle/Vector3D.bundle.h"
#include "src/include/bundle/Straight.bundle.h"
#include "src/include/bundle/Dipole.bundle.h"
#include "src/include/bundle/Quadrupole.bundle.h"
#include "src/include/bundle/Frodo.bundle.h"
#include "src/include/bundle/Accelerator.bundle.h"
#include "src/include/bundle/TextRenderer.bundle.h"

using namespace std;

int main() {
	// Create the default TextRenderer engine which prints to std::cout
	TextRenderer engine;

	Accelerator acc(&engine);

	Vector3D pos_dep(3, 2, 0);
	Vector3D dir_frodo(0, -1, 0);
	Vector3D pos_fin;
	Vector3D dir_dipole(-1, -1, 0);

	for (int i = 0; i < 4; ++i) {

		pos_fin = pos_dep + 4 * dir_frodo;
		acc.addElement(Frodo(
			pos_dep, pos_fin,
			0.1, 1.2, 1
			));

		pos_dep = pos_fin;
		pos_fin += dir_dipole;

		acc.addElement(Dipole(
			pos_dep,
			pos_fin,
			0.1, 1, 5.89158
			));

		pos_dep = pos_fin;

		// -90° rotation
		dir_frodo ^= Vector3D(0, 0, 1);
		dir_dipole ^= Vector3D(0, 0, 1);
	}

	acc.closeElementLoop();

	acc.addParticle(Particle(
		Vector3D(3.01, 0, 0), 2,
		Vector3D(0, -2.64754e+08, 0),
		CONSTANTS::M_PROTON
	));

	acc.addParticle(Particle(
		Vector3D(2.99, 0, 0), 2,
		Vector3D(0, -2.64754e+08, 0),
		CONSTANTS::M_PROTON
	));

	// Render the accelerator
	// acc.draw();

	//1 : 4660 value near which the second particle added goes out
	//2 : 4869 value near which the first particle added goes out
	for (int i = 0; i < 300000; ++i) {
		acc.step();
	}

	acc.draw();
	acc.clear();

	return 0;
}
