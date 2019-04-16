#include "src/globals.h"
#include "src/exceptions.h"
#include "src/include/bundle/Vector3D.bundle.h"
#include "src/include/bundle/Particle.bundle.h"
#include "src/include/bundle/Straight.bundle.h"
#include "src/include/bundle/Beam.bundle.h"
#include "test/lib/Test.h"

using namespace std;

int main() {
	Straight straight_1(Vector3D(3, 0, 0), Vector3D(-2, -1, 0), 0.08);
	Particle part_1(Vector3D(2.99, 0.01, 0.04), 2, Vector3D(-0.5, -0.5, 0.01), 0.938272);
	part_1.setElement(&straight_1);
	Beam beam_1(part_1);

	// cout << beam_1 << endl;

	Vector3D coeff(beam_1.getEllipsePhaseCoefR());
	// assert(Test::eq(1, coeff.getX() * coeff.getY() -coeff.getZ() * coeff.getZ()));

	return 0;
}
