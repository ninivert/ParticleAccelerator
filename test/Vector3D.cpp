#include <iostream>
#include <cassert>
#include "../src/lib/Vector3D.cpp"
#include "./Test.cpp"

using namespace std;

int main() {
	Vector3D v1(2, -5, 6);
	Vector3D v2(3, -7, -2);
	Vector3D v3(4, 7, -1);

	assert((v1 + v2) == Vector3D(5, -12, 4));

	cout << v1 << endl;
	cout << v2 << endl;
	cout << v3 << endl;

	cout << "ARITHMETIC" << endl;
	cout << v1 + v2 << endl;
	cout << v1 - v2 << endl;
	cout << v1 * 2 << endl;
	cout << v1 / 3 << endl;
	cout << v1 * v2 << endl;
	cout << (v1 ^ v2) << endl;
	cout << (v1 ^ v2) * v2 << endl;
	cout << (v1 ^ v2) * v1 << endl;

	cout << "COMPARAISON" << endl;
	cout << (v1 == v1) << endl;
	cout << (v1 == v2) << endl;

	cout << "TRIPLE PRODUCT" << endl;
	cout << v1 << endl;
	cout << (v2 ^ v3) << endl;
	cout << Vector3D::tripleProduct(v1, v2, v3) << endl;

	cout << "NORM" << endl;
	cout << v1.norm() << endl;
	cout << v1.normSquared() << endl;

	cout << "ASSIGNMENT" << endl;
	v1 = v2;
	cout << (v1 == v2) << endl;

	cout << "NORMALIZE" << endl;
	v1.normalize();
	cout << v1 << endl;

	cout << "Passed all tests." << endl;

}