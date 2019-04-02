#include "src/include/bundle/TextRenderer.bundle.h"

using namespace std;

/****************************************************************
 * Constructors and destructors
 ****************************************************************/

TextRenderer::TextRenderer(ostream * streamPtr) : streamPtr(streamPtr) {}

TextRenderer::~TextRenderer() {}

/****************************************************************
 * Drawing
 ****************************************************************/

void TextRenderer::draw(Accelerator const& acc) {
	*streamPtr << acc;
}

void TextRenderer::draw(Dipole const& dipole) {
	*streamPtr << dipole;
}

void TextRenderer::draw(Quadrupole const& quadrupole) {
	*streamPtr << quadrupole;
}

void TextRenderer::draw(Straight const& straight) {
	*streamPtr << straight;
}

void TextRenderer::draw(Frodo const& frodo) {
	*streamPtr << frodo;
}

void TextRenderer::draw(Particle const& particle) {
	*streamPtr << particle;
}

void TextRenderer::draw(Vector3D const& vec) {
	*streamPtr << vec;
}

// that's all folks !
