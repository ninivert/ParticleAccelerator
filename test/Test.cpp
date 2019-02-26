#include <cmath>
#include "../src/constants.cpp"

class Test {
public:
	static bool eq(double x, double y, double epsilon = EPSILON) {
		return (abs(x - y) <= epsilon);
	}
};

