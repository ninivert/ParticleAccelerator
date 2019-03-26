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
	Vector3D X(p.getPos() - getPosIn());
	Vector3D d(getPosOut() - getPosIn());
	~d;
	return ((X - (X * d) * d).norm() > getRadius());
}

string Straight::to_string() const {
	stringstream stream;
	stream << "Straight : " << endl;
	stream << Element::to_string();
	return stream.str();
}

