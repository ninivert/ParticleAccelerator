#include <iostream>
#include <cassert>
#include <cmath>
#include "src/include/Vector3D.h"
#include "test/lib/Test.h"

using namespace std;

int main() {
	Vector3D v1; // no const here because we call v1.normalize() later on
				 // test of default constructor
	v1 += Vector3D(2, -5, 6);
	Vector3D v2(3, -7, -2); // no const because we use += and -= later on
	Vector3D const v3(4, 7, -1);
	Vector3D const v4(-3, 3, -3);
	Vector3D const v5(4, -3, 0);


	// cout << v1 << endl;
	// cout << v2 << endl;
	// cout << v3 << endl;
	// cout << v4 << endl;
	// cout << v5 << endl;

	// cout << "\nARITHMETIC\n\n";

	// cout << "Operator +\n";
	assert((v1 + v2) == Vector3D(5, -12, 4));
	assert((v2 + v1) == Vector3D(5, -12, 4));
		// cout << "\tpassed\n";
		// cout << v1 + v2 << endl;

	// cout << "Operator +=\n";
	assert((v1 += v2) == Vector3D(5, -12, 4));
	assert((v2 += v1) == Vector3D(8, -19, 2));
		// cout << "\tpassed\n";
		// cout << (v1 += v2) << endl;
		// cout << (v2 += v1) << endl;

	// cout << "Operator -=\n";
	assert((v2 -= v1) == Vector3D(3, -7, -2));
	assert((v1 -= v2) == Vector3D(2, -5, 6));
		// cout << "\tpassed\n";
		// cout << (v2 -= v1) << endl;
		// cout << (v1 -= v2) << endl;

	// cout << "Operator -\n";
	assert((v1 - v2) == Vector3D(-1, 2, 8));
	assert((v2 - v1) == Vector3D(1, -2, -8));
		// cout << "\tpassed\n";
		// cout << v1 - v2 << endl;

	// cout << "Operator * (scalar)\n";
	assert((v1 * 2) == Vector3D(4, -10, 12));
		// cout << "\tpassed\n";
		// cout << v1 * 2 << endl;

	// cout << "Operator *= (scalar)\n";
	assert((v2 *= 6) == Vector3D(18, -42, -12));
	assert((v2 *= 0.5) == Vector3D(9, -21, -6));
		// cout << "\tpassed\n";
		// cout << (v2 *= 6) << endl;
		// cout << (v1 *= 0.5) << endl;

	// cout << "Operator / (scalar)\n";
	assert((v1 / 3) == Vector3D(0.666667, -1.666667, 2.000000));
		// cout << "\tpassed\n";
		// cout << "\t";
		// cout << v1 / 3 << endl;

	// cout << "Operator /= (scalar)\n";
	assert((v2 /= 3) == Vector3D(3, -7, -2));
	assert((v2 /= 1) == Vector3D(3, -7, -2));
		// cout << "\tpassed\n";
		// cout << (v2 /= 3) << endl;
		// cout << (v1 /= 1) << endl;

	// cout << "Operator * (Vector3D: dot product)\n";
	assert((v1 * v2) == 29);
	assert((v2 * v1) == 29);
		// cout << "\tpassed\n";
		// cout << v1 * v2 << endl;

	// cout << "Operator ^ (Vector3D: cross product)\n";
	assert((v1 ^ v2) == Vector3D(52, 22, 1));
	assert((v2 ^ v1) == Vector3D(-52, -22, -1));
		// cout << "\tpassed\n";
		// cout << (v1 ^ v2) << endl;
	assert((v1 ^ v2) * v2 == 0);
		// cout << "\tpassed\n";
		// cout << (v1 ^ v2) * v2 << endl;
	assert((v1 ^ v2) * v1 == 0);
		// cout << "\tpassed\n";
		// cout << (v1 ^ v2) * v1 << endl;

	Vector3D const v6(v1);
	// cout << v6 << endl;
	// cout << "Operator ^= (Vector3D: cross product)\n";
	assert((v1 ^= v2) == Vector3D(52, 22, 1));
		// cout << "\tpassed\n";
		// cout << v1 << endl;
	v1 = v6;

	// cout << "Triple Product (Vector3D: static method triple product)\n";
	assert(Vector3D::tripleProduct(v1, v2, v3) == 361);
	assert(Vector3D::tripleProduct(v2, v1, v3) == -361);
	assert(Vector3D::tripleProduct(v1, v1, v3) == 0);
		// cout << "\tpassed\n";
		// cout << Vector3D::tripleProduct(v1, v2, v3) << endl;

	// cout << "Norm\n";
	assert(v5.norm() == 5);
		// cout << "\tpassed\n";
		// cout << v5.norm() << endl;

	// cout << "NormSquared\n";
	assert(v1.normSquared() == 65);
		// cout << "\tpassed\n";
		// cout << v1.normSquared() << endl;

	// cout << "\nCOMPARAISON\n\n";

	// cout << "Operator == (Vector3D: equality test)\n";
	assert((v1 == v1) == 1);
		// cout << (v1 == v1) << endl;
		// cout << "\tpassed\n";
	assert((v1 == v2) == 0);
		// cout << (v1 == v2) << endl;
		// cout << "\tpassed\n";

	// cout << "Operator != (Vector3D: inequality test)\n";
	assert((v1 != v1) == 0);
		// cout << (v1 == v1) << endl;
		// cout << "\tpassed\n";
	assert((v1 != v4) == 1);
		// cout << (v1 == v2) << endl;
		// cout << "\tpassed\n";

	// cout << "\nASSIGNMENT\n\n";

	// cout << "Operator = (Vector3D: assignement test)\n";
	v1 = v2;
	assert((v1 == v2) == 1);
		// cout << "\tpassed\n";
		// cout << (v1 == v2) << endl;

	// cout << "\nNORMALIZATION\n\n";

	// cout << "Operator ~ (Vector3D: reduce to unit vector test)\n";
	v1 = v5;
	~v1;
	assert(Test::eq((v1.norm()),1));
		// cout << "\tpas...\n";
	assert((v1 * v5) == v5.norm());
		// cout << "\t...sed\n";
		// cout << v1 << endl;

	v1 = v5;
	v2 = v3;
	// cout << "\nROTATION\n\n";

	assert(v1.rotate((v1 ^ v2), M_PI) == v5 * (-1));

	v1.setNull();

	assert(v1 == Vector3D(0, 0, 0));
		// cout << "\tpassed\n";
		// cout << v1 * (-1) << endl;
		// cout << v5 << endl;

	// cout << "\nPASSED ALL TESTS.\n";

	return 0;
}
