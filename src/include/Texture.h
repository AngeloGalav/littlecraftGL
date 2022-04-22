#ifndef TEXTURE_H
#define TEXTURE_H
#include <stb/stb_image.h> // libreria per il caricamento delle immagini 
#include "Lib.h"

class Texture {
public:
    // stuff here
    void textureSetup();
    void loadTextureImg();

    Texture();
};

#endif
