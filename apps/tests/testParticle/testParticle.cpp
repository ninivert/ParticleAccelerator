#include "include/bundle/Vector3D.bundle.h"
#include "include/bundle/Particle.bundle.h"
#include "globals.h"
#include "exceptions.h"
#include "include/bundle/Test.bundle.h"

using namespace std;

int main() {
	Particle p1(Vector3D(3.00894, -0.391837, 0), 1.999989, Vector3D(-210200, -2.64754e8, 0), 0.938272);
	Particle p2(Vector3D(2.99016, -0.391837, 0), 2, Vector3D(210200, -2.64754e8, 0), 0.938272);

	Particle p3(Vector3D(3.00892956975892, -0.394484520288904, 0), 1.99998900529594, Vector3D(-1043024.10832297, -264752028.890446, 0), 0.938272);
	Particle p4(Vector3D(2.99015377377424, -0.394484537620625, 0), 2.00000000004337, Vector3D(-622622.575845106, -264753762.062512, 0), 0.938272);

	p1.exertLorentzForce(Vector3D(0, 0, 7));
	p2.exertLorentzForce(Vector3D(0, 0, 7));

	p1.step();
	p2.step();

	assert(Test::eq(p1.getSpeed().getX(), p3.getSpeed().getX(), 1e-3));
	assert(Test::eq(p1.getSpeed().getY(), p3.getSpeed().getY(), 1e-3));
	assert(Test::eq(p1.getSpeed().getZ(), p3.getSpeed().getZ(), 1e-3));

	assert(Test::eq(p2.getSpeed().getX(), p4.getSpeed().getX(), 1e-3));
	assert(Test::eq(p2.getSpeed().getY(), p4.getSpeed().getY(), 1e-3));
	assert(Test::eq(p2.getSpeed().getZ(), p4.getSpeed().getZ(), 1e-3));

	assert(p1.getMoment() == p3.getMoment());
	assert(p2.getMoment() == p4.getMoment());

	assert(Test::eq(p1.getPos().getX(), p3.getPos().getX(), 1e-3));
	assert(Test::eq(p1.getPos().getY(), p3.getPos().getY(), 1e-3));
	assert(Test::eq(p1.getPos().getZ(), p3.getPos().getZ(), 1e-3));

	assert(Test::eq(p2.getPos().getX(), p4.getPos().getX(), 1e-3));
	assert(Test::eq(p2.getPos().getY(), p4.getPos().getY(), 1e-3));
	assert(Test::eq(p2.getPos().getZ(), p4.getPos().getZ(), 1e-3));

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
