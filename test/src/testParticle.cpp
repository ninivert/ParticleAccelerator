#include <iostream>
#include <cassert>
#include <cmath>
#include "src/include/Vector3D.h"
#include "src/include/Particle.h"
#include "test/lib/Test.h"

using namespace std;

int main() {

	Particle p1(Vector3D(3.00894, -0.391837, 0), Vector3D(-210200, -2.64754e8, 0), 0.938272, 1);
	cout << p1 << endl;
	p1.exertMagnetForce(Vector3D(0, 0, 7));
	p1.step();
	cout << p1 << endl;
}
