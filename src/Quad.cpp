// TODO: Inserire la creazione del VAO Vector dentro a initQuad. 

#include "include/Quad.h"
#include <iostream>

extern GLuint render_mode; 


Quad::Quad(vec4 color) {
    this->quadColor = color;
	initQuadWithSingleColor();
	hasTexture = false;
}

Quad::Quad() {
    texture_coords_offset = vec2(1,15);
	hasTexture = false;
}

void Quad::initQuad(){
    
	vertices.push_back(vec3(-1.0, -1.0, 0.0));
	colors.push_back(vec4(1.0, 0.0, 0.0, 1.0));
	vertices.push_back(vec3(1.0, -1.0, 0.0));
	colors.push_back(vec4(0.0, 1.0, 0.0, 1.0));
	vertices.push_back(vec3(1.0, 1.0, 0.0));
	colors.push_back(vec4(0.0, 0.0, 1.0, 1.0));
	vertices.push_back(vec3(-1.0, 1.0, 0.0));
	colors.push_back(vec4(1.0, 0.0, 1.0, 1.0));

	// aggiunge gli indici 
	indices.push_back(0); indices.push_back(1); indices.push_back(2);
	indices.push_back(2); indices.push_back(3); indices.push_back(0);
}

/** Crea un quad di un particolare colore. 
 * 
 */
void Quad::initQuadWithSingleColor(){
	vertices.push_back(vec3(-1.0, -1.0, 0.0));
	colors.push_back(quadColor);
	vertices.push_back(vec3(1.0, -1.0, 0.0));
	colors.push_back(quadColor);
	vertices.push_back(vec3(1.0, 1.0, 0.0));
	colors.push_back(quadColor);
	vertices.push_back(vec3(-1.0, 1.0, 0.0));
	colors.push_back(quadColor);

	indices.push_back(0); indices.push_back(1); indices.push_back(2);
	indices.push_back(2); indices.push_back(3); indices.push_back(0);
}

void Quad::drawMesh(int ModelUniform) {
	glBindVertexArray(VAO);
	glUniformMatrix4fv(ModelUniform, 1, GL_FALSE, value_ptr(Model));
	glDrawElements(GL_TRIANGLES, (indices.size() - 1) * sizeof(GLuint), GL_UNSIGNED_INT, 0);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glBindVertexArray(0);
}

void Quad::drawMeshFromParent(int ModelUniform, mat4 parentModel) {
	glBindVertexArray(VAO);
	glUniformMatrix4fv(ModelUniform, 1, GL_FALSE, value_ptr(parentModel*Model));
	glDrawElements(GL_TRIANGLES, (indices.size() - 1) * sizeof(GLuint), GL_UNSIGNED_INT, 0);
	glPolygonMode(GL_FRONT_AND_BACK, render_mode);
	glBindVertexArray(0);
}

void Quad::translateQuad(vec3 translate_vector){
	Model = translate(Model, ((float)UNIT_SIZE)*translate_vector);
}

void Quad::initQuadTexture(){
	initQuad();
	texture_coordinates.clear();
	texture_coordinates.push_back(vec2((0.0 + texture_coords_offset.x)/TEX_ATLAS_UNIT_SIZE, (0.0 + texture_coords_offset.y)/TEX_ATLAS_UNIT_SIZE));
	texture_coordinates.push_back(vec2((1.0 + texture_coords_offset.x)/TEX_ATLAS_UNIT_SIZE, (0.0 + texture_coords_offset.y)/TEX_ATLAS_UNIT_SIZE));
	texture_coordinates.push_back(vec2((1.0 + texture_coords_offset.x)/TEX_ATLAS_UNIT_SIZE, (1.0 + texture_coords_offset.y)/TEX_ATLAS_UNIT_SIZE));
	texture_coordinates.push_back(vec2((0.0 + texture_coords_offset.x)/TEX_ATLAS_UNIT_SIZE, (1.0 + texture_coords_offset.y)/TEX_ATLAS_UNIT_SIZE));
}

