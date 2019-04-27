#include "src/include/bundle/Dipole.bundle.h"

using namespace std;

/****************************************************************
 * Constructors
 ****************************************************************/

Dipole::Dipole(Vector3D const& posIn, Vector3D const& posOut, double const& radius, double const& curvature, double const& B, Renderer * engine_ptr)
: Element(posIn, posOut, radius, engine_ptr), curvature(curvature), B(B),
  posCenter (0.5 * (posOut + posIn) + 1 / (curvature) * sqrt(1 - curvature * curvature * (posOut - posIn).normSquared()/ 4.0) * ((posOut - posIn) ^ Vector3D(0, 0, 1)) / (posOut - posIn).norm())
{}

/****************************************************************
 * Polymorphic copy for Accelerator
 ****************************************************************/

shared_ptr<Element> Dipole::copy() const { return cloneThis(); }

shared_ptr<Dipole> Dipole::cloneThis() const {
	return shared_ptr<Dipole>(new Dipole(*this));
}

/****************************************************************
 * Getters (virtual)
 ****************************************************************/

Vector3D Dipole::getField(Vector3D const& pos, bool const& methodChapi) const { return Vector3D(0, 0, B); }

Vector3D const Dipole::getNormalDirection(Vector3D const& pos) const {
	Vector3D X(pos - posCenter);
	Vector3D u(X - pos.getZ() * Vector3D(0, 0, 1));
	return ~u;
}

double Dipole::getParticleProgress(Vector3D const& pos, bool const& methodChapi) const {
	if (methodChapi) {
		bool const isInNextElement(Vector3D::tripleProduct(Vector3D(0, 0, 1), pos, getPosOut()) >= 0);
		if (isInNextElement) {
			return 2;
		} else {
			return 0.5;
		}
	} else {
		double ix(getPosIn().getX());
		double iy(getPosIn().getY());

		double totalAngle(atan2(getPosOut().getX(), getPosOut().getY()) - atan2(ix, iy));
		double angle(atan2(pos.getX(), pos.getY()) - atan2(ix, iy));

		return angle / totalAngle;
	}
}

double Dipole::getLength() const {
	double totalAngle(atan2(getPosOut().getX(), getPosOut().getY()) - atan2(getPosIn().getX(), getPosIn().getY()));
	if (totalAngle < 0) { totalAngle += 2 * M_PI; }
	return totalAngle / curvature;
}

Vector3D Dipole::getPosAtProgress(double const& progress) const {
	if (progress < 0 or progress > 1) { ERROR(EXCEPTIONS::BAD_PROGRESS); }

	double angle(atan2(getPosOut().getX(), getPosOut().getY()) - atan2(getPosIn().getX(), getPosIn().getY()));
	if (angle < 0) { angle += 2 * M_PI; }

	angle *= progress;
	Vector3D pos(getPosIn() - posCenter);

	pos.rotate(Vector3D(0, 0, -1), angle);
	pos += posCenter;
	return pos;
}

Vector3D Dipole::getVelAtProgress(double const& progress, bool const& clockwise) const {
	if (progress < 0 or progress > 1) { ERROR(EXCEPTIONS::BAD_PROGRESS); }

	Vector3D dir(getNormalDirection(getPosAtProgress(progress)));

	// 90° rotation (clockwise)
	dir ^= Vector3D(0, 0, 1);
	if (not clockwise) { dir *= -1; }
	return dir;
}

/****************************************************************
 * Setters
 ****************************************************************/

void Dipole::setB(double const& _B) { B = _B; }

/****************************************************************
 * Virtual methods
 ****************************************************************/

bool Dipole::isInWall(Particle const& p) const {
	Vector3D X(p.getPos() - posCenter);
	Vector3D u(X - p.getPos().getZ() * Vector3D(0, 0, 1));
	~u;
	return ((X - 1 / abs(curvature) * u).norm() > getRadius());
}

string Dipole::to_string() const {
	stringstream stream;
	stream
		<< STYLES::COLOR_CYAN
		<< "Dipole"
		<< STYLES::NONE
		<< endl;
	stream << Element::to_string();
	stream << setprecision(STYLES::PRECISION);
	stream << left;
	stream
		// Curvature
		<< setw(STYLES::PADDING_XSM) << ""
		<< setw(STYLES::PADDING_MD) << "Curvature"
		<< setw(STYLES::PADDING_LG) << curvature
		<< " (" << UNITS::CURVATURE << ")"
		<< endl
		// Curvature center
		<< setw(STYLES::PADDING_XSM) << ""
		<< setw(STYLES::PADDING_MD) << "Curv. center"
		<< setw(STYLES::PADDING_LG) << posCenter
		<< " (" << UNITS::DISTANCE << ")"
		<< endl
		// Magnetic field
		<< setw(STYLES::PADDING_XSM) << ""
		<< setw(STYLES::PADDING_MD) << "Magnetic field"
		<< setw(STYLES::PADDING_LG) << getField(Vector3D(0, 0, 0))
		<< " (" << UNITS::DISTANCE << ")"
		<< endl;
	return stream.str();
}

/****************************************************************
 * Drawing
 ****************************************************************/

void Dipole::draw(Renderer * engine_ptr) const {
	// No engine specified, try to substitute it ?
	if (engine_ptr == nullptr) {
		// Do we have another engine ?
		if (this->engine_ptr == nullptr) {
			ERROR(EXCEPTIONS::NULLPTR);
		} else {
			engine_ptr = this->engine_ptr;
		}
	}
	engine_ptr->draw(*this);
}
