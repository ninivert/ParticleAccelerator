#include "include/bundle/Vector3D.bundle.h"
#include "include/bundle/Particle.bundle.h"
#include "globals.h"
#include "exceptions.h"
#include "include/bundle/Test.bundle.h"

using namespace std;

int main() {
	Particle p1(Vector3D(3.00894, -0.391837, 0), Vector3D(-210200, -2.64754e8, 0), 0.938272);
	Particle p2(Vector3D(2.99016, -0.391837, 0), 2, Vector3D(210200, -2.64754e8, 0), 0.938272);

	Particle p3(Vector3D(3.00892956975892, -0.394484520288904, 0), 1.99998900529594, Vector3D(-1043024.10832297, -264752028.890446, 0), 0.938272);
	Particle p4(Vector3D(2.99015377377424, -0.394484537620625, 0), 2.00000000004337, Vector3D(-622622.575845106, -264753762.062512, 0), 0.938272);

	p1.exertLorentzForce(Vector3D(0, 0, 7));
	p2.exertLorentzForce(Vector3D(0, 0, 7));

	p1.step();
	p2.step();

	// We have to "reduce" the speed or our `operator ==` won't evaluate it correctly
	// We are working at high speed (10e8) so small errors are way larger than our EPSILON (in globals.h)
	assert(p1.getSpeed() / 10e8 == p3.getSpeed() / 10e8);
	assert(p2.getSpeed() / 10e8 == p4.getSpeed() / 10e8);

	assert(p1.getMoment() == p3.getMoment());
	assert(p2.getMoment() == p4.getMoment());

	assert(p1.getPos() == p3.getPos());
	assert(Test::eq(p2.getPos().getX(), p4.getPos().getX()));
	assert(Test::eq(p2.getPos().getY(), p4.getPos().getY()));
	assert(Test::eq(p2.getPos().getZ(), p4.getPos().getZ()));

	assert(Test::eq(p1.getEnergy(), p3.getEnergy()));
	assert(Test::eq(p2.getEnergy(), p4.getEnergy()));

	assert(Test::eq(p1.getGamma(), p3.getGamma()));
	assert(Test::eq(p2.getGamma(), p4.getGamma()));

	assert(Test::eq(p1.getMass(), p3.getMass()));
	assert(Test::eq(p2.getMass(), p4.getMass()));

	assert(Test::eq(p1.getCharge(), p3.getCharge()));
	assert(Test::eq(p2.getCharge(), p4.getCharge()));

	assert(Test::eq(p1.getChargeNumber(), p3.getChargeNumber()));
	assert(Test::eq(p2.getChargeNumber(), p4.getChargeNumber()));

	return 0;
}
