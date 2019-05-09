#include <iostream>

#include "globals.h"
#include "include/bundle/Vector3D.bundle.h"
#include "include/bundle/Straight.bundle.h"
#include "include/bundle/Dipole.bundle.h"
#include "include/bundle/Quadrupole.bundle.h"
#include "include/bundle/Frodo.bundle.h"
#include "include/bundle/Beam.bundle.h"
#include "include/bundle/Accelerator.bundle.h"
#include "include/bundle/TextRenderer.bundle.h"

using namespace std;

int main() {


	acc.addParticle(part_1);
	// acc.drawBeams();

	acc.step();

	acc.clearBeams();
}
