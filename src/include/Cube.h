// Classe del cubo 
#ifndef CUBE_H
#define CUBE_H

#include "Quad.h"


/** Derivare da Mesh è molto brutta come cosa, ma che ci vuoi fare. 
 *  
 */
class Cube {
public:
    vec3 position;
    Quad faces[6]; // facce del cubo 
    mat4 ModelCube;


    void initCube();
    void moveTo(vec3 position);
    void translateCube(vec3 translate_vector);
    void drawMesh(int Model_Uniform);

    Cube(vec4 pos);
    Cube();    
};

/** Le facce sono organizzate in questo modo:
 *  0 - front, 1 - right, 2 - back,
 *  3 - left, 4 - up, 5 - down
 */

#endif