/** Classe per le primitive per il motore a voxel.
 *  In questo modo, è possibile decidere quale faccia deve essere disegnata
 *  e quale no...
 */


// primitiva per la creazione del voxel engine
#ifndef QUAD_H
#define QUAD_H


// todo: inserire codice delle texture qui prima o poi 
#include "Mesh.h"

class Quad : public Mesh {
protected:
    void initQuad();
public:
    void initQuadWithSingleColor();
    vec4 position;
    vec4 quadColor;
    float angle;
    
    void createQuad();
    void drawMesh(int ModelUniform);
    void drawMeshDebug(int ModelUniform, mat4 ok);
    void translateQuad(vec3 translate_vector);

    //initTexture???
    
    // costruttori del quad
    Quad(vec4 color);
    Quad();


    //DEBUG
    void rotate_debug();
};

#endif