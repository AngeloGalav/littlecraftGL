#ifndef MESH_H
#define MESH_H
#include "Lib.h"
#include "definitions.h"

// todo: delete useless stuff


class Mesh {
public:
    vector<vec3> vertici;
	vector<vec4> colori;
	vector<GLuint> indici;
	vector<vec3> normali;
	vector<vec2> texture_coordinates;
	
	mat4 Model;
	int sceltaVS;
	int sceltaFS;
	GLuint VAO;
	GLuint VBO_G;
	GLuint VBO_C;
	GLuint VBO_normali;
	GLuint EBO_indici;
	GLuint VBO_texture;
	string nome;

    void buildMesh();
    virtual void drawMesh(int ModelUniform);
    void initVAO();
    void crea_VAO_Vector();
	void flushData();

	void crea_VAO_Vector_textures();

    Mesh();
};

#endif