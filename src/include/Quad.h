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
public:
    vec4 quadColor;
    void initQuad();
    void createQuad();

    // costruttori del quad
    Quad(vec4 color);
    Quad();
};

#endif