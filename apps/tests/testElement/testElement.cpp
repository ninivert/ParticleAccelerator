#include "globals.h"
#include "exceptions.h"
#include "include/bundle/Vector3D.bundle.h"
#include "include/bundle/Particle.bundle.h"
#include "include/bundle/Quadrupole.bundle.h"
#include "include/bundle/Straight.bundle.h"
#include "include/bundle/Dipole.bundle.h"
#include "include/bundle/Element.bundle.h"
#include "include/bundle/Test.bundle.h"

using namespace std;

int main() {

	/****************************************************************
	 * Dipole
	 ****************************************************************/

	Dipole dipole(Vector3D(3, 0, 0), Vector3D(2, -1, 0), 0.1, 1, 5.12);

	// posCenter : (2, 0, 0)

	assert(dipole.getPosIn() == Vector3D(3, 0, 0));
	assert(dipole.getPosOut() == Vector3D(2, -1, 0));
	assert(Test::eq(dipole.getRadius(), 0.1));
	assert(dipole.getField(Vector3D(0, 0, 0)) == Vector3D(0, 0, 5.12));
	dipole.setB(7);
	assert(dipole.getField(Vector3D(0, 0, 0)) == Vector3D(0, 0, 7));

	Particle p1(Vector3D(3.00894, -0.391837, 0), 1.999989, Vector3D(-210200, -2.64754e8, 0), 0.938272);
	Particle p2(Vector3D(3.00892956975892, -0.394484520288904, 0), 1.99998900529594, Vector3D(-1043024.10832297, -264752028.890446, 0), 0.938272);

	p1.setElement(&dipole);
	p1.step();

	assert(p1.getElementPtr() == &dipole);
	// We can see with that with the parameters given the particle is still in the same element
	double dist(dipole.getParticleProgress(p1.getPos()));
	assert(dist <=1 and dist >= 0);

	assert(Test::eq(p1.getSpeed().getX(), p2.getSpeed().getX(), 1e-3));
	assert(Test::eq(p1.getSpeed().getY(), p2.getSpeed().getY(), 1e-3));
	assert(Test::eq(p1.getSpeed().getZ(), p2.getSpeed().getZ(), 1e-3));

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
	ASSERT_EXCEPTION(Quadrupole quadru(Vector3D(3, -1, 0), -1, Vector3D(0, -1, 0), 0.1, -1.2), EXCEPTIONS::BAD_DIRECTION);

	Quadrupole quadru(Vector3D(3, 0, 0), Vector3D(3, -1, 0), 0.1, -1.2);
	assert(quadru.getPosIn() == Vector3D(3, 0, 0));
	assert(quadru.getPosOut() == Vector3D(3, -1, 0));
	assert(Test::eq(quadru.getRadius(), 0.1));
	assert(quadru.getField(Vector3D(3.01, 0, 0)) == Vector3D(0, 0, -0.012));

	Particle p3(Vector3D(3.01, 0, 0), 1.9999868, Vector3D(0, -2.64754e8, 0), 0.938272);

	Particle p4(Vector3D(3.01, -0.00264754, 0), 1.9999868, Vector3D(1427.7, -2.64754e+08, 0), 0.938272);

	p3.setElement(&quadru);
	p3.step();

	assert(p3.getElementPtr() == &quadru);
	// Using exemple of P10 exercise, the particle should still be in the current element
	dist = quadru.getParticleProgress(p3.getPos());
	assert(dist <=1 and dist >= 0);

	assert(Test::eq(p3.getSpeed().getX(), p4.getSpeed().getX(), 1e-3));
	assert(Test::eq(p3.getSpeed().getY(), p4.getSpeed().getY(), 1e-3));
	assert(Test::eq(p3.getSpeed().getZ(), p4.getSpeed().getZ(), 1e-3));
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

	Particle p5(Vector3D(3.00894, -0.391837, 0), 1.999989, Vector3D(-210200, -2.64754e8, 0), 0.938272);

	// need a lot of decimals of the energy to have correct speed values
	Particle p6(Vector3D(3.008937898, -0.39448454, 0), 1.99998900525257, Vector3D(-210200, -2.64754e8, 0), 0.938272);

	p5.setElement(&straight1);
	p5.step();

	assert(p5.getElementPtr() == &straight1);

	dist = straight1.getParticleProgress(p5.getPos());
	assert(not (dist <=1 and dist >= 0));

	assert(Test::eq(p5.getSpeed().getX(), p6.getSpeed().getX(), 1e-3));
	assert(Test::eq(p5.getSpeed().getY(), p6.getSpeed().getY(), 1e-3));
	assert(Test::eq(p5.getSpeed().getZ(), p6.getSpeed().getZ(), 1e-3));
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

	Particle p7(Vector3D(3.015, -1.2, 0), 1, Vector3D(-210200, -2.64754e8, 0), 0.938272);
	straight2.linkNext(straight3);

	dist = straight2.getParticleProgress(p7.getPos());
	assert(not (dist <=1 and dist >= 0));
	straight2.updatePointedElement(p7);
	dist = straight3.getParticleProgress(p7.getPos());
	assert(dist <=1 and dist >= 0);

	/**
	 * For manual comparaison
	 */

	// p7.step();
	// cout << p7 << endl;

	return 0;
}
