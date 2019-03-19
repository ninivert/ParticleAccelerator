#include <cassert>
#include <iostream>
#include "src/include/Converter.h"
#include "src/globals.h"
#include "test/lib/Test.h"

using namespace std;

int main() {
	// Mass
	// cout << CONVERT::MassSItoEV(CONVERT::MassGeVtoSI(CONSTANTS::M_ELECTRON)) << endl;

	// Momentum
	cout << CONVERT::MomentumGeVtoSI(Vector3D(1, 2, -1)) << endl;

	// Energy
	assert(CONVERT::EnergyEVtoSI(1) == CONSTANTS::EV);
	assert(CONVERT::EnergyGeVtoSI(1) == CONSTANTS::EV * 1e9);
	assert(CONVERT::EnergySItoEV(CONSTANTS::EV) == 1);
	assert(CONVERT::EnergySItoGeV(CONSTANTS::EV) == 1e-9);
}
