#include <cassert>
#include <iostream>
#include "src/include/Converter.h"
#include "src/globals.h"
#include "test/lib/Test.h"

using namespace std;

int main() {
	// Mass
	assert(CONVERT::MassSItoEV(CONVERT::MassGeVtoSI(CONSTANTS::M_ELECTRON)) == CONSTANTS::M_ELECTRON * 1e9);

	// Momentum
	// Remark: our threshold for double comparaison is 1e-6 per default,
	// so a small error would probably never be detected.
	// We are however pretty confident everything works from the few tests we already ran
	// and the correctness of the Particle test results
	assert(CONVERT::MomentumGeVtoSI(Vector3D(1, 2, -1)) == Vector3D(5.34429e-19, 1.06886e-18, -5.34429e-19));

	// Energy
	assert(CONVERT::EnergyEVtoSI(1) == CONSTANTS::EV);
	assert(CONVERT::EnergyGeVtoSI(1) == CONSTANTS::EV * 1e9);
	assert(CONVERT::EnergySItoEV(CONSTANTS::EV) == 1);
	assert(CONVERT::EnergySItoGeV(CONSTANTS::EV) == 1e-9);

	return 0;
}
