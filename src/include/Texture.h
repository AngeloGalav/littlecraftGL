#ifndef TEXTURE_H
#define TEXTURE_H
#include "Lib.h"

class Texture {
public:
    // stuff here
    char** pixels;
    GLuint texture_id;
    int texture_width, texture_height, nrChannels;

    void initTexture();
    void loadTextureImg();

    void bindTexture();
    void destroyTexture();


    Texture();
};

#endif
