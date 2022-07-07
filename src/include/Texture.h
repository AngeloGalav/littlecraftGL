#ifndef TEXTURE_H
#define TEXTURE_H
#include "Lib.h"

class Texture {
public:
    // stuff here
    char** pixels;
    GLuint texture_id;

    void textureSetup();
    void loadTextureImg();

    void bindTexture();
    void destroyTexture();


    Texture();
};

#endif
