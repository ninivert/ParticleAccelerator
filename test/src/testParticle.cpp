#include <iostream>
#include <cassert>
#include <cmath>
#include "src/include/Vector3D.h"
#include "src/include/Particle.h"
#include "test/lib/Test.h"

using namespace std;

int main() {

	Particle p1(Vector3D(3.00894, -0.391837, 0), Vector3D(-210200, -2.64754e8, 0), 0.938272, 1);
	Particle p2(Vector3D(2.99016, -0.391837, 0), 2, Vector3D(210200, -2.64754e8, 0), 0.938272, 1);
	cout << "P1 : \n" << p1 << endl;
	cout << "P2 : \n" << p2 << endl;
	p1.exertMagnetForce(Vector3D(0, 0, 7));
	p2.exertMagnetForce(Vector3D(0, 0, 7));
	p1.step();
	p2.step();
	cout << "P1 : \n" << p1 << endl;
	cout << "P2 : \n" << p2 << endl;
}
