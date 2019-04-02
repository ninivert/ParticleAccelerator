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

/**
 * Draw an entire Accelerator
 */

void TextRenderer::draw(Accelerator const& acc) {
	*streamPtr << acc;
}

/**
 * Draw a Dipole element
 */

void TextRenderer::draw(Dipole const& dipole) {
	*streamPtr << dipole;
}

/**
 * Draw a Quadrupole element
 */

void TextRenderer::draw(Quadrupole const& quadrupole) {
	*streamPtr << quadrupole;
}

/**
 * Draw a Straight element
 */

void TextRenderer::draw(Straight const& straight) {
	*streamPtr << straight;
}

/**
 * Draw a Particle
 */

void TextRenderer::draw(Particle const& particle) {
	*streamPtr << particle;
}

/**
 * Draw a Vector3D (debugging purposes)
 */

void TextRenderer::draw(Vector3D const& vec) {
	*streamPtr << vec;
}

// that's all folks !
