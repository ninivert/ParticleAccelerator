#ifndef CONVERT_H
#define CONVERT_H

#pragma once

#include <cmath>

// Forward declaration
class Vector3D;

#include "globals.h"

/**
 * Utility to convert units from SI to GeV and back
 */

namespace CONVERT {
	/**
	 * Mass
	 */
	double MassEVtoSI(double val);
	double MassGeVtoSI(double val);
	double MassSItoEV(double val);
	double MassSItoGeV(double val);

	/**
	 * Momentum
	 */
	Vector3D MomentumEVtoSI(Vector3D const& val);
	Vector3D MomentumGeVtoSI(Vector3D const& val);
	Vector3D MomentumSItoEV(Vector3D const& val);
	Vector3D MomentumSItoGeV(Vector3D const& val);

	/**
	 * Energy
	 */
	double EnergyEVtoSI(double val);
	double EnergyGeVtoSI(double val);
	double EnergySItoEV(double val);
	double EnergySItoGeV(double val);
}

#endif
