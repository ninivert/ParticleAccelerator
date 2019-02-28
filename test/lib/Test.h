#include <cmath>
#include "src/constants.h"

class Test {
public:
	static bool eq(double, double, double = CONSTANTS::EPSILON);
};
