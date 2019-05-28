#include "globals.h"
#include "exceptions.h"
#include "include/bundle/Dipole.bundle.h"
#include "include/bundle/Straight.bundle.h"
#include "include/bundle/Accelerator.bundle.h"
#include "include/bundle/Test.bundle.h"

using namespace std;

int main() {
	Accelerator acc(nullptr, false);

	// Make elements
		// Exception
	Straight straight_1(Vector3D(3, 0, 0), Vector3D(3.01, -1, 0), 0.1);
	Straight straight_2(Vector3D(3.01, -1, 0), Vector3D(3.02, -3, 0), 0.1);
	Straight straight_3(Vector3D(3.02, -3, 0), Vector3D(3.02, -6, 0), 0.1);
		// Tests for Elements and Particles
	Dipole dipole_1(Vector3D(1, 0, 0), Vector3D(0, -1, 0), 0.1, -1, 7);
		// clearDeadParticles
	Straight straight_4(Vector3D(3, 0, 0), Vector3D(-2, -1, 0), 0.08);

	// Make particles
 	Particle part_1(Vector3D(3.015, -1.2, 0), 2, Vector3D(-210200, -2.64754e8, 0), 0.938272);
	Particle part_2(Vector3D(0.90984, -0.091837, 0), 2, Vector3D(-210200, -2.64754e8, 0), 0.938272);
	Particle part_3(Vector3D(0.99016, -0.191837, 0), 2, Vector3D(-210200, -2.64754e8, 0), 0.938272);
	Particle part_4(Vector3D(2.99, -0.01, 0), 2, Vector3D(0.001, 0, 0), 0.938272);
	Particle part_5(Vector3D(-2, -1, 0), 2, Vector3D(1e8, 1e8, 0), 0.938272);
	Particle part_6(Vector3D(2.55, -0.0099, 0), 2, Vector3D(-2.64e7, 2.64754e8, 0), 0.938272);
	Particle part_7(Vector3D(0.5, -0.501, 0), 2, Vector3D(-210200, 64754, 0), 0.938272);
	Particle part_8(Vector3D(0.5, -0.58, 0), 2, Vector3D(2e7, -2.754e8, 0), 0.938272);
	Particle part_9(Vector3D(-2, -0.92, 0), 2, Vector3D(2.99e7, 2.45e8, 0), 0.938272);
	Particle part_10(Vector3D(-1.95, -0.95, 0), 2, Vector3D(-210200, -2.64754e8, 0), 0.938272);
	Particle part_11(Vector3D(-2, -1, 0), 2, Vector3D(0, 2, 0), 0.938272);

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
	acc.addParticle(part_2);

	// Manual comparaison because we are not allowed
	// to access directly to the particles stored in acc

	// cout << acc << endl;
	// cout << part_2 << endl;

	acc.clearBeams();
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

	// We can just count the number of particles
	// which are still in the acc after 1 step

	// cout << acc << endl;		// 8 beams
	acc.step();
	// cout << acc << endl;		// 5 beams

	acc.clear();

	/****************************************************************
	 * Particle not in accelerator
	 ****************************************************************/

	acc.addElement(Dipole(Vector3D(1, 0, 0), Vector3D(0, -1, 0), 0.0001, 1, 7));
	acc.addElement(Straight(Vector3D(0, -1, 0), Vector3D(-2, -1, 0), 0.1));

	// Juuust outside dipole
	ASSERT_EXCEPTION(acc.addParticle(Particle(Vector3D(1, 0.1, 0), 2, Vector3D(1, 0, 0), CONSTANTS::M_PROTON)), EXCEPTIONS::PARTICLE_NOT_IN_ACCELERATOR);

	acc.clearBeams();
	// Juuuust inside dipole
	acc.addParticle(Particle(Vector3D(1, 0, 0), 1, Vector3D(0, -1, 0), CONSTANTS::M_PROTON));
	// Just in the the dipole
	acc.addParticle(Particle(Vector3D(sqrt(2) / 2, -sqrt(2) / 2, 0), 2, Vector3D(0.5, 2, 2), CONSTANTS::M_PROTON));
	// Just in the the dipole (go out after 1 acc.step())
	acc.addParticle(Particle(Vector3D(sqrt(2) / 2 + 0.00007, -sqrt(2) / 2 - 0.00007, 0), 10, Vector3D(0.5, 2, 0), CONSTANTS::M_PROTON));
	// At the edge between the dipole and straight
	acc.addParticle(Particle(Vector3D(0, -1, 0), 2, Vector3D(-1e8, 0, 0), CONSTANTS::M_PROTON));

	// cout << acc << endl;	// 4 particles
	acc.step();
	// cout << acc << endl;	// 3 particles

	acc.clear();

	return 0;
}
