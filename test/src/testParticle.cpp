#include <iostream>
#include <cassert>
#include <cmath>
#include "src/include/Vector3D.h"
#include "src/include/Particle.h"
#include "test/lib/Test.h"

using namespace std;

int main() {
	Particle p1(Vector3D(), Vector3D(), 1, 1);
	cout << p1 << endl;
	p1.exertForce(Vector3D(1, 0, 0));
	p1.step();
	cout << p1 << endl;
}
