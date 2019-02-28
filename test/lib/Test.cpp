#include "Test.h"

bool Test::eq(double x, double y, double epsilon) {
	return (abs(x - y) <= epsilon);
}
