#include <iostream>
#include <cassert>
#include <cmath>
#include "src/include/Vector3D.h"
#include "src/include/Particle.h"
#include "test/lib/Test.h"

using namespace std;

int main() {
	Particle p1(Vector3D(3.00894, -0.391837, 0), Vector3D(-210200, -2.64754e8, 0), 0.938272);
	Particle p2(Vector3D(2.99016, -0.391837, 0), 2, Vector3D(210200, -2.64754e8, 0), 0.938272);

	Particle p3(Vector3D(3.00893, -0.394485, 0), 1.99999, Vector3D(-1.04302e6, -2.64752e8, 0), 0.938272);
	Particle p4(Vector3D(2.99015, -0.394485, 0), 2, Vector3D(-622623, -2.64754e8, 0), 0.938272);

	cout << "P1 : \n" << p1 << endl;
	cout << "P2 : \n" << p2 << endl;

	p1.exertLorentzForce(Vector3D(0, 0, 7));
	p2.exertLorentzForce(Vector3D(0, 0, 7));

	p1.step();
	p2.step();

	cout << "P1 : \n" << p1 << endl;
	cout << "P2 : \n" << p2 << endl;

	// cout << "Speed\n";
	// We have to "reduce" the speed or our `operator ==` won't evaluate it correctly
	// We are working at high speed (10e8) so small errors are way larger than our EPSILON (in globals.h)
	assert(p1.getSpeed() / 10e8 == p3.getSpeed() / 10e8);
		// cout << p1.getSpeed() << endl << p3.getSpeed() << endl;
	assert(p2.getSpeed() / 10e8 == p4.getSpeed() / 10e8);
		// cout << p2.getSpeed() << endl << p4.getSpeed() << endl;

	// cout << "Momentum\n";
	assert(p1.getMoment() == p3.getMoment());
		// cout << p1.getMoment() << endl << p3.getMoment() << endl;
	assert(p2.getMoment() == p4.getMoment());
		// cout << p2.getMoment() << endl << p4.getMoment() << endl;

	// cout << "Position\n";
	assert(p1.getPos() == p3.getPos());
		// cout << p1.getPos() << endl << p3.getPos() << endl;
	assert(true == Test::eq(p2.getPos().getX(), p4.getPos().getX()));
	assert(true == Test::eq(p2.getPos().getY(), p4.getPos().getY()));
	assert(true == Test::eq(p2.getPos().getZ(), p4.getPos().getZ()));
		// cout << p2.getPos() << endl << p4.getPos() << endl;

	// cout << "Energy\n";
	assert(true == Test::eq(p1.getEnergy(), p3.getEnergy()));
		// cout << p1.getEnergy() << endl << p3.getEnergy() << endl;
	assert(true == Test::eq(p2.getEnergy(), p4.getEnergy()));
		// cout << p2.getEnergy() << endl << p4.getEnergy() << endl;

	// cout << "Gamma\n";
	assert(true == Test::eq(p1.getGamma(), p3.getGamma()));
		// cout << p1.getGamma() << endl << p3.getGamma() << endl;
	assert(true == Test::eq(p2.getGamma(), p4.getGamma()));
		// cout << p2.getGamma() << endl << p4.getGamma() << endl;

	// cout << "Mass\n";
	assert(true == Test::eq(p1.getMass(), p3.getMass()));
		// cout << p1.getMass() << endl << p3.getMass() << endl;
	assert(true == Test::eq(p2.getMass(), p4.getMass()));
		// cout << p2.getMass() << endl << p4.getMass() << endl;

	// cout << "Charge\n";
	assert(true == Test::eq(p1.getCharge(), p3.getCharge()));
		// cout << p1.getCharge() << endl << p3.getCharge() << endl;
	assert(true == Test::eq(p2.getCharge(), p4.getCharge()));
		// cout << p2.getCharge() << endl << p4.getCharge() << endl;

	// cout << "Charge Number\n";
	assert(true == Test::eq(p1.getChargeNumber(), p3.getChargeNumber()));
		// cout << p1.getChargeNumber() << endl << p3.getChargeNumber() << endl;
	assert(true == Test::eq(p2.getChargeNumber(), p4.getChargeNumber()));
		// cout << p2.getChargeNumber() << endl << p4.getChargeNumber() << endl;

	// cout << "\nPASSED ALL TESTS.\n";
	return 0;
}
