#include <cmath>
#include "src/include/Vector3D.h"
#include "src/globals.h"

namespace CONVERT {
	/****************************************************************
	 * Mass
	 ****************************************************************/
	double MassEVtoSI(double const& val) { return val * CONSTANTS::E / std::pow(CONSTANTS::C, 2); }
	double MassGEVtoSI(double const& val) { return MassEVtoSI(val) * 1e9; }
	double MassSItoEV(double const& val) { return val * std::pow(CONSTANTS::C, 2) / CONSTANTS::E; }
	double MassSItoGEV(double const& val) { return MassSItoEV(val) / 1e9; }
	
	/****************************************************************
	 * Momentum
	 ****************************************************************/
	Vector3D MomentumEVtoSI(Vector3D const& val) { return val * CONSTANTS::E / CONSTANTS::C; }
	Vector3D MomentumGEVtoSI(Vector3D const& val) { return MomentumEVtoSI(val) * 1e9; }
	Vector3D MomentumSItoEV(Vector3D const& val) { return val * CONSTANTS::C / CONSTANTS::E; }
	Vector3D MomentumSItoGEV(Vector3D const& val) { return MomentumSItoEV(val) / 1e9; }
	
	/****************************************************************
	 * Energy
	 ****************************************************************/
	double EnergyEVtoSI(double const& val) { return val * CONSTANTS::E; }
	double EnergyGEVtoSI(double const& val) { return EnergyEVtoSI(val) * 1e9; }
	double EnergySItoEV(double const& val) { return val / CONSTANTS::E; }
	double EnergySItoGEV(double const& val) { return EnergySItoEV(val) / 1e9; }
}