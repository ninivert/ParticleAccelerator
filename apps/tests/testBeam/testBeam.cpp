#include "globals.h"
#include "exceptions.h"
#include "include/bundle/Vector3D.bundle.h"
#include "include/bundle/Particle.bundle.h"
#include "include/bundle/Straight.bundle.h"
#include "include/bundle/Dipole.bundle.h"
#include "include/bundle/Beam.bundle.h"
#include "include/bundle/TextRenderer.bundle.h"
#include "include/bundle/Test.bundle.h"

using namespace std;

int main() {
	TextRenderer engine;

	Accelerator acc(&engine);

	Dipole dipole_1(Vector3D(1, 0, 0), Vector3D(0, -1, 0), 0.1, 1, 7);
	acc.addElement(dipole_1);
	acc.addElement(Dipole(Vector3D(0, -1, 0), Vector3D(-1, 0, 0), 0.1, 1, 7));
	acc.addElement(Dipole(Vector3D(-1, 0, 0), Vector3D(0, 1, 0), 0.1, 1, 7));
	acc.addElement(Dipole(Vector3D(0, 1, 0), Vector3D(1, 0, 0), 0.1, 1, 7));

	acc.closeElementLoop();

	// acc.draw();

	Particle part_1(Vector3D(1.01, -0.01, -0.04), 2, Vector3D(-1, -0, 0.01), 0.938272);
	part_1.setElement(&dipole_1);

	Beam beam_1(part_1, 4, 2, acc);

	// cout << beam_1;

	acc.addBeam(part_1, 4, 2);

	// acc.drawBeams();

	acc.addParticle(part_1);
	// acc.drawBeams();

	acc.clearBeams();
	// acc.draw();

	Beam beam_2(part_1, 10000, 500, acc);

	// cout << beam_2;

	return 0;
}
