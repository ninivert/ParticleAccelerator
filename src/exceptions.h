#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#pragma once

#include <exception>
#include <string>
#include <stdexcept>

/****************************************************************
 * Custom exeption class
 * https://stackoverflow.com/questions/348833/how-to-know-the-exact-line-of-code-where-where-an-exception-has-been-caused#answer-348862
 ****************************************************************/

class OurException : public std::runtime_error {
public:
	OurException(std::string const& arg, std::string const& file, int const& line)
	: std::runtime_error(arg),
	  msg("At file " + file + ", line " + std::to_string(line) + "\n\t" + arg),
	  exceptionCode(arg)
	{}

	// "throw" guarantees the compiler this function will NOT throw any exceptions
	const char * what() const throw() { return msg.c_str(); }
	const char * error() const throw() { return exceptionCode.c_str(); }

private:
	std::string exceptionCode;
	std::string msg;
};

namespace EXCEPTIONS {
	/**
	 * Division by 0
	 */

	inline constexpr char DIV_0[]("Division by 0");

	/**
	 * Pointer is nullptr
	 */

	inline constexpr char NULLPTR[]("Pointer may not be a nullptr");

	/**
	 * Class Element : Input and output positions are colinear
	 */

	inline constexpr char BAD_ORIENTATION[]("Input and output positions are colinear");

	/**
	 * Class Accelerator : there is no element in which to add the particle
	 */

	inline constexpr char NO_ELEMENTS[]("Accelerator needs to contain at least one element before adding a particle");
}

/**
 * Compiler macro
 * __FILE__ and __LINE__ are compiler macros
 *
 * Throws a new instance of `OurException`
 * Such as : DIV_0
 */

#ifndef ERROR
#define ERROR(arg) throw OurException(arg, __FILE__, __LINE__);
#endif

#endif
