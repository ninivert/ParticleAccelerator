#include "src/globals.h"
#include <iomanip>

#include "src/exceptions.h"
#include "src/include/Vector3D.h"
#include "src/include/Particle.h"
#include "src/include/Element.h"
#include "src/include/Dipole.h"
#include "src/include/Quadrupole.h"
#include "src/include/Accelerator.h"
#include "test/lib/Test.h"

using namespace std;

int main() {
	Accelerator acc;

	/****************************************************************
	 * Tests for EXCEPTIONS
	 ****************************************************************/

	ASSERT_EXCEPTION(acc.addElement(nullptr), EXCEPTIONS::NULLPTR);
	ASSERT_EXCEPTION(acc.addParticle(nullptr), EXCEPTIONS::NULLPTR);

	ASSERT_EXCEPTION(new Dipole(Vector3D(0, 1, 0), Vector3D(0, -1, 0), 0.1, 1, 0), EXCEPTIONS::BAD_ORIENTATION);

	ASSERT_EXCEPTION(acc.addParticle(new Particle(Vector3D(1.00984, -0.191837, 0), Vector3D(-210200, -2.64754e8, 0), 0.938272)), EXCEPTIONS::NO_ELEMENTS);

	/****************************************************************
	 * Tests for Elements and Particles
	 ****************************************************************/

	Dipole * dipole = new Dipole(Vector3D(1, 0, 0), Vector3D(0, -1, 0), 0.1, -1, 7);
	Particle * part1 = new Particle(Vector3D(1.00984, -0.191837, 0), Vector3D(-210200, -2.64754e8, 0), 0.938272);
	Particle * part2 = new Particle(Vector3D(0.99016, -0.191837, 0), 2, Vector3D(-210200, -2.64754e8, 0), 0.938272);

	acc.addElement(dipole);
	acc.addParticle(part1);
	acc.addParticle(part2);

	// Tests Dipole

	assert(dipole->getPosIn() == Vector3D(1, 0, 0));
	assert(dipole->getPosOut() == Vector3D(0, -1, 0));
	assert(Test::eq(dipole->getRadius(), 0.1));
	assert(dipole->getField(Vector3D(0, 0, 0)) == Vector3D(0, 0, 7));

	// Tests Particle

	Particle part3(Vector3D(1.00984, -0.191837, 0), Vector3D(-210200, -2.64754e8, 0), 0.938272);
	Particle part4(Vector3D(0.99016, -0.191837, 0), Vector3D(-210200.33, -2.6475441e8, 0), 0.938272);

	// We have to "reduce" the speed or our `operator ==` won't evaluate it correctly
	// We are working at high speed (10e8) so small errors are way larger than our EPSILON (in globals.h)
	assert(part1->getSpeed() / 10e8 == part3.getSpeed() / 10e8);
	assert(Test::eq(part2->getSpeed().getX(), part4.getSpeed().getX()));
	assert(Test::eq(part2->getSpeed().getY(), part4.getSpeed().getY()));
	assert(Test::eq(part2->getSpeed().getZ(), part4.getSpeed().getZ()));

	assert(part1->getMoment() == part3.getMoment());
	assert(part2->getMoment() == part4.getMoment());

	assert(part1->getPos() == part3.getPos());
	assert(part2->getPos() == part4.getPos());

	assert(Test::eq(part1->getEnergy(), part3.getEnergy()));
	assert(Test::eq(part2->getEnergy(), part4.getEnergy()));

	assert(Test::eq(part1->getGamma(), part3.getGamma()));
	assert(Test::eq(part2->getGamma(), part4.getGamma()));

	assert(Test::eq(part1->getMass(), part3.getMass()));
	assert(Test::eq(part2->getMass(), part4.getMass()));

	assert(Test::eq(part1->getCharge(), part3.getCharge()));
	assert(Test::eq(part2->getCharge(), part4.getCharge()));

	assert(Test::eq(part1->getChargeNumber(), part3.getChargeNumber()));
	assert(Test::eq(part2->getChargeNumber(), part4.getChargeNumber()));

	// Display

	cout << acc << endl;

	acc.clearParticles();
	// cout << acc << endl;

	acc.clear();
	// cout << acc << endl;

	return 0;
}
