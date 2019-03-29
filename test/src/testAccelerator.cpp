#include "src/globals.h"
#include "src/exceptions.h"
#include "src/include/bundle/Dipole.bundle.h"
#include "src/include/bundle/Straight.bundle.h"
#include "src/include/bundle/Accelerator.bundle.h"
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

	ASSERT_EXCEPTION(
		acc.addElement(new Straight (Vector3D(3, 0, 0), Vector3D(3.01, -1, 0), 0.1));
		acc.addElement(new Straight (Vector3D(3.02, -1, 0), Vector3D(3.02, -2, 0), 0.1));
	, EXCEPTIONS::ELEMENTS_NOT_TOUCHING);

	acc.clear();

	ASSERT_EXCEPTION(
		acc.addElement(new Straight (Vector3D(3, 0, 0), Vector3D(-2, -1, 0), 0.1));
		acc.addElement(new Straight (Vector3D(-2, -1, 0), Vector3D(-2, 1, 0), 0.1));
		acc.addElement(new Straight (Vector3D(-2, 1, 0), Vector3D(7.2, 0, 0), 0.1));

		acc.closeElementLoop();
	, EXCEPTIONS::ELEMENT_LOOP_INCOMPLETE);

	acc.clear();

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

	// cout << acc << endl;

	acc.clearParticles();
	// cout << acc << endl;

	acc.clear();
	// cout << acc << endl;

	/****************************************************************
	 * updateParticleElement
	 ****************************************************************/
	Straight * straight1 = new Straight (Vector3D(3, 0, 0), Vector3D(3.01, -1, 0), 0.1);
	Straight * straight2 = new Straight (Vector3D(3.01, -1, 0), Vector3D(3.02, -2, 0), 0.1);
 	Particle * p = new Particle(Vector3D(3.015, -1.2, 0), Vector3D(-210200, -2.64754e8, 0), 0.938272);

	acc.addElement(straight1);
	acc.addElement(straight2);
	acc.addParticle(p);

	assert(p->getElementPtr() == straight1);
	assert(straight1->isInNextElement(*p));
	acc.step();
	assert(not straight2->isInNextElement(*p));
	assert(p->getElementPtr() == straight2);

	/**
	 * To see the results : compare the output (position) with the output (position) of
	 */
	// cout << acc << endl;

	acc.clear();

	/****************************************************************
	 * closeElementLoop
	 ****************************************************************/
	Straight * straight3 = new Straight (Vector3D(3, 0, 0), Vector3D(-2, -1, 0), 0.1);
	Straight * straight4 = new Straight (Vector3D(-2, -1, 0), Vector3D(-2, 1, 0), 0.1);
	Straight * straight5 = new Straight (Vector3D(-2, 1, 0), Vector3D(3, 0, 0), 0.1);

	// p2 is close to straight3
	Particle p2(Vector3D(3.015, -1.2, 0), Vector3D(-210200, -2.64754e8, 0), 0.938272);

	p2.setElement(straight5);

	acc.addElement(straight3);
	acc.addElement(straight4);
	acc.addElement(straight5);

	acc.closeElementLoop();

	// As straight3 is closer to p2 than straight5,
	// the particle should be in straight3 (as straight3 is now also linked to straight4)
	straight5->updatePointedElement(p2);

	assert(p2.getElementPtr() == straight3);
	acc.clear();

	/****************************************************************
	 * clearDeadParticles
	 ****************************************************************/
	Particle * part_a = new Particle(Vector3D(2.99, -0.01, 0), Vector3D(0, 0, 0), 0.938272);
	Particle * part_b = new Particle(Vector3D(-2, -1, 0), Vector3D(1e8, 1e8, 0), 0.938272);
	Particle * part_c = new Particle(Vector3D(3.015, -1.2, 0), Vector3D(-210200, -2.64754e8, 0), 0.938272);
	Particle * part_d = new Particle(Vector3D(3.015, -1.2, 0), Vector3D(-210200, -2.64754e8, 0), 0.938272);
	Particle * part_e = new Particle(Vector3D(7.015, -1.2, 0), Vector3D(-210200, -2.64754e8, 0), 0.938272);
	Particle * part_f = new Particle(Vector3D(-2, -1, 0), Vector3D(1e8, 1e8, 0), 0.938272);
	Particle * part_g = new Particle(Vector3D(3.015, -1.2, 0), Vector3D(-210200, -2.64754e8, 0), 0.938272);
	Particle * part_h = new Particle(Vector3D(7.015, 4.21, 0), Vector3D(-210200, -2.64754e8, 0), 0.938272);
	Particle * part_i = new Particle(Vector3D(3.015, -1.2, 0), Vector3D(-210200, -2.64754e8, 0), 0.938272);
	Particle * part_j = new Particle(Vector3D(7.015, 4.21, 4), Vector3D(-210200, -2.64754e8, 0), 0.938272);

	Straight * straight6 = new Straight (Vector3D(3, 0, 0), Vector3D(-2, -1, 0), 0.1);

	part_a->setElement(straight6);
	part_b->setElement(straight6);
	part_c->setElement(straight6);
	part_d->setElement(straight6);
	part_e->setElement(straight6);
	part_f->setElement(straight6);
	part_g->setElement(straight6);
	part_h->setElement(straight6);
	part_i->setElement(straight6);
	part_j->setElement(straight6);
	acc.addElement(straight6);

	acc.addParticle(part_a);
	acc.addParticle(part_b);
	acc.addParticle(part_c);
	acc.addParticle(part_d);
	acc.addParticle(part_e);
	acc.addParticle(part_f);
	acc.addParticle(part_g);
	acc.addParticle(part_h);
	acc.addParticle(part_i);
	acc.addParticle(part_j);

	cout << acc << endl;

	acc.step();

	cout << acc << endl;

	acc.clear();

	return 0;
}
