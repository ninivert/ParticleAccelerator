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

/****************************************************************
 * Setters
 ****************************************************************/

void Dipole::setB(double const& _B) { B = _B; }

/****************************************************************
 * Virtual methods
 ****************************************************************/

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

bool Dipole::isInWall(Particle const& p) const {
	Vector3D X(p.getPos() - posCenter);
	Vector3D u(X - p.getPos().getZ() * Vector3D(0, 0, 1));
	~u;
	return ((X - 1 / abs(curvature) * u).norm() > getRadius());
}

/****************************************************************
 * Drawing
 ****************************************************************/

void Dipole::draw() const {
	if (engine_ptr == nullptr) ERROR(EXCEPTIONS::NULLPTR);
	engine_ptr->draw(*this);
}

void Dipole::drawTo(Renderer * engine_ptr) const {
	if (engine_ptr == nullptr) ERROR(EXCEPTIONS::NULLPTR);
	engine_ptr->draw(*this);
}
