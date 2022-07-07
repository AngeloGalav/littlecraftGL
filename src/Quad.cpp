// TODO: Inserire la creazione del VAO Vector dentro a initQuad. 

#include "include/Quad.h"
#include <iostream>

Quad::Quad(vec4 color) {
    this->quadColor = color;
	initQuadWithSingleColor();
	hasTexture = false;
	angle = 0;
}

Quad::Quad() {
    texture_coords_offset = vec2(1,15);
	hasTexture = false;
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
	glBindVertexArray(VAO);
	glUniformMatrix4fv(ModelUniform, 1, GL_FALSE, value_ptr(Model));
	glDrawElements(GL_TRIANGLES, (indici.size() - 1) * sizeof(GLuint), GL_UNSIGNED_INT, 0);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glBindVertexArray(0);
}

void Quad::drawMeshFromParent(int ModelUniform, mat4 parentModel) {
	glBindVertexArray(VAO);
	glUniformMatrix4fv(ModelUniform, 1, GL_FALSE, value_ptr(parentModel*Model));
	glDrawElements(GL_TRIANGLES, (indici.size() - 1) * sizeof(GLuint), GL_UNSIGNED_INT, 0);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glBindVertexArray(0);
}

void Quad::rotate_debug(){
	if (angle > 179) angle = -179;
	angle += 1.0f;
	Model = rotate(Model, radians(angle), vec3(0, 1, 0));
}

void Quad::translateQuad(vec3 translate_vector){
	Model = translate(Model, translate_vector);
}


void Quad::initQuadTexture(){
	initQuad();
	hasTexture = false;
	texture_coordinates.push_back(vec2((0.0 + texture_coords_offset.x)/16, (0.0 + texture_coords_offset.y)/16));
	texture_coordinates.push_back(vec2((1.0 + texture_coords_offset.x)/16, (0.0 + texture_coords_offset.y)/16));
	texture_coordinates.push_back(vec2((1.0 + texture_coords_offset.x)/16, (1.0 + texture_coords_offset.y)/16));
	texture_coordinates.push_back(vec2((0.0 + texture_coords_offset.x)/16, (1.0 + texture_coords_offset.y)/16));
}

