#pragma once

#ifndef GLOBALS_H
#define GLOBALS_H

/****************************************************************
 * Physical constants
 ****************************************************************/

namespace CONSTANTS {
	inline constexpr double EV(1.60217653e-19); // J
	inline constexpr double C(299792458); // m/s
	inline constexpr double M_PROTON(0.938272); // GeV/c^2
	inline constexpr double M_ELECTRON(5.10999e-4); // GeV/c^2
};

namespace UNITS {
	inline constexpr char ENERGY[]("GeV");
	inline constexpr char CHARGE[]("GeV");
	inline constexpr char MASS[]("GeV/c^2");
	inline constexpr char MOMENTUM[]("GeV/c");
	inline constexpr char FORCE[]("N");
	inline constexpr char DISTANCE[]("m");
}

/****************************************************************
 * Computational constants
 ****************************************************************/

namespace GLOBALS {
	inline constexpr double EPSILON(1e-6); // For double comparaison
	inline constexpr double DT(1e-1); // Timestep
};

#endif
