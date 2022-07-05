// TODO: Inserire la creazione del VAO Vector dentro a initQuad. 

#include "include/Quad.h"
#include <iostream>

Quad::Quad(vec4 color) {
    this->quadColor = color;
	initQuadWithSingleColor();
	angle = 0;
}

Quad::Quad() {
	angle = 0;
}

void Quad::initQuad(){
    
	vertici.push_back(vec3(-1.0, -1.0, 0.0));
	colori.push_back(vec4(1.0, 0.0, 0.0, 1.0));
	vertici.push_back(vec3(1.0, -1.0, 0.0));
	colori.push_back(vec4(0.0, 1.0, 0.0, 1.0));
	vertici.push_back(vec3(1.0, 1.0, 0.0));
	colori.push_back(vec4(0.0, 0.0, 1.0, 1.0));
	vertici.push_back(vec3(-1.0, 1.0, 0.0));
	colori.push_back(vec4(1.0, 0.0, 1.0, 1.0));

	// aggiunge gli indici 
	indici.push_back(0); indici.push_back(1); indici.push_back(2);
	indici.push_back(2); indici.push_back(3); indici.push_back(0);
}

/** Crea un quad di un particolare colore. 
 * 
 */
void Quad::initQuadWithSingleColor(){
	vertici.push_back(vec3(-1.0, -1.0, 0.0));
	colori.push_back(quadColor);
	vertici.push_back(vec3(1.0, -1.0, 0.0));
	colori.push_back(quadColor);
	vertici.push_back(vec3(1.0, 1.0, 0.0));
	colori.push_back(quadColor);
	vertici.push_back(vec3(-1.0, 1.0, 0.0));
	colori.push_back(quadColor);

	indici.push_back(0); indici.push_back(1); indici.push_back(2);
	indici.push_back(2); indici.push_back(3); indici.push_back(0);
}


void Quad::drawMesh(int ModelUniform) {
	glUniformMatrix4fv(ModelUniform, 1, GL_FALSE, value_ptr(Model));
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, (indici.size() - 1) * sizeof(GLuint), GL_UNSIGNED_INT, 0);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glBindVertexArray(0);
}

void Quad::rotate_debug(){
	if (angle > 179) angle = -179;
	angle += 1.0f;
	Model = rotate(Model, radians(angle), vec3(0, 1, 0));
}
