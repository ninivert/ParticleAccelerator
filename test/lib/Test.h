#include <cmath>
#include "src/globals.h"

class Test {
public:
	static bool eq(double, double, double = GLOBALS::EPSILON);
};
