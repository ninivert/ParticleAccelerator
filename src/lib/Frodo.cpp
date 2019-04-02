#include "src/include/bundle/Frodo.bundle.h"

/****************************************************************
 * Constructor
 ****************************************************************/

/****************************************************************
 * Getter (virtual)
 ****************************************************************/

Vector3D Frodo::getField(Vector3D const& pos) const {
	return Vector3D(0, 0, 0);
}

/****************************************************************
 * Virtual methods
 ****************************************************************/

bool Frodo::isInWall(Particle const& p) const {
	return false;
}

std::string Frodo::to_string() const {
	return "";
}

/****************************************************************
 * Drawing
 ****************************************************************/

void Frodo::draw() const {
	if (engine == nullptr) ERROR(EXCEPTIONS::NULLPTR);
	engine->draw(*this);
}

void Frodo::drawTo(Renderer * engine) const {
	if (engine == nullptr) ERROR(EXCEPTIONS::NULLPTR);
	engine->draw(*this);
}
