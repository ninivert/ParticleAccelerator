#include "src/globals.h"
#include "src/exceptions.h"
#include "src/include/bundle/Vector3D.bundle.h"
#include "src/include/bundle/Straight.bundle.h"
#include "src/include/bundle/Dipole.bundle.h"
#include "src/include/bundle/Quadrupole.bundle.h"
#include "src/include/bundle/Accelerator.bundle.h"
#include "src/include/bundle/TextRenderer.bundle.h"
#include "test/lib/Test.h"

#include <iostream>
#include <fstream>

using namespace std;

int main() {
	// Default engine
	TextRenderer engine;

	// File stream engine
	ofstream fout("./log/testRenderer.log");
	if (fout.fail()) cerr << "Well, that didn't really go as planned..." << endl;
	TextRenderer engineToFile(&fout);

	// Make the accelerator
	Accelerator acc;
	acc.addElement(new Dipole(Vector3D(1, 0, 0), Vector3D(0, -1, 0), 0.1, 1, 7));
	acc.addElement(new Straight(Vector3D(0, -1, 0), Vector3D(-1, -1, 0), 0.1));
	acc.addElement(new Quadrupole(Vector3D(-1, -1, 0), Vector3D(-2, -1, 0), 0.1, 1.2));
	acc.addParticle(new Particle(Vector3D(1.00984, -0.191837, 0), 2, Vector3D(-210200, -2.64754e+08, 0), CONSTANTS::M_PROTON));
	acc.addParticle(new Particle(Vector3D(0.99016, -0.191837, 0), 2, Vector3D(210200, -2.64754e+08, 0), CONSTANTS::M_PROTON));

	// Test exceptions
	ASSERT_EXCEPTION(acc.drawTo(nullptr), EXCEPTIONS::NULLPTR);

	// Rendering
	// acc.drawTo(&engine);
	acc.drawTo(&engineToFile);

	// Do this or chap chap will be very mad òwó
	fout.close();

	return 0;
}
