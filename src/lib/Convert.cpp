#include "src/include/bundle/Convert.bundle.h"

/**
 * Mass
 */

double CONVERT::MassEVtoSI(double const& val) { return val * CONSTANTS::EV / std::pow(CONSTANTS::C, 2); }
double CONVERT::MassGeVtoSI(double const& val) { return MassEVtoSI(val) * 1e9; }
double CONVERT::MassSItoEV(double const& val) { return val * std::pow(CONSTANTS::C, 2) / CONSTANTS::EV; }
double CONVERT::MassSItoGeV(double const& val) { return MassSItoEV(val) / 1e9; }

/**
 * Momentum
 */

Vector3D CONVERT::MomentumEVtoSI(Vector3D const& val) { return val * CONSTANTS::EV / CONSTANTS::C; }
Vector3D CONVERT::MomentumGeVtoSI(Vector3D const& val) { return MomentumEVtoSI(val) * 1e9; }
Vector3D CONVERT::MomentumSItoEV(Vector3D const& val) { return val * CONSTANTS::C / CONSTANTS::EV; }
Vector3D CONVERT::MomentumSItoGeV(Vector3D const& val) { return MomentumSItoEV(val) / 1e9; }

/**
 * Energy
 */

double CONVERT::EnergyEVtoSI(double const& val) { return val * CONSTANTS::EV; }
double CONVERT::EnergyGeVtoSI(double const& val) { return EnergyEVtoSI(val) * 1e9; }
double CONVERT::EnergySItoEV(double const& val) { return val / CONSTANTS::EV; }
double CONVERT::EnergySItoGeV(double const& val) { return EnergySItoEV(val) / 1e9; }
