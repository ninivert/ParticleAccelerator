#ifndef GLOBALS_H
#define GLOBALS_H

#pragma once

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
}

/****************************************************************
 * Errors
 ****************************************************************/

#include <exception>
#include <string>
#include <stdexcept>

namespace EXCEPTIONS {
	/**
	 * Custom exeption class
	 * https://stackoverflow.com/questions/348833/how-to-know-the-exact-line-of-code-where-where-an-exception-has-been-caused#answer-348862
	 */

	// Queue USSR Anthem
	class OurException : public std::runtime_error {
	public:
		OurException(std::string const& arg, std::string const& file, int const& line)
		: std::runtime_error(arg), msg("At file " + file + ", line " + std::to_string(line) + "\n\t" + arg)
		{}

		// "throw" guarantees the compiler this function will NOT throw any exceptions
		const char * what() const throw() { return msg.c_str(); }

	private:
		std::string msg;
	};

	/**
	 * Exception strings
	 */

	inline constexpr char DIV0[]("Division by 0");
}

// Compiler macro
// __FILE__ and __LINE__ are compiler macros
#ifndef ERROR
#define ERROR(arg) throw EXCEPTIONS::OurException(arg, __FILE__, __LINE__);
#endif

#endif
