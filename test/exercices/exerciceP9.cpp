#include <iostream>

#include "src/globals.h"
#include "src/include/bundle/Vector3D.bundle.h"
#include "src/include/bundle/Straight.bundle.h"
#include "src/include/bundle/Dipole.bundle.h"
#include "src/include/bundle/Quadrupole.bundle.h"
#include "src/include/bundle/Accelerator.bundle.h"
#include "src/include/bundle/TextRenderer.bundle.h"

using namespace std;

int main() {
	// Create the default TextRenderer engine which prints to std::cout
	TextRenderer engine;

	// Create accelerator
	// Accelerator acc;
	// acc.addElement(new Dipole(
	// 	Vector3D(1, 0, 0),
	// 	Vector3D(0, -1, 0),
	// 	0.1,
	// 	1,
	// 	7
	// ));
	// acc.addElement(new Straight(
	// 	Vector3D(0, -1, 0),
	// 	Vector3D(-1, -1, 0),
	// 	0.1
	// ));
	// acc.addElement(new Quadrupole(
	// 	Vector3D(-1, -1, 0),
	// 	Vector3D(-2, -1, 0),
	// 	0.1,
	// 	1.2
	// ));
	// acc.addParticle(new Particle(
	// 	Vector3D(1.00984, -0.191837, 0),
	// 	2,
	// 	Vector3D(-210200, -2.64754e+08, 0),
	// 	CONSTANTS::M_PROTON
	// ));
	// acc.addParticle(new Particle(
	// 	Vector3D(0.99016, -0.191837, 0),
	// 	2,
	// 	Vector3D(210200, -2.64754e+08, 0),
	// 	CONSTANTS::M_PROTON
	// ));

	// // Render the accelerator
	// acc.drawTo(&engine);

	return 0;
}
