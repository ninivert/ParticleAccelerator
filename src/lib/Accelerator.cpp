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
 * Getter
 ****************************************************************/

/**
 * No see Accelerator.h
 */

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
	// Protection against empty pointers
	if (element != nullptr) {
		elements.push_back(shared_ptr<Element>(element));
	} else {
		ERROR(EXCEPTIONS::NULLPTR);
	}
}

void Accelerator::addElement(Element * element, Element * prevElement) {
	// Protection against empty pointers
	if (element != nullptr) {
		elements.push_back(shared_ptr<Element>(element));
		prevElement->linkNext(*element);
	} else {
		ERROR(EXCEPTIONS::NULLPTR);
	}
}

void Accelerator::addParticle(Particle * particle) {
	// Protection against empty pointers
	if (particle != nullptr) {
		// Protection against no element to point to
		if (elements.size() > 0) {
			particle->setElement(elements[0].get());
			particles.push_back(unique_ptr<Particle>(particle));
		} else {
			ERROR(EXCEPTIONS::NO_ELEMENTS);
		}
	} else {
		ERROR(EXCEPTIONS::NULLPTR);
	}
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
	stream << "Accelerator contains " << elements.size() << " element(s)" << endl;
	for (shared_ptr<Element> const& element : elements) stream << *element << endl;
	stream << "Accelerator contains " << particles.size() << " particle(s)" << endl;
	for (unique_ptr<Particle> const& particle : particles) stream << *particle << endl;
	return stream.str();
}

/****************************************************************
 * Operator overloading
 ****************************************************************/

std::ostream& operator<< (std::ostream& stream, Accelerator const& a) {
	return stream << a.to_string();
}
