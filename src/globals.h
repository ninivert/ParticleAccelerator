#ifndef GLOBALS_H
#define GLOBALS_H

/****************************************************************
 * Physical constants
 ****************************************************************/

namespace CONSTANTS {
	inline constexpr double EV(1.60217653e-19); // J
	inline constexpr double E(1.60217653e-19); // C
	inline constexpr double C(299792458); // m/s
	inline constexpr double M_PROTON(0.938272); // GeV/c^2
	inline constexpr double M_ELECTRON(5.10999e-4); // GeV/c^2
}

namespace UNITS {
	inline constexpr char ENERGY[]("GeV");
	inline constexpr char MOMENTUM[]("GeV/c");
	inline constexpr char MASS[]("GeV/c²");
	inline constexpr char SPEED[]("m/s");
	inline constexpr char FORCE[]("N");
	inline constexpr char DISTANCE[]("m");
	inline constexpr char CHARGE[]("Coulomb");
	inline constexpr char SCALAR[]("-");
}

/****************************************************************
 * Computational constants
 ****************************************************************/

namespace GLOBALS {
	inline constexpr double EPSILON(1e-6); // For double comparaison
	inline constexpr double DT(1e-11); // Timestep
}

/****************************************************************
 * Styling/display constants
 ****************************************************************/

namespace STYLES {
	inline constexpr unsigned int PADDING_XSM(4);
	inline constexpr unsigned int PADDING_SM(8);
	inline constexpr unsigned int PADDING_MD(16);
	inline constexpr unsigned int PADDING_LG(32);
	inline constexpr unsigned int PADDING_XLG(64);
	inline constexpr unsigned int PRECISION(6);
}

#endif
