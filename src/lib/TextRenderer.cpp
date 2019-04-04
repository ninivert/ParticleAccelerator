#include "src/include/bundle/TextRenderer.bundle.h"

using namespace std;

/****************************************************************
 * Constructors and destructors
 ****************************************************************/

TextRenderer::TextRenderer(ostream * stream_ptr)
: stream_ptr(stream_ptr)
{}

TextRenderer::TextRenderer(string const& fileName) {
	fileStream = ofstream(fileName);
	if (fileStream.fail()) ERROR(EXCEPTIONS::FILE_EXCEPTION);
	stream_ptr = &fileStream;
}

TextRenderer::~TextRenderer() {
	fileStream.close();
}

/****************************************************************
 * Drawing
 ****************************************************************/

/**
 * Draw an entire Accelerator
 */

void TextRenderer::draw(Accelerator const& acc) {
	*stream_ptr << acc;
}

/**
 * Draw a Dipole element
 */

void TextRenderer::draw(Dipole const& dipole) {
	*stream_ptr << dipole;
}

/**
 * Draw a Quadrupole element
 */

void TextRenderer::draw(Quadrupole const& quadrupole) {
	*stream_ptr << quadrupole;
}

/**
 * Draw a Straight element
 */

void TextRenderer::draw(Straight const& straight) {
	*stream_ptr << straight;
}

/**
 * Draw a Particle
 */

void TextRenderer::draw(Particle const& particle) {
	*stream_ptr << particle;
}

/**
 * Draw a Vector3D (debugging purposes)
 */

void TextRenderer::draw(Vector3D const& vec) {
	*stream_ptr << vec;
}

// that's all folks !
