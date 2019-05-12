#include "globals.h"
#include "exceptions.h"
#include "include/bundle/Vector3D.bundle.h"
#include "include/bundle/Straight.bundle.h"
#include "include/bundle/Dipole.bundle.h"
#include "include/bundle/Quadrupole.bundle.h"
#include "include/bundle/Frodo.bundle.h"
#include "include/bundle/Accelerator.bundle.h"
#include "include/bundle/TextRenderer.bundle.h"
#include "include/bundle/Test.bundle.h"

#include <iostream>

using namespace std;

int main() {
	// Default engine
	// TextRenderer engine;

	// File stream engine
	TextRenderer engineToFile("../log/testRenderer.log");


	// Make the elements
	Dipole D1(Vector3D(1, 0, 0), Vector3D(0, -1, 0), 0.1, 1, 7);
	Straight S1(Vector3D(0, -1, 0), Vector3D(-1, -1, 0), 0.1);
	Quadrupole Q1(Vector3D(-1, -1, 0), Vector3D(-2, -1, 0), 0.1, 1.2);

	// Make the particles
	Particle P1(Vector3D(1.00984, -0.191837, 0), 2, Vector3D(-210200, -2.64754e+08, 0), CONSTANTS::M_PROTON);
	Particle P2(Vector3D(0.99016, -0.191837, 0), 2, Vector3D(210200, -2.64754e+08, 0), CONSTANTS::M_PROTON);

	// Make the accelerator
	Accelerator acc(&engineToFile);
	acc.addElement(D1);
	acc.addElement(S1);
	acc.addElement(Q1);
	acc.addParticle(P1);
	acc.addParticle(P2);

	// Test exceptions
	Accelerator accNoRenderer;
	ASSERT_EXCEPTION(accNoRenderer.draw(), EXCEPTIONS::NULLPTR);

	// Rendering
	// Log to file engine using draw(Renderer * engine)
	acc.draw();
	// Log to terminal
	// acc.draw(&engine);

	return 0;
}
