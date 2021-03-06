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

/**
 * Queue USSR Anthem
 */

class OurException : public std::runtime_error {
public:
	OurException(std::string const& arg, std::string const& file, int line)
	: std::runtime_error(arg),
	  msg("At file " + file + ", line " + std::to_string(line) + "\n\t" + arg),
	  exceptionCode(arg)
	{}

	// "throw" guarantees the compiler this function will NOT throw any exceptions
	const char * what() const throw() { return msg.c_str(); }
	const char * error() const throw() { return exceptionCode.c_str(); }

private:
	std::string msg;
	std::string exceptionCode;
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
	 * Class Element : Input and output positions are colinear on the line passing through the origin
	 */

	inline constexpr char BAD_ORIENTATION[]("Input and output positions are colinear on the line passing through the origin");

	/**
	 * Class Element : Element is going into the wrong direction (counter-clockwise)
	 */

	inline constexpr char BAD_DIRECTION[]("Element is facing the wrong direction (counter-clockwise)");

	/**
	 * Class Element : Some particle is not in the element and should therefore not have called
	 * the Element's methods
	 */

	inline constexpr char NOT_INSIDE_ELEMENT[]("Position given is outside the Element");

	/**
	 * Class Element : The particle is out of the Accelerator (outside the first / last Element)
	 */

	inline constexpr char OUTSIDE_ACCELERATOR[]("The Particle is now outside the accelerator (out of the first / last element)");

	/**
	 * Class Element : The progress given is not between 0 and 1
	 */

	inline constexpr char BAD_PROGRESS[]("The pourcentage (progress) must be between 0 and 1");

	/**
	 * Class Beam : The coefficient lambda (scaling factor) given is less than 1
	 */

	inline constexpr char BAD_LAMBDA[]("The coefficient lambda (scaling factor) given is less than 1");

	/**
	 * Class Beam : There is no particle : particleCount = 0
	 */

	inline constexpr char NO_PARTICLES[]("Beam needs to contain at least one particle");

	/**
	 * Class Accelerator : There is no element in which to add the particle
	 */

	inline constexpr char NO_ELEMENTS[]("Accelerator needs to contain at least one element before adding a particle");

	/**
	 * Class Accelerator : The input position of the new element does not coincide with the output position of the last element of the accelerator
	 */

	inline constexpr char ELEMENTS_NOT_TOUCHING[]("The new element needs to have the same input position as the output position of the last element of the accelerator");

	/**
	 * Class Accelerator : The position output of the last element does not coincide with the input position of the first element of the accelerator
	 */

	inline constexpr char ELEMENT_LOOP_INCOMPLETE[]("The last element needs to have the same output position as the input position of the first element of the accelerator");

	/**
	 * Class Accelerator : The particle given to initialize is outside the accelerator
	 */

	inline constexpr char PARTICLE_NOT_IN_ACCELERATOR[]("The particle to initialize is outside the Accelerator");

	/**
	 * Class TextRenderer : Opening fstream for writing to a file did not succeed
	 */

	inline constexpr char FILE_EXCEPTION[]("Something went wrong while opening the file");
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
