#ifndef TEXTURE_H
#define TEXTURE_H
#include "Lib.h"

class Texture {
public:
    int texture_width, texture_height, nrChannels;
    unsigned int texture;
    void initTexture(unsigned int *texture_programId);
    void useTexture();

    Texture();
};

#endif
