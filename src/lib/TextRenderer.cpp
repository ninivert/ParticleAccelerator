#include "src/include/bundle/TextRenderer.bundle.h"

/****************************************************************
 * Constructors and destructors
 ****************************************************************/

TextRenderer::TextRenderer() {}
TextRenderer::~TextRenderer() {}

/****************************************************************
 * Drawing
 ****************************************************************/

/**
 * Draw an entire Accelerator
 */

void TextRenderer::draw(Accelerator const& acc) {

}

/**
 * Draw an element. This method is not overridden in Element.cpp
 * thus the Element remains abstract.
 */

void TextRenderer::draw(Element const& elmt) {

}

/**
 * Draw a Dipole element
 */

void TextRenderer::draw(Dipole const& dipole) {

}

/**
 * Draw a Quadrupole element
 */

void TextRenderer::draw(Quadrupole const& quadrupole) {

}

/**
 * Draw a Straight element
 */

void TextRenderer::draw(Straight const& straight) {

}

/**
 * Draw a Particle
 */

void TextRenderer::draw(Particle const& particle) {

}

/**
 * Draw a Vector3D (debugging purposes)
 */

void TextRenderer::draw(Vector3D const& vec) {

}

// that's all folks !
