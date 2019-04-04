#include "src/globals.h"
#include "src/exceptions.h"
#include "src/include/bundle/Frodo.bundle.h"
#include "src/include/bundle/Particle.bundle.h"
#include "src/include/bundle/Quadrupole.bundle.h"
#include "src/include/bundle/Straight.bundle.h"
#include "src/include/bundle/Accelerator.bundle.h"
#include "src/include/bundle/TextRenderer.bundle.h"
#include "test/lib/Test.h"

#include <iostream>

using namespace std;

int main() {
	TextRenderer engine;
	Accelerator acc;

	// acc.addElement(new Frodo(
	// 	Vector3D(1, 0, 0),
	// 	Vector3D(1, -10, 0),
	// 	1,
	// 	30,
	// 	0.25
	// ));

	acc.addElement(new Quadrupole(
		Vector3D(1, 0, 0),
		Vector3D(1, -2.5, 0),
		1,
		2
	));

	acc.addElement(new Straight(
		Vector3D(1, -2.5, 0),
		Vector3D(1, -5, 0),
		1
	));

	acc.addElement(new Quadrupole(
		Vector3D(1, -5, 0),
		Vector3D(1, -7.5, 0),
		1,
		-2
	));

	acc.addElement(new Straight(
		Vector3D(1, -7.5, 0),
		Vector3D(1, -10, 0),
		1
	));

	// In first quadrupole, the particle is a bit offset
	acc.addParticle(new Particle(
		Vector3D(0.8, 0, 0.2),
		2,
		Vector3D(0, -2.64754e+08, 0),
		CONSTANTS::M_PROTON
	));

	int i(0);
	do {
		++i;
		acc.step();
		cout << acc << endl;
		cout << i << endl;
	} while (true);
}
