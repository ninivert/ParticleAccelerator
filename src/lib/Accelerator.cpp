#include "src/include/Accelerator.h"

using namespace std;

/****************************************************************
 * Constructors
 ****************************************************************/

Accelerator::Accelerator() {};

/****************************************************************
 * Methods
 ****************************************************************/

void Accelerator::step(double const& dt) {
	// Do nothing if dt is null
	if (abs(dt) < GLOBALS::DELTA) { return; }

	// Step through all the particles
	for (Particle & particle : particles) {
		particle.step(dt);
	}
}

void Accelerator::addElement(Element const& element) {
	elements.push_back(element);
}

void Accelerator::addElement(Element & element, Element & prevElement) {
	elements.push_back(element);
	prevElement.linkNext(element);
}

void Accelerator::addParticle(Particle const& particle) {
	particles.push_back(particle);
}

void Accelerator::clearParticles() { particles.clear(); }
void Accelerator::clearElements() { elements.clear(); }
void Accelerator::clear() {
	clearParticles();
	clearElements();
}

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

std::ostream& operator<< (std::ostream& stream, Accelerator const& a) {
	return stream << a.to_string();
}
