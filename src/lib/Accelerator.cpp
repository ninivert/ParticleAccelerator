#include "src/include/Accelerator.h"

using namespace std;

/****************************************************************
 * Constructors
 ****************************************************************/

Accelerator::Accelerator() {};

/****************************************************************
 * Methods
 ****************************************************************/

/**
 * Simulate the particle accelerator over a timestep dt
 *
 * If dt is null (aka inferior to GLOBALS::DELTA), then this doesn't do anything
 */

void Accelerator::step(double const& dt) {
	// Do nothing if dt is null
	if (abs(dt) < GLOBALS::DELTA) { return; }

	// Step through all the particles
	for (Particle & particle : particles) {
		particle.step(dt);
	}
}

/**
 * Add an element (dipole, quadrupole, etc.) to the accelerator
 *
 * This element is unlinked from any other element
 */

void Accelerator::addElement(Element const& element) {
	elements.push_back(element);
}

/**
 * Add an element (dipole, quadrupole, etc.) to the accelerator
 * and assemble it after another element
 *
 * element.prev and prevElement.next pointers are modified to assure cohesion
 */

void Accelerator::addElement(Element & element, Element & prevElement) {
	elements.push_back(element);
	prevElement.linkNext(element);
}

/**
 * Adds a particle to the accelerator
 */

void Accelerator::addParticle(Particle const& particle) {
	particles.push_back(particle);
}

/**
 * Removes all particles from the accelerator
 */

void Accelerator::clearParticles() { particles.clear(); }

/**
 * Removes all elements from the accelerator
 */

void Accelerator::clearElements() { elements.clear(); }

/**
 * Removes all elements and particles from the accelerator
 */

void Accelerator::clear() {
	clearParticles();
	clearElements();
}

/**
 * Generates the string representation of the accelerator
 */

string Accelerator::to_string() const {
	stringstream stream;
	stream << setprecision(STYLES::PRECISION);
	stream << left;
	stream << "Accelerator contains the following elements"s << endl;
	for (Element const& element : elements) stream << element << endl;
	stream << "Accelerator contains the following particles"s << endl;
	for (Particle const& particle : particles) stream << particle << endl;
	return stream.str();
}

/****************************************************************
 * Operator overloading
 ****************************************************************/

/**
 * Overloads ostream operator <<
 */

std::ostream& operator<< (std::ostream& stream, Accelerator const& a) {
	return stream << a.to_string();
}
