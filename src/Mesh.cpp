#include "include/Mesh.h"
#include <iostream>

Mesh::Mesh(){}


/** TODO: questa funzione deve chaiamatrsi initVAO, com'è giusto che sia 
 */
void Mesh::crea_VAO_Vector()
{
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	// Genero , rendo attivo, riempio il VBO della geometria dei vertici
	glGenBuffers(1, &VBO_G);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_G);
	glBufferData(GL_ARRAY_BUFFER, vertici.size() * sizeof(vec3), vertici.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);
	glEnableVertexAttribArray(0);

	// Genero , rendo attivo, riempio il VBO dei colori
	glGenBuffers(1, &VBO_C);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_C);
	glBufferData(GL_ARRAY_BUFFER, colori.size() * sizeof(vec4), colori.data(), GL_STATIC_DRAW);
	// Adesso carico il VBO dei colori nel layer 2
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (void *)0);
	glEnableVertexAttribArray(1);

	// EBO di tipo indici
	glGenBuffers(1, & EBO_indici);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_indici);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indici.size() * sizeof(GLuint), indici.data(), GL_STATIC_DRAW);
}

void Mesh::crea_VAO_Vector_textures(){
	
}


void Mesh::drawMesh(int ModelUniform){ cout << "debug: wrong call" << endl;}