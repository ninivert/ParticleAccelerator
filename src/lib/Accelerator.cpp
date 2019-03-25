#include "src/include/Accelerator.h"

using namespace std;

/****************************************************************
 * Constructor
 ****************************************************************/

Accelerator::Accelerator() {};

/****************************************************************
 * Destructor
 ****************************************************************/

Accelerator::~Accelerator() { this->clear(); };

/****************************************************************
 * Methods
 ****************************************************************/

void Accelerator::step(double const& dt) {
	// Do nothing if dt is null
	if (abs(dt) < GLOBALS::DELTA) { return; }

	// Step through all the particles
	for (unique_ptr<Particle> & particle : particles) {
		particle->step(dt);
	}
}

void Accelerator::addElement(Element * element) {
	elements.push_back(shared_ptr<Element>(element));
}

void Accelerator::addElement(Element * element, Element * prevElement) {
	elements.push_back(shared_ptr<Element>(element));
	prevElement->linkNext(*element);
}

void Accelerator::addParticle(Particle * particle) {
	particles.push_back(unique_ptr<Particle>(particle));
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
	for (shared_ptr<Element> const& element : elements) stream << *element << endl;
	stream << "Accelerator contains the following particles"s << endl;
	for (unique_ptr<Particle> const& particle : particles) stream << *particle << endl;
	return stream.str();
}

/****************************************************************
 * Operator overloading
 ****************************************************************/

std::ostream& operator<< (std::ostream& stream, Accelerator const& a) {
	return stream << a.to_string();
}
