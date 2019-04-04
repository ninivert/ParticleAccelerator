#include "src/globals.h"
#include "src/exceptions.h"
#include "src/include/bundle/Frodo.bundle.h"
#include "src/include/bundle/Accelerator.bundle.h"
#include "src/include/bundle/TextRenderer.bundle.h"
#include "test/lib/Test.h"

using namespace std;

int main() {
	TextRenderer engine;

	Frodo FRODO(
		Vector3D(1, 0, 0),
		Vector3D(1, -1, 0),
		1,
		1,
		0.25
	);

	Frodo SAM(
		Vector3D(1, -1, 0),
		1,
		Vector3D(0, -1, 0),
		1,
		1,
		0.25
	);

	Accelerator acc(&engine);
	acc.addElement(FRODO);
	acc.addElement(SAM);

	// acc.draw();
}
