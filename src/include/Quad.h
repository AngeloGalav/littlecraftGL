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
    void initQuadWithSingleColor();
public:
    vec4 quadColor;
    void createQuad();
    vec4 position;

    //initTexture???


    // costruttori del quad
    Quad(vec4 color);
    Quad();
};

#endif