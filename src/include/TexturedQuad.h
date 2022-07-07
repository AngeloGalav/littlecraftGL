#ifndef TEXTURE_QUAD_H
#define TEXTURED_QUAD_H 

#include "Quad.h"

class TexturedQuad : public Quad {
    public:
    vec2 texture_coords_offset;  
    void initQuadTexture();

    TexturedQuad();
};

#endif