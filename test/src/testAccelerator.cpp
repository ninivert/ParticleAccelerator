#include "src/globals.h"
#include "src/exceptions.h"
#include "src/include/Vector3D.h"
#include "src/include/Particle.h"
#include "src/include/Element.h"
#include "src/include/Dipole.h"
#include "src/include/Quadrupole.h"
#include "src/include/Accelerator.h"
#include "test/lib/Test.h"

using namespace std;

int main() {
	Accelerator acc;

	ASSERT_EXCEPTION(acc.addParticle(new Particle(Vector3D(1.00984, -0.191837, 0), Vector3D(-210200, -2.64754e8, 0), 0.938272)), EXCEPTIONS::NO_ELEMENTS);

	acc.addElement(new Dipole(Vector3D(1, 0, 0), Vector3D(0, -1, 0), 0.1, 1));

	acc.addParticle(new Particle(Vector3D(1.00984, -0.191837, 0), Vector3D(-210200, -2.64754e8, 0), 0.938272));
	acc.addParticle(new Particle(Vector3D(0.99016, -0.191837, 0), Vector3D(-210200, -2.64754e8, 0), 0.938272));

	cout << acc << endl;

	acc.clearParticles();

	cout << acc << endl;

	ASSERT_EXCEPTION(acc.addElement(nullptr), EXCEPTIONS::NULLPTR);
	ASSERT_EXCEPTION(acc.addParticle(nullptr), EXCEPTIONS::NULLPTR);

	return 0;
}
