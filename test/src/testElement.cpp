#include "src/globals.h"
#include "src/exceptions.h"
#include "src/include/bundle/Vector3D.bundle.h"
#include "src/include/bundle/Particle.bundle.h"
#include "src/include/bundle/Quadrupole.bundle.h"
#include "src/include/bundle/Straight.bundle.h"
#include "src/include/bundle/Dipole.bundle.h"
#include "src/include/bundle/Element.bundle.h"
#include "test/lib/Test.h"

using namespace std;

int main() {

	/****************************************************************
	 * Dipole
	 ****************************************************************/

	Dipole dipole(Vector3D(3, 0, 0), Vector3D(2, -1, 0), 0.1, -1, 5.12);

	// posCenter : (3, -1, 0)

	assert(dipole.getPosIn() == Vector3D(3, 0, 0));
	assert(dipole.getPosOut() == Vector3D(2, -1, 0));
	assert(Test::eq(dipole.getRadius(), 0.1));
	assert(dipole.getField(Vector3D(0, 0, 0)) == Vector3D(0, 0, 5.12));
	dipole.setB(7);
	assert(dipole.getField(Vector3D(0, 0, 0)) == Vector3D(0, 0, 7));

	Particle p1(Vector3D(3.00894, -0.391837, 0), Vector3D(-210200, -2.64754e8, 0), 0.938272);
	Particle p2(Vector3D(3.00892956975892, -0.394484520288904, 0), 1.99998900529594, Vector3D(-1043024.10832297, -264752028.890446, 0), 0.938272);

	p1.setElement(&dipole);
	p1.step();

	assert(p1.getElement() == &dipole);
	// We can see with that with the parameters given the particle is still in the same element
	assert(not dipole.isInNextElement(p1));

	// We have to "reduce" the speed or our `operator ==` won't evaluate it correctly
	// We are working at high speed (10e8) so small errors are way larger than our EPSILON (in globals.h)
	assert(p1.getSpeed() / 10e8 == p2.getSpeed() / 10e8);
	assert(p1.getMoment() == p2.getMoment());
	assert(p1.getPos() == p2.getPos());
	assert(Test::eq(p1.getEnergy(), p2.getEnergy()));
	assert(Test::eq(p1.getGamma(), p2.getGamma()));
	assert(Test::eq(p1.getMass(), p2.getMass()));
	assert(Test::eq(p1.getCharge(), p2.getCharge()));
	assert(Test::eq(p1.getChargeNumber(), p2.getChargeNumber()));

	/****************************************************************
	 * Quadrupole
	 ****************************************************************/
	// See example P10 (Week 6)

	// Badly Oriented (anti-clockwise) => will exchange the posIn and posOut
	// Made on purpose
	Quadrupole quadru(Vector3D(3, -1, 0), -1, Vector3D(0, -1, 0), 0.1, -1.2);

	assert(quadru.getPosIn() == Vector3D(3, 0, 0));
	assert(quadru.getPosOut() == Vector3D(3, -1, 0));
	assert(Test::eq(quadru.getRadius(), 0.1));
	assert(quadru.getField(Vector3D(3.01, 0, 0)) == Vector3D(0, 0, -0.012));

	Particle p3(Vector3D(3.01, 0, 0), Vector3D(0, -2.64754e8, 0), 0.938272);

	Particle p4(Vector3D(3.01, -0.00264754, 0), Vector3D(1427.7, -2.64754e+08, 0), 0.938272);

	p3.setElement(&quadru);
	p3.step();

	assert(p3.getElement() == &quadru);
	// Using exemple of P10 exercise, the particle should still be in the current element
	assert(not quadru.isInNextElement(p3));

	// We have to "reduce" the speed or our `operator ==` won't evaluate it correctly
	// We are working at high speed (10e8) so small errors are way larger than our EPSILON (in globals.h)
	assert(p3.getSpeed() / 10e8 == p4.getSpeed() / 10e8);
	assert(p3.getMoment() == p4.getMoment());
	assert(Test::eq(p3.getPos().getX(), p4.getPos().getX()));
	assert(Test::eq(p3.getPos().getY(), p4.getPos().getY()));
	assert(Test::eq(p3.getPos().getZ(), p4.getPos().getZ()));

	assert(Test::eq(p3.getEnergy(), p4.getEnergy()));
	assert(Test::eq(p3.getGamma(), p4.getGamma()));
	assert(Test::eq(p3.getMass(), p4.getMass()));
	assert(Test::eq(p3.getCharge(), p4.getCharge()));
	assert(Test::eq(p3.getChargeNumber(), p4.getChargeNumber()));

	/****************************************************************
	 * Straight
	 ****************************************************************/
	// We choose these values for the initial and final position so that the particle is outside the element after 1 step
	Straight straight1(Vector3D(3, 0, 0), Vector3D(3.008939, -0.392, 0), 0.5);

	assert(straight1.getPosIn() == Vector3D(3, 0, 0));
	assert(straight1.getPosOut() == Vector3D(3.008939, -0.392, 0));
	assert(Test::eq(straight1.getRadius(), 0.5));
	assert(straight1.getField(Vector3D(0, 0, 0)) == Vector3D(0, 0, 0));

	Particle p5(Vector3D(3.00894, -0.391837, 0), Vector3D(-210200, -2.64754e8, 0), 0.938272);

	// need a lot of decimals of the energy to have correct speed values
	Particle p6(Vector3D(3.008937898, -0.39448454, 0), 1.99998900525257, Vector3D(-210200, -2.64754e8, 0), 0.938272);

	p5.setElement(&straight1);
	p5.step();

	assert(p5.getElement() == &straight1);
	assert(straight1.isInNextElement(p5));

	// We have to "reduce" the speed or our `operator ==` won't evaluate it correctly
	// We are working at high speed (10e8) so small errors are way larger than our EPSILON (in globals.h)
	assert(p5.getSpeed() / 10e8 == p6.getSpeed() / 10e8);
	assert(p5.getMoment() == p6.getMoment());
	assert(p5.getPos() == p6.getPos());
	assert(Test::eq(p5.getEnergy(), p6.getEnergy()));
	assert(Test::eq(p5.getGamma(), p6.getGamma()));
	assert(Test::eq(p5.getMass(), p6.getMass()));
	assert(Test::eq(p5.getCharge(), p6.getCharge()));
	assert(Test::eq(p5.getChargeNumber(), p6.getChargeNumber()));

	/****************************************************************
	 * linkNext + updatePointedElement
	 ****************************************************************/
	Straight straight2(Vector3D(3, 0, 0), Vector3D(3.01, -1, 0), 0.1);
	Straight straight3(Vector3D(3.01, -1, 0), Vector3D(3.02, -2, 0), 0.1);

	Particle p7(Vector3D(3.015, -1.2, 0), Vector3D(-210200, -2.64754e8, 0), 0.938272);
	straight2.linkNext(straight3);

	assert(straight2.isInNextElement(p7));
	straight2.updatePointedElement(p7);
	assert(not straight3.isInNextElement(p7));

	/**
	 * For manual comparaison with the testAccelerator.cpp in the updateElement test (near the end)
	 */

	// p7.step();
	// cout << p7 << endl;

	return 0;
}
