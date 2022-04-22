#ifndef MESH_H
#define MESH_H
#include "Lib.h"

// todo: delete useless stuff


class Mesh {
public:
    vector<vec3> vertici;
	vector<vec4> colori;
	vector<GLuint> indici;
	vector<vec3> normali;
	vector<vec2> texCoords;
	mat4 Model;
	int sceltaVS;
	int sceltaFS;
	GLuint VAO;
	GLuint VBO_G;
	GLuint VBO_C;
	GLuint VBO_normali;
	GLuint EBO_indici;
	GLuint VBO_coord_texture;
	string nome;

    void buildMesh();
    void drawMesh();
    void initVAO();
    void crea_VAO_Vector();

    Mesh();
};

#endif