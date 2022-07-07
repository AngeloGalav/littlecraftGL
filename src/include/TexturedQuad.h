#ifndef TEXTURE_QUAD_H
#define TEXTURED_QUAD_H 

#include "Quad.h"

class TexturedQuad : public Quad {
    public:
    ivec2 texture_coords_offeset;  
    void initQuadTexture();
};

#endif