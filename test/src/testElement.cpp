#include "src/globals.h"
#include "src/exceptions.h"
#include "src/include/Vector3D.h"
#include "src/include/Particle.h"
#include "src/include/Element.h"
#include "src/include/Dipole.h"
#include "src/include/Quadrupole.h"
#include "test/lib/Test.h"

using namespace std;

int main() {

	// Dipole

	Dipole dipole(Vector3D(1, 0, 0), Vector3D(0, -1, 0), 0.1, -1, 7);

	assert(dipole.getPosIn() == Vector3D(1, 0, 0));
	assert(dipole.getPosOut() == Vector3D(0, -1, 0));
	assert(Test::eq(dipole.getRadius(), 0.1));
	assert(dipole.getField(Vector3D(0, 0, 0)) == Vector3D(0, 0, 7));

	return 0;
}
