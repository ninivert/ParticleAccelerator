#ifndef TEST_H
#define TEST_H

#pragma once

#include <iostream>
#include <cmath>
#include <cassert>
#include <string> // assert exceptions
#include "globals.h"
#include "exceptions.h"

/**
 * Utility functions used for testing
 */

class Test {
public:
	/**
	 * Test an equality between two doubles with error range `GLOBALS::EPSILON`
	 */

	static bool eq(double x, double y, double = GLOBALS::EPSILON);
};

/**
 * Macro to easily test if specific code throws an expression
 */

#ifndef ASSERT_EXCEPTION
#define ASSERT_EXCEPTION(__test__, __err__)\
try {\
	__test__;\
	std::cerr << "----------------ASSERT_EXCEPTION did not throw any exceptions !" << std::endl;\
	throw;\
} catch (OurException& e) {\
	assert(std::string(e.error()) == std::string(__err__));\
}
#endif

#endif
