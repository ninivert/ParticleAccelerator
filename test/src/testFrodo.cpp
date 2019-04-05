#include "src/globals.h"
#include "src/exceptions.h"
#include "src/include/bundle/Frodo.bundle.h"
#include "src/include/bundle/Particle.bundle.h"
#include "src/include/bundle/Quadrupole.bundle.h"
#include "src/include/bundle/Straight.bundle.h"
#include "src/include/bundle/Accelerator.bundle.h"
#include "src/include/bundle/TextRenderer.bundle.h"
#include "test/lib/Test.h"

using namespace std;

int main() {
	TextRenderer engine;

	Particle p1(Vector3D(1, -0.2, 0), 10, Vector3D(0.03, -1, 0.03), CONSTANTS::M_PROTON);

	Frodo FRODO(
		Vector3D(1, 0, 0),
		Vector3D(1, -1, 0),
		1,
		-1,
		3/16.0
	);

	Frodo SAM(
		Vector3D(1, -1, 0),
		1,
		Vector3D(0, -1, 0),
		1,
		1,
		0.25
	);

	Quadrupole q1(Vector3D(1, 0, 0), Vector3D(1, -5/16.0, 0), 1, -1);
	Quadrupole q2(Vector3D(1, -8/16.0, 0), Vector3D(1, -13/16.0, 0), 1, 1);
	Straight s1(Vector3D(1, -5/16.0, 0), Vector3D(1, -8/16.0, 0), 1);
	Straight s2(Vector3D(1, -13/16.0, 0), Vector3D(1, -1, 0), 1);
	Quadrupole q3(Vector3D(1, 0, 0), Vector3D(1, -1, 0), 1, 1);

	Accelerator acc(&engine);
	Accelerator accbis(&engine);
	Accelerator acctri(&engine);

	accbis.addElement(q1);
	accbis.addElement(s1);
	accbis.addElement(q2);
	accbis.addElement(s2);
	accbis.addParticle(p1);
	accbis.addElement(SAM);

	acctri.addElement(q3);
	acctri.addElement(SAM);
	acctri.addParticle(p1);

	acc.addElement(FRODO);
	acc.addElement(SAM);
	acc.addParticle(p1);

	for (int i = 0; i < 500; ++i) {
		acc.step();
		// accbis.step();
		// acctri.step();
	}

	// acc.draw();
	acc.clear();
	accbis.clear();
	acctri.clear();
}
