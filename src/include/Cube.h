// Classe del cubo 
#ifndef CUBE_H
#define CUBE_H

#include "Quad.h"

class Cube {
public:
    vec3 position;
    Quad faces[6]; // facce del cubo 

    void initCube();

    Cube(vec4 pos);
    Cube();    
};

#endif