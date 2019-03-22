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

namespace EXCEPTIONS {
	inline constexpr char DIV_0[]("Division by 0");
}

// Compiler macro
// __FILE__ and __LINE__ are compiler macros
#ifndef ERROR
#define ERROR(arg) throw OurException(arg, __FILE__, __LINE__);
#endif

#endif
