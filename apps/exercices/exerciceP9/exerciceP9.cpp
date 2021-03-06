#include <iostream>

#include "globals.h"
#include "include/bundle/Vector3D.bundle.h"
#include "include/bundle/Straight.bundle.h"
#include "include/bundle/Dipole.bundle.h"
#include "include/bundle/Quadrupole.bundle.h"
#include "include/bundle/Accelerator.bundle.h"
#include "include/bundle/TextRenderer.bundle.h"

using namespace std;

int main() {
	// Create the default TextRenderer engine which prints to std::cout
	TextRenderer engine("log/exerciceP9.log");

	Dipole D1(
		Vector3D(1, 0, 0),
		Vector3D(0, -1, 0),
		0.1,
		1,
		7
	);
	Straight S1(
		Vector3D(0, -1, 0),
		Vector3D(-1, -1, 0),
		0.1
	);
	Quadrupole Q1(
		Vector3D(-1, -1, 0),
		Vector3D(-2, -1, 0),
		0.1,
		1.2
	);

	Particle p1(
		Vector3D(1.00984, -0.191837, 0), 2,
		Vector3D(-210200, -2.64754e+08, 0),
		CONSTANTS::M_PROTON
	);

	Particle p2(
		Vector3D(0.99016, -0.191837, 0), 2,
		Vector3D(210200, -2.64754e+08, 0),
		CONSTANTS::M_PROTON
	);


	// Create accelerator
	Accelerator acc(&engine);
	acc.addElement(D1);
	acc.addElement(S1);
	acc.addElement(Q1);
	acc.addParticle(p1);
	acc.addParticle(p2);

	// Render the accelerator
	acc.draw();

	acc.clear();

	return 0;
}
