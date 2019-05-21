#include "include/bundle/Accelerator.bundle.h"

using namespace std;

/****************************************************************
 * Constructor
 ****************************************************************/

Accelerator::Accelerator(Renderer * engine_ptr, bool methodChapi, bool beamFromParticle)
: Drawable(engine_ptr), methodChapi(methodChapi), beamFromParticle(beamFromParticle)
{}

/****************************************************************
 * Destructor
 ****************************************************************/

Accelerator::~Accelerator() { this->clear(); };

/****************************************************************
 * Getter
 ****************************************************************/

bool Accelerator::getBeamFromParticle() const { return beamFromParticle; }

/****************************************************************
 * Methods
 ****************************************************************/

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

void Accelerator::addBeam(Particle const& defaultParticle, size_t const& particleCount, double lambda) {
	// Protection against no element to point to
	if (elements_ptr.size() > 0) {
		beams_ptr.push_back(unique_ptr<Beam>(new Beam(defaultParticle, particleCount, lambda, *this, engine_ptr)));
		// Beam is automatically initialize

		associatedProgresses.push_back(vector<double>(1, 0));
		size_t i(associatedProgresses.size() - 1);
		size_t j(beams_ptr.size() - 1);
		beams_ptr[j]->updateProgresses(associatedProgresses[i], *this);
	} else {
		ERROR(EXCEPTIONS::NO_ELEMENTS);
	}
}

void Accelerator::addParticle(Particle particle) {
	// Protection against no element to point to
	if (elements_ptr.size() > 0) {
		// If there is only one particle, the beam is not automatically initialized !
		initParticleToClosestElement(particle);
		beams_ptr.push_back(unique_ptr<Beam>(new Beam(particle, engine_ptr)));

		associatedProgresses.push_back(vector<double>(1, 0));
		size_t i(associatedProgresses.size() - 1);
		size_t j(beams_ptr.size() - 1);
		beams_ptr[j]->updateProgresses(associatedProgresses[i], *this);
	} else {
		ERROR(EXCEPTIONS::NO_ELEMENTS);
	}
}

void Accelerator::initParticleToClosestElement(Particle & particle) const {
	bool found(false);
	size_t index(0);
	do {
		double const pos(elements_ptr[index]->getParticleProgress(particle.getPos(), methodChapi));
		bool const inWall(elements_ptr[index]->isInWall(particle));
		if ((pos >= 0 and pos <= 1) and (not inWall)) {
			found = true;
			particle.setElement(elements_ptr[index].get());
		}
		++index;
	} while ((not found) and index < elements_ptr.size());

	if (not found) {
		ERROR(EXCEPTIONS::PARTICLE_NOT_IN_ACCELERATOR);
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

void Accelerator::clearBeams() {
	beams_ptr.clear();
	associatedProgresses.clear();
}

void Accelerator::clearElements() { elements_ptr.clear(); }

void Accelerator::clear() {
	clearBeams();
	clearElements();
}

void Accelerator::clearDeadBeams() {
	// Remove beams that does not contain any particles from the simulation
	size_t size(beams_ptr.size());
	for (size_t i(0); i < size; ++i) {
		if (beams_ptr[i]->noParticle()) {
			beams_ptr[i].reset();

			// using swap + pop_back
			// faster but changes indexes
			swap(beams_ptr[i], beams_ptr[size - 1]);
			swap(associatedProgresses[i], associatedProgresses[size - 1]);
			beams_ptr.pop_back();
			associatedProgresses.pop_back();

			// using erase
			// slower but preserves indexes
			// beams_ptr.erase(beams_ptr.begin() + i);

			// We resized the vector so we need to take it into account
			--size;
			// We need to evalute the new `beams_ptr[i]` that has been swapped
			--i;
		}
	}
}

Vector3D Accelerator::getPosAtProgress(double progress) const {
	if (progress < 0 or progress > 1) { ERROR(EXCEPTIONS::BAD_PROGRESS); }

	double length(getTotalLength() * progress);
	size_t i(0);
	size_t size(elements_ptr.size());
	if (size == 0) { return Vector3D(); }

	do {
		length -= elements_ptr[i]->getLength();
		++i;
	} while (length >= 0 and i < size);
	--i;

	double lengthElement(elements_ptr[i]->getLength());
	length += lengthElement;

	double prog(length / lengthElement);
	return elements_ptr[i]->getPosAtProgress(prog);
}

Vector3D Accelerator::getVelAtProgress(double progress, bool clockwise) const {
	if (progress < 0 or progress > 1) { ERROR(EXCEPTIONS::BAD_PROGRESS); }

	double length(getTotalLength() * progress);
	size_t i(0);
	size_t size(elements_ptr.size());
	if (size == 0) { return Vector3D(); }

	do {
		length -= elements_ptr[i]->getLength();
		++i;
	} while(length >= 0 and i < size);
	--i;

	double lengthElement(elements_ptr[i]->getLength());
	length += lengthElement;

	double prog(length / lengthElement);
	return elements_ptr[i]->getVelAtProgress(prog, clockwise);
}

double Accelerator::getTotalLength() const {
	double length(0);
	for (shared_ptr<Element> const& element_ptr : elements_ptr) {
		length += element_ptr->getLength();
	}
	return length;
}

double Accelerator::getParticleProgress(Vector3D const& pos) const {
	if (elements_ptr.empty()) { ERROR(EXCEPTIONS::NO_ELEMENTS); }

	double x1(pos.getX());
	double y1(pos.getY());
	double x2(elements_ptr[0]->getPosIn().getX());
	double y2(elements_ptr[0]->getPosIn().getY());
	double angle(atan2(x1*y2 - y1*x2, x1*x2 + y1*y2));

	if (angle < 0) { angle += 2 * M_PI; }
	return angle / (2 * M_PI);
}

void Accelerator::exertInteraction(size_t beam1, size_t part1, size_t beam2, size_t part2) {
	Vector3D force(beams_ptr[beam2]->getPos(part2) - beams_ptr[beam1]->getPos(part1));
	double r(force.norm());

	if (r < GLOBALS::EPSILON) {
		// cout << "Collision !" << endl;
		return;
	}

	double charge1(beams_ptr[beam1]->getCharge());
	double charge2(beams_ptr[beam2]->getCharge());

	double cst(charge1 * charge2 / (4 * M_PI * CONSTANTS::EPISLON0));

	// Mean of the 2 gammas
	double gamma1(beams_ptr[beam1]->getGamma(part1));
	double gamma2(beams_ptr[beam2]->getGamma(part2));

	double gamma((gamma2 + gamma1) / 2);

	force *= cst / (r * r * r * gamma * gamma);
	beams_ptr[beam2]->exertForce(force, part2);
	beams_ptr[beam1]->exertForce(-force, part1);
}

void Accelerator::step(double dt) {
	// Do nothing if dt is null
	if (abs(dt) < GLOBALS::DELTA_DIV0) { return; }

	double i(0);
	for (unique_ptr<Beam> & beam_ptr : beams_ptr) {
		// Change the element if the particle goes out
		beam_ptr->updatePointedElement(methodChapi);

		beam_ptr->updateProgresses(associatedProgresses[i], *this);
		++i;
	}

	// The progresses are normaly initialized so we can use them here
	// 		to add interaction
	size_t nbrBeam(associatedProgresses.size());

	for (size_t beam1(0); beam1 < nbrBeam; ++beam1) {
		size_t nbrPart1(associatedProgresses[beam1].size());

		for (size_t part1(0); part1 < nbrPart1; ++part1) {

			for (size_t beam2(0); beam2 < nbrBeam; ++beam2) {
				if (beam1 <= beam2) {
					size_t nbrPart2(associatedProgresses[beam2].size());

					for (size_t part2(0); part2 < nbrPart2; ++part2) 	{
						// no interaction if the particle is the same
						if (part1 <= part2) {
							// cout << beam1 << "    " << part1 << "    " << beam2 << "    " << part2	 << endl;
							if (not((beam1 == beam2) and (part1 == part2))) {
								if (abs(associatedProgresses[beam1][part1] - associatedProgresses[	beam2][part2]) < GLOBALS::DELTA_INTERACTION) {
									// cout << "Interaction" << endl;
									exertInteraction(beam1, part1, beam2, part2);
								}
							}
						}
					}
				}
			}
		}
	}

	// Step through all the particles
	for (unique_ptr<Beam> & beam_ptr : beams_ptr) {
		beam_ptr->step(dt, methodChapi);
	}

	clearDeadBeams();
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
		<< "Accelerator contains " << beams_ptr.size() << " beam(s)" << endl
		<< STYLES::NONE;
	for (unique_ptr<Beam> const& beam_ptr : beams_ptr) stream << *beam_ptr;
		stream << endl;
	return stream.str();
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

void Accelerator::draw(Renderer * engine_ptr) const {
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

void Accelerator::drawBeams() const {
	if (engine_ptr == nullptr) ERROR(EXCEPTIONS::NULLPTR);
	for (unique_ptr<Beam> const& beam_ptr : beams_ptr) {
		beam_ptr->draw(engine_ptr);
	}
}

void Accelerator::drawElements() const {
	if (engine_ptr == nullptr) ERROR(EXCEPTIONS::NULLPTR);
	for (shared_ptr<Element> const& element_ptr : elements_ptr) {
		element_ptr->draw(engine_ptr);
	}
}
