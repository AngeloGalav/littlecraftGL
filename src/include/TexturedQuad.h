#pragma once 
#include "Quad.h"

class TexturedQuad : public Quad {
    public:
    vec2 texture_coords_offset;  
    void initQuadTexture();

    TexturedQuad();
};

