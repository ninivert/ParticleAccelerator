#include "src/globals.h"
#include "src/exceptions.h"
#include "src/include/bundle/Dipole.bundle.h"
#include "src/include/bundle/Straight.bundle.h"
#include "src/include/bundle/Accelerator.bundle.h"
#include "test/lib/Test.h"

using namespace std;

int main() {
	Accelerator acc;

	// Make elements
		// Exception
	Straight straight_1(Vector3D(3, 0, 0), Vector3D(3.01, -1, 0), 0.1);
	Straight straight_2(Vector3D(3.01, -1, 0), Vector3D(3.02, -3, 0), 0.1);
	Straight straight_3(Vector3D(3.02, -3, 0), Vector3D(3.02, -6, 0), 0.1);
		// Tests for Elements and Particles
	Dipole dipole_1(Vector3D(1, 0, 0), Vector3D(0, -1, 0), 0.1, -1, 7);
		// clearDeadParticles
	Straight straight_4(Vector3D(3, 0, 0), Vector3D(-2, -1, 0), 0.1);

	// Make particles
 	Particle part_1(Vector3D(3.015, -1.2, 0), Vector3D(-210200, -2.64754e8, 0), 0.938272);
	Particle part_2(Vector3D(1.00984, -0.191837, 0), Vector3D(-210200, -2.64754e8, 0), 0.938272);
	Particle part_3(Vector3D(0.99016, -0.191837, 0), 2, Vector3D(-210200, -2.64754e8, 0), 0.938272);
	Particle part_4(Vector3D(2.99, -0.01, 0), Vector3D(0, 0, 0), 0.938272);
	Particle part_5(Vector3D(-2, -1, 0), Vector3D(1e8, 1e8, 0), 0.938272);
	Particle part_6(Vector3D(3.015, -1.2, 0), Vector3D(-210200, -2.64754e8, 0), 0.938272);
	Particle part_7(Vector3D(0.5, -0.513, 0), Vector3D(-210200, -2.64754e8, 0), 0.938272);
	Particle part_8(Vector3D(1.25, -11.2, 0), Vector3D(-210200, -2.64754e8, 0), 0.938272);
	Particle part_9(Vector3D(7.015, 4.21, 4), Vector3D(-210200, -2.64754e8, 0), 0.938272);
	Particle part_10(Vector3D(-2.015, -1.01, 0), Vector3D(-210200, -2.64754e8, 0), 0.938272);
	Particle part_11(Vector3D(-2, -1, 0), Vector3D(-210200, -2.64754e8, 0), 0.938272);

	/****************************************************************
	 * Tests for EXCEPTIONS
	 ****************************************************************/

	ASSERT_EXCEPTION(acc.addParticle(part_1), EXCEPTIONS::NO_ELEMENTS);

	ASSERT_EXCEPTION(
		acc.addElement(straight_1);
		acc.addElement(straight_3);
	, EXCEPTIONS::ELEMENTS_NOT_TOUCHING);

	acc.clear();

	ASSERT_EXCEPTION(
		acc.addElement(straight_1);
		acc.addElement(straight_2);
		acc.addElement(straight_3);

		acc.closeElementLoop();
	, EXCEPTIONS::ELEMENT_LOOP_INCOMPLETE);

	acc.clear();

	/****************************************************************
	 * Tests for Elements and Particles
	 ****************************************************************/

	acc.addElement(dipole_1);
	acc.addParticle(part_1);
	acc.addParticle(part_2);

	// Tests Particle and Dipole

	// Manual comparaison because we are not allowed
	// to access directly to the particles stored in acc

	// cout << acc << endl;
	// cout << part_1 << endl;
	// cout << part_2 << endl;

	acc.clearParticles();
	// cout << acc << endl;

	acc.clear();
	// cout << acc << endl;

	/****************************************************************
	 * clearDeadParticles
	 ****************************************************************/
	acc.addElement(straight_4);

	acc.addParticle(part_4);	// Ok
	acc.addParticle(part_5);	// Ok
	acc.addParticle(part_6);
	acc.addParticle(part_7);	// Ok
	acc.addParticle(part_8);
	acc.addParticle(part_9);
	acc.addParticle(part_10);	// Ok
	acc.addParticle(part_11);	// Ok

	// Manual comparaison because we are not allowed
	// to access directly to the particles stored in acc
	// We can just count the number of particles which are still in the acc

	// cout << acc << endl;
	acc.step();
	// cout << acc << endl;

	acc.clear();

	return 0;
}
