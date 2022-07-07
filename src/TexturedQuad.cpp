#include "include/TexturedQuad.h"

TexturedQuad::TexturedQuad() : Quad() {
    texture_coords_offset = vec2(1,15);
}


void TexturedQuad::initQuadTexture(){
	initQuad();
	texture_coordinates.push_back(vec2((0.0 + texture_coords_offset.x)/16, (0.0 + texture_coords_offset.y)/16));
	texture_coordinates.push_back(vec2((1.0 + texture_coords_offset.x)/16, (0.0 + texture_coords_offset.y)/16));
	texture_coordinates.push_back(vec2((1.0 + texture_coords_offset.x)/16, (1.0 + texture_coords_offset.y)/16));
	texture_coordinates.push_back(vec2((0.0 + texture_coords_offset.x)/16, (1.0 + texture_coords_offset.y)/16));
}