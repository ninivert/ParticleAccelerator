#include <iostream>
#include <cassert>
#include "src/include/Converter.h"
#include "src/globals.h"
#include "test/lib/Test.h"

using namespace std;

int main() {
	//

	// Energy
	assert(CONVERT::EnergyEVtoSI(1) == CONSTANTS::E);
	assert(CONVERT::EnergyGEVtoSI(1) == CONSTANTS::E * 1e9);
	assert(CONVERT::EnergySItoEV(CONSTANTS::E) == 1);
	assert(CONVERT::EnergySItoGEV(CONSTANTS::E) == 1e-9);
}