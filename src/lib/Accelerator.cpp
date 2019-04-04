#include "src/include/bundle/Accelerator.bundle.h"

using namespace std;

/****************************************************************
 * Constructor
 ****************************************************************/

Accelerator::Accelerator(Renderer * engine_ptr)
: Drawable(engine_ptr)
{}

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
	for (unique_ptr<Particle> & particle_ptr : particles_ptr) {
		// Change the element if the particle goes out
		if (particle_ptr->getElementPtr()->isInNextElement(*particle_ptr)) {
			// Particle is in next element
			particle_ptr->getElementPtr()->updatePointedElement(*particle_ptr);
		}

		particle_ptr->step(dt);
	}
}

void Accelerator::addElement(Element const& element) {
	// Protection against empty vector elements
	if (elements_ptr.size() > 0) {
		// Protection against non-touching elements
		if (elements_ptr[elements_ptr.size() - 1]->getPosOut() == element.getPosIn()) {
			elements_ptr.push_back(element.copy());
			elements_ptr[elements_ptr.size() - 2]->linkNext(*elements_ptr[elements_ptr.size() - 1]);
		} else {
			ERROR(EXCEPTIONS::ELEMENTS_NOT_TOUCHING);
		}
	} else {
		elements_ptr.push_back(element.copy());
	}
}

void Accelerator::addParticle(Particle const& particle) {
	// Protection against no element to point to
	if (elements_ptr.size() > 0) {
		particles_ptr.push_back(particle.copy());
		particles_ptr[particles_ptr.size() - 1]->setElement(elements_ptr[0].get());
	} else {
		ERROR(EXCEPTIONS::NO_ELEMENTS);
	}
}

void Accelerator::closeElementLoop() {
	// We need 2 elements
	if (elements_ptr.size() > 1) {
		if (elements_ptr[elements_ptr.size() - 1]->getPosOut() == elements_ptr[0]->getPosIn()) {
			elements_ptr[elements_ptr.size() - 1]->linkNext(*elements_ptr[0]);
		} else {
			ERROR(EXCEPTIONS::ELEMENT_LOOP_INCOMPLETE);
		}
	}
}

void Accelerator::clearParticles() { particles_ptr.clear(); }
void Accelerator::clearElements() { elements_ptr.clear(); }
void Accelerator::clear() {
	clearParticles();
	clearElements();
}

string Accelerator::to_string() const {
	stringstream stream;
	stream << setprecision(STYLES::PRECISION);
	stream << left;
	stream
		<< STYLES::COLOR_YELLOW
		<< STYLES::FORMAT_BOLD
		<< "Accelerator contains " << elements_ptr.size() << " element(s)"
		<< STYLES::NONE
		<< endl;
	for (shared_ptr<Element> const& element_ptr : elements_ptr) stream << *element_ptr << endl;
	stream
		<< STYLES::COLOR_YELLOW
		<< STYLES::FORMAT_BOLD
		<< "Accelerator contains " << particles_ptr.size() << " particle(s)" << endl
		<< STYLES::NONE;
	for (unique_ptr<Particle> const& particle_ptr : particles_ptr) stream << *particle_ptr << endl;
	return stream.str();
}

void Accelerator::clearDeadParticles() {
	// Remove particles that are out of the simulation
	size_t size(particles_ptr.size());
	for (size_t i(0); i < size; ++i) {
		if (particles_ptr[i]->getElementPtr()->isInWall(*particles_ptr[i])) {
			particles_ptr[i].reset();

			// using swap + pop_back
			// faster but changes indexes
			swap(particles_ptr[i], particles_ptr[size - 1]);
			particles_ptr.pop_back();

			// using erase
			// slower but preserves indexes
			// particles_ptr.erase(particles_ptr.begin() + i);

			// We resized the vector so we need to take it into account
			--size;
			// We need to evalute the new `particles_ptr[i]` that has been swapped
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
	if (engine_ptr == nullptr) ERROR(EXCEPTIONS::NULLPTR);
	engine_ptr->draw(*this);
}

void Accelerator::drawTo(Renderer * engine_ptr) const {
	if (engine_ptr == nullptr) ERROR(EXCEPTIONS::NULLPTR);
	engine_ptr->draw(*this);
}
