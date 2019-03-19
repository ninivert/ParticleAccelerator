#pragma once

#ifndef CONVERTER_H
#define CONVERTER_H

#include <cmath>
#include "src/include/Vector3D.h"
#include "src/globals.h"

namespace CONVERT {
	/****************************************************************
	 * Mass
	 ****************************************************************/
	inline double MassEVtoSI(double const& val) { return val * CONSTANTS::EV / std::pow(CONSTANTS::C, 2); }
	inline double MassGeVtoSI(double const& val) { return MassEVtoSI(val) * 1e9; }
	inline double MassSItoEV(double const& val) { return val * std::pow(CONSTANTS::C, 2) / CONSTANTS::EV; }
	inline double MassSItoGeV(double const& val) { return MassSItoEV(val) / 1e9; }

	/****************************************************************
	 * Momentum
	 ****************************************************************/
	inline Vector3D MomentumEVtoSI(Vector3D const& val) { return val * CONSTANTS::EV / CONSTANTS::C; }
	inline Vector3D MomentumGeVtoSI(Vector3D const& val) { return MomentumEVtoSI(val) * 1e9; }
	inline Vector3D MomentumSItoEV(Vector3D const& val) { return val * CONSTANTS::C / CONSTANTS::EV; }
	inline Vector3D MomentumSItoGeV(Vector3D const& val) { return MomentumSItoEV(val) / 1e9; }

	/****************************************************************
	 * Energy
	 ****************************************************************/
	inline double EnergyEVtoSI(double const& val) { return val * CONSTANTS::EV; }
	inline double EnergyGeVtoSI(double const& val) { return EnergyEVtoSI(val) * 1e9; }
	inline double EnergySItoEV(double const& val) { return val / CONSTANTS::EV; }
	inline double EnergySItoGeV(double const& val) { return EnergySItoEV(val) / 1e9; }
}

#endif
