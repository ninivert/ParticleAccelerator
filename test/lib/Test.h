#ifndef TEST_H
#define TEST_H

#pragma once

#include <cmath>
#include "src/globals.h"
#include "src/exceptions.h"

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

#ifndef TESTEXCEPTION
#define TESTEXCEPTION(arg) try { arg; } catch (OurException& e) { cout << "Correctly cought the following exception: " << e.what() << endl; }
#endif

#endif
