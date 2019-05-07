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
	double MassEVtoSI(double const& val);
	double MassGeVtoSI(double const& val);
	double MassSItoEV(double const& val);
	double MassSItoGeV(double const& val);

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
	double EnergyEVtoSI(double const& val);
	double EnergyGeVtoSI(double const& val);
	double EnergySItoEV(double const& val);
	double EnergySItoGeV(double const& val);
}

#endif
