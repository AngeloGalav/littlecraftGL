#include "include/TexturedQuad.h"

void TexturedQuad::initQuadTexture(){
	initQuad();

	texture_coordinates.push_back(vec2(0.0f, 0.0f));
	texture_coordinates.push_back(vec2(1.0f/16, 0.0f));
	texture_coordinates.push_back(vec2(1.0f/16, 1.0f/16));
	texture_coordinates.push_back(vec2(0.0f, 1.0f/16));

}