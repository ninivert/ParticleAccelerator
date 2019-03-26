#include "src/include/Vector3D.h"
#include "src/globals.h"
#include "src/exceptions.h"
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

	assert((v1 + v2) == Vector3D(5, -12, 4));
	assert((v2 + v1) == Vector3D(5, -12, 4));

	assert((v1 += v2) == Vector3D(5, -12, 4));
	assert((v2 += v1) == Vector3D(8, -19, 2));

	assert((v2 -= v1) == Vector3D(3, -7, -2));
	assert((v1 -= v2) == Vector3D(2, -5, 6));

	assert((v1 - v2) == Vector3D(-1, 2, 8));
	assert((v2 - v1) == Vector3D(1, -2, -8));

	assert((v1 * 2) == Vector3D(4, -10, 12));

	assert((v2 *= 6) == Vector3D(18, -42, -12));
	assert((v2 *= 0.5) == Vector3D(9, -21, -6));

	assert((v1 / 3) == Vector3D(2/3.0, -5/3.0, 2.0));

	ASSERTEXCEPTION(v1 /= 0, EXCEPTIONS::DIV_0);

	assert((v2 /= 3) == Vector3D(3, -7, -2));
	assert((v2 /= 1) == Vector3D(3, -7, -2));

	assert((v1 * v2) == 29);
	assert((v2 * v1) == 29);

	assert((v1 ^ v2) == Vector3D(52, 22, 1));
	assert((v2 ^ v1) == Vector3D(-52, -22, -1));
	assert((v1 ^ v2) * v2 == 0);

	assert((v1 ^ v2) * v1 == 0);

	Vector3D const v6(v1);

	assert((v1 ^= v2) == Vector3D(52, 22, 1));

	v1 = v6;

	assert(Vector3D::tripleProduct(v1, v2, v3) == 361);
	assert(Vector3D::tripleProduct(v2, v1, v3) == -361);

	assert(v5.norm() == 5);

	assert(v1.normSquared() == 65);

	assert((v1 == v1) == 1);

	assert((v1 == v2) == 0);

	assert((v1 != v1) == 0);

	assert((v1 != v4) == 1);

	v1 = v2;
	assert((v1 == v2) == 1);

	v1 = v5;
	~v1;
	assert(Test::eq((v1.norm()),1));
	assert((v1 * v5) == v5.norm());

	v1 = v5;
	v2 = v3;

	assert(v1.rotate((v1 ^ v2), M_PI) == v5 * (-1));

	v1.setNull();

	assert(v1 == Vector3D(0, 0, 0));

	return 0;
}
