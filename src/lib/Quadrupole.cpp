#include "src/include/Quadrupole.h"

using namespace std;

Vector3D Quadrupole::getField(Vector3D const& pos) const {
	return Vector3D(1, 0, 0);
}

bool Quadrupole::isOut(Particle const& p) const {
	return false;
}

bool Quadrupole::isInNext(Particle const& p) const {
	return false;
}



string Quadrupole::to_string() const {
	return "Quadrupole";
}
