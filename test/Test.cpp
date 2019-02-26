#include <cmath>

class Test {
public:
	static bool eq(double x, double y, double epsilon = 1e-6) {
		return (abs(x - y) <= epsilon);
	}
};

