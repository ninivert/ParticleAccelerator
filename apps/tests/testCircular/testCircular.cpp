#include "globals.h"
#include "exceptions.h"
#include "include/bundle/Vector3D.bundle.h"
#include "include/bundle/Particle.bundle.h"
#include "include/bundle/Dipole.bundle.h"
#include "include/bundle/Test.bundle.h"

#include <cmath>

using namespace std;

int main() {
	Particle p1(Vector3D(2, 0, 0), 2, Vector3D(0.03, -1, 0.03), CONSTANTS::M_PROTON);
	Particle p2(Vector3D(0, 2, 0), 2, Vector3D(0.03, -1, 0.03), CONSTANTS::M_PROTON);
	Particle p3(Vector3D(2, 2, 0), 2, Vector3D(0.03, -1, 0.03), CONSTANTS::M_PROTON);
	Dipole dip(Vector3D(0, 2, 0), Vector3D(2, 0, 0), 1, 0.5, 1);

	double ix(dip.getPosIn().getX());
	double iy(dip.getPosIn().getY());

	double ox(dip.getPosOut().getX());
	double oy(dip.getPosOut().getY());

	double px1(p1.getPos().getX());
	double py1(p1.getPos().getY());
	double px2(p2.getPos().getX());
	double py2(p2.getPos().getY());
	double px3(p3.getPos().getX());
	double py3(p3.getPos().getY());

	double totalAngle(atan2(ox, oy) - atan2(ix, iy));
	double angle1(atan2(px1, py1) - atan2(ix, iy));
	double angle2(atan2(px2, py2) - atan2(ix, iy));
	double angle3(atan2(px3, py3) - atan2(ix, iy));

	assert(angle1 / totalAngle == 1);
	assert(angle2 / totalAngle == 0);
	assert(angle3 / totalAngle == 0.5);
}
