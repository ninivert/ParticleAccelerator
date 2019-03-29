#include "src/include/bundle/Accelerator.bundle.h"

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

	clearDeadParticles();

	// Step through all the particles
	for (unique_ptr<Particle> & particle : particles) {
		// Change the element if the particle goes out
		updateParticleElement(*particle);

		particle->step(dt);
	}
}

void Accelerator::addElement(Element * element) {
	// Protection against empty pointers
	if (element != nullptr) {
		// Protection against empty vector elements
		if (elements.size() > 0) {
			// Protection against non-touching elements
			if (elements[elements.size() - 1]->getPosOut() == element->getPosIn()) {
				elements[elements.size() - 1]->linkNext(*element);
				elements.push_back(shared_ptr<Element>(element));
			} else {
				ERROR(EXCEPTIONS::ELEMENTS_NOT_TOUCHING);
			}
		} else {
			elements.push_back(shared_ptr<Element>(element));
		}
	} else {
		ERROR(EXCEPTIONS::NULLPTR);
	}
}

void Accelerator::closeElementLoop() {
	// We need 2 elements
	if (elements.size() > 1) {
		if (elements[elements.size() - 1]->getPosOut() == elements[0]->getPosIn()) {
			elements[elements.size() - 1]->linkNext(*elements[0]);
		} else {
			ERROR(EXCEPTIONS::ELEMENT_LOOP_INCOMPLETE);
		}
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

void Accelerator::updateParticleElement(Particle & particle) const {
	if (particle.getElementPtr()->isInNextElement(particle)) {
		// Particle is in next element
		particle.getElementPtr()->updatePointedElement(particle);
	}
}

void Accelerator::clearDeadParticles() {
	// Remove particles that are out of the simulation
	size_t size(particles.size());
	for (size_t i(0); i < size; ++i) {
		if (particles[i]->getElementPtr()->isInWall(*particles[i])) {
			particles[i].reset();

			// using swap + pop_back
			// faster but changes indexes
			swap(particles[i], particles[size - 1]);
			particles.pop_back();

			// using erase
			// slower but preserves indexes
			// particles.erase(particles.begin() + i);

			// We resized the vector so we need to take it into account
			--size;
			// We need to evalute the new `particles[i]` that has been swapped
			--i;
		}
	}
}

/****************************************************************
 * Operator overloading
 ****************************************************************/

std::ostream& operator<< (std::ostream& stream, Accelerator const& a) {
	return stream << a.to_string();
}

/****************************************************************
 * Drawing
 ****************************************************************/

void Accelerator::draw() const {
	engine->draw(*this);
}
