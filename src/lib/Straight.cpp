#include "src/include/Straight.h"

using namespace std;



/****************************************************************
 * getter
 ****************************************************************/

Vector3D Straight::getField(Vector3D const& pos) const { return Vector3D(0, 0, 0); }

/****************************************************************
 * methods
 ****************************************************************/

bool Straight::isOut(Particle const& p) const {
	return false;
}

bool Straight::isInNext(Particle const& p) const {
	return false;
}

string Straight::to_string() const {
	return "Straight : ";
}

