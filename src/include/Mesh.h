#ifndef MESH_H
#define MESH_H
#include "Lib.h"
#include "definitions.h"

class Mesh {
   public:
    vector<vec3> vertices;
    vector<vec4> colors;
    vector<GLuint> indices;
    vector<vec2> texture_coordinates;

    mat4 Model;
    GLuint VAO;
    GLuint VBO_G;  // geometry vbo
    GLuint VBO_C;  // colors vbo
    GLuint EBO_indices;
    GLuint VBO_texture;  // texture vbo

    void buildMesh();
    virtual void drawMesh(int ModelUniform);
    void initVAO(bool hasTextures);
    void flushData();

    Mesh();
};

#endif