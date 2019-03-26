#include "src/globals.h"
#include "src/exceptions.h"
#include "src/include/Vector3D.h"
#include "src/include/Particle.h"
#include "src/include/Element.h"
#include "src/include/Dipole.h"
#include "src/include/Quadrupole.h"
#include "src/include/Straight.h"
#include "test/lib/Test.h"

#include <iomanip>


using namespace std;

int main() {

	/****************************************************************
	 * Dipole
	 ****************************************************************/

	Dipole dipole(Vector3D(1, 0, 0), Vector3D(0, -1, 0), 0.1, -1, 5.12);

	assert(dipole.getPosIn() == Vector3D(1, 0, 0));
	assert(dipole.getPosOut() == Vector3D(0, -1, 0));
	assert(Test::eq(dipole.getRadius(), 0.1));
	assert(dipole.getField(Vector3D(0, 0, 0)) == Vector3D(0, 0, 5.12));
	dipole.setB(7);
	assert(dipole.getField(Vector3D(0, 0, 0)) == Vector3D(0, 0, 7));

	Particle p1(Vector3D(3.00894, -0.391837, 0), Vector3D(-210200, -2.64754e8, 0), 0.938272);
	Particle p2(Vector3D(3.00892956975892, -0.394484520288904, 0), 1.99998900529594, Vector3D(-1043024.10832297, -264752028.890446, 0), 0.938272);

	p1.setElement(&dipole);
	p1.step();

	// assert(dipole.isInNext(p1));

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

	// See example étape 6

	// Badly Oriented (anti-clockwise) => will exchange the posIn and posOut
	// Made on purpose
	// Quadrupole quadru(Vector3D(3, 0, 0), -1, Vector3D(0, -1, 0), 0.1, -1.2);

	// assert(quadru.getPosIn() == Vector3D(3, 2, 0));
	// assert(quadru.getPosOut() == Vector3D(3, 1, 0));
	// assert(Test::eq(quadru.getRadius(), 0.1));
	// assert(quadru.getField(Vector3D(0, 0, 0)) == Vector3D(0, 0, -3.6));

	// Particle p3(Vector3D(3.01, 0, 0), Vector3D(0, -2.64754e8, 0), 0.938272);

	// Particle p4(Vector3D(3.01, -0.00264754, 0), Vector3D(-1427.7, -2.64754e+08, 0), 0.938272);
	// p3.setElement(&quadru);

	// cout << p3 << endl;
	// p3.step();
	// cout << p3 << endl;

	// // assert(quadru.isInNext(p3));

	// // We have to "reduce" the speed or our `operator ==` won't evaluate it correctly
	// // We are working at high speed (10e8) so small errors are way larger than our EPSILON (in globals.h)
	// // assert(p3.getSpeed() / 10e8 == p4.getSpeed() / 10e8);
	// assert(p3.getMoment() == p4.getMoment());
	// assert(Test::eq(p3.getPos().getX(), p4.getPos().getX()));
	// assert(Test::eq(p3.getPos().getY(), p4.getPos().getY()));
	// assert(Test::eq(p3.getPos().getZ(), p4.getPos().getZ()));

	// assert(Test::eq(p3.getEnergy(), p4.getEnergy()));
	// assert(Test::eq(p3.getGamma(), p4.getGamma()));
	// assert(Test::eq(p3.getMass(), p4.getMass()));
	// assert(Test::eq(p3.getCharge(), p4.getCharge()));
	// assert(Test::eq(p3.getChargeNumber(), p4.getChargeNumber()));

	/****************************************************************
	 * Straight
	 ****************************************************************/

	Straight straight(Vector3D(1, 0, 0), sqrt(2), Vector3D(-1, -1, 0), 0.1);

	assert(straight.getPosIn() == Vector3D(1, 0, 0));
	assert(straight.getPosOut() == Vector3D(0, -1, 0));
	assert(Test::eq(straight.getRadius(), 0.1));
	assert(straight.getField(Vector3D(0, 0, 0)) == Vector3D(0, 0, 0));

	Particle p5(Vector3D(3.00894, -0.391837, 0), Vector3D(-210200, -2.64754e8, 0), 0.938272);

	// need a lot of decimals of the ernergy to have correct speed values
	Particle p6(Vector3D(3.008937898, -0.39448454, 0), 1.99998900525257, Vector3D(-210200, -2.64754e8, 0), 0.938272);

	p5.setElement(&straight);
	p5.step();

	// assert(straight.isInNext(p5));

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

	return 0;
}
