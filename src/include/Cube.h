// Classe del cubo 
#ifndef CUBE_H
#define CUBE_H

#include "Quad.h"

class Cube {
public:
    ivec3 position;
    Quad faces[6]; // facce del cubo

    bool must_be_drawn[6]; // ad ogni faccia è associato un bool, per dire se 
                           // lo devo disegnare o no, per ottimizzare drasticamente 
                           // il rendering 

    mat4 ModelCube; // Model Matrix dell'intero cubo
    ivec2 atlas_offset[3]; // texture offset, ogni cubo ha massimo 3 texture in Minecraft

    bool isAir;

    void initCube();
    void initTexturedCube();
    void initTextures();
    void moveTo(ivec3 position);
    void translateCube(ivec3 translate_vector);
    void drawMesh(int Model_Uniform);

    Cube(vec4 color);
    Cube();    
};

enum Direction {
    Front = 0,
    Right,
    Back, 
    Left,
    Up,
    Down
}; 

/** Le facce sono organizzate in questo modo:
 *  0 - front, 1 - right, 2 - back,
 *  3 - left, 4 - up, 5 - down
 */

#endif