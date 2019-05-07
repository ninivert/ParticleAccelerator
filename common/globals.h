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
	inline constexpr char CURVATURE[]("1/m");
	inline constexpr char CHARGE[]("Coulomb");
	inline constexpr char MAGNETIC_FIELD[]("Tesla");
	inline constexpr char SCALAR[]("-");
}

/****************************************************************
 * Computational constants
 ****************************************************************/

namespace GLOBALS {
	inline constexpr double EPSILON(1e-10); // For double comparaison
	inline constexpr double DELTA(1e-30); // For division by 0 tests
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
	inline constexpr unsigned int PRECISION(8);
	inline constexpr char COLOR_BLACK[]("\033[30m");
	inline constexpr char COLOR_RED[]("\033[31m");
	inline constexpr char COLOR_GREEN[]("\033[32m");
	inline constexpr char COLOR_YELLOW[]("\033[33m");
	inline constexpr char COLOR_BLUE[]("\033[34m");
	inline constexpr char COLOR_PURPLE[]("\033[35m");
	inline constexpr char COLOR_CYAN[]("\033[36m");
	inline constexpr char COLOR_WHITE[]("\033[37m");
	inline constexpr char FORMAT_BOLD[]("\033[1m");
	inline constexpr char FORMAT_UNDERLINE[]("\033[4m");
	inline constexpr char FORMAT_BLINK[]("\033[5m");
	inline constexpr char FORMAT_REVERSE[]("\033[7m");
	inline constexpr char FORMAT_CONCEALED[]("\033[8m");
	inline constexpr char NONE[]("\033[0m");
}

/****************************************************************
 * Graphic settings
 ****************************************************************/

namespace GRAPHICS {
	inline constexpr double FOV(60); // 60 degrees
	inline constexpr double CLOSE_PLANE(0.1);
	inline constexpr double FAR_PLANE(1000);
	inline constexpr unsigned int PRECISION(32); // 32 steps per circle
}

/****************************************************************
 * Control settings
 ****************************************************************/

namespace CONTROLS {
	inline constexpr double TRANSLATION_SPEED(0.02);
	inline constexpr double ROTATION_SPEED(0.2);
	inline constexpr double SLOWMO(0.2);
}

#endif
