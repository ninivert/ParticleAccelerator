#include "src/globals.h"
#include "src/exceptions.h"
#include "src/include/bundle/Frodo.bundle.h"
#include "src/include/bundle/Accelerator.bundle.h"
#include "src/include/bundle/TextRenderer.bundle.h"
#include "test/lib/Test.h"

#include <iostream>

using namespace std;

int main() {
	TextRenderer engine;
	Accelerator acc;

	acc.addElement(new Frodo(
		Vector3D(1, 0, 0),
		Vector3D(1, -1, 0),
		1,
		1,
		0.25
	));

	acc.addElement(new Frodo(
		Vector3D(1, -1, 0),
		1,
		Vector3D(0, -1, 0),
		1,
		1,
		0.25
	));

	cout << acc << endl;
}
