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
    vec4 quadColor;
        
    void createQuad();
    void drawMesh(int ModelUniform);
    void drawMeshFromParent(int ModelUniform, mat4 parentModel);
    void translateQuad(vec3 translate_vector);

    // texture on the quad
    vec2 texture_coords_offset;  
    bool hasTexture;
    void initQuadTexture();
    
    // costruttori del quad
    Quad(vec4 color);
    Quad();
};

#endif