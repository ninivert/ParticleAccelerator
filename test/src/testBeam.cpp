#include "src/globals.h"
#include "src/exceptions.h"
#include "src/include/bundle/Vector3D.bundle.h"
#include "src/include/bundle/Particle.bundle.h"
#include "src/include/bundle/Straight.bundle.h"
#include "src/include/bundle/Dipole.bundle.h"
#include "src/include/bundle/Beam.bundle.h"
#include "test/lib/Test.h"

using namespace std;

int main() {
	Accelerator acc;

	Dipole dipole_1(Vector3D(1, 0, 0), Vector3D(0, -1, 0), 0.1, 1, 7);
	acc.addElement(dipole_1);
	acc.addElement(Dipole(Vector3D(0, -1, 0), Vector3D(-1, 0, 0), 0.1, 1, 7));
	acc.addElement(Dipole(Vector3D(-1, 0, 0), Vector3D(0, 1, 0), 0.1, 1, 7));
	acc.addElement(Dipole(Vector3D(0, 1, 0), Vector3D(1, 0, 0), 0.1, 1, 7));

	acc.closeElementLoop();

	cout << acc << endl;



	Particle part_1(Vector3D(1.01, -0.01, -0.04), 2, Vector3D(-1, -0, 0.01), 0.938272);
	part_1.setElement(&dipole_1);

	Beam beam_1(part_1, 4, 2, acc);

	cout << beam_1 << endl;

	return 0;
}
