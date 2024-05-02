#include "include/Mesh.h"

#include <iostream>

Mesh::Mesh() {}


// MOLTO IMPORTANTE DA TENERE A MENTE: CI SONO 2 VAO PER LE TEXTURES E SENZA LA
// TEXTURES
void Mesh::initVAO(bool hasTextures) {
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    // Genero , rendo attivo, riempio il VBO della geometria dei vertici
    glGenBuffers(1, &VBO_G);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_G);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vec3),
                 vertices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);
    glEnableVertexAttribArray(0);

    // Genero , rendo attivo, riempio il VBO dei colori
    glGenBuffers(1, &VBO_C);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_C);
    glBufferData(GL_ARRAY_BUFFER, colors.size() * sizeof(vec4), colors.data(),
                 GL_STATIC_DRAW);
    // Adesso carico il VBO dei colori nel layer 2
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (void *)0);
    glEnableVertexAttribArray(1);

    // Genero , rendo attivo, riempio il VBO delle texture
    if (hasTextures) {
        glGenBuffers(1, &VBO_texture);
        glBindBuffer(GL_ARRAY_BUFFER, VBO_texture);
        glBufferData(GL_ARRAY_BUFFER, texture_coordinates.size() * sizeof(vec2),
                     texture_coordinates.data(), GL_STATIC_DRAW);
        // Adesso carico il VBO dei colori nel layer 3
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, (void *)0);
        glEnableVertexAttribArray(2);
    }
    // EBO di tipo indici
    glGenBuffers(1, &EBO_indices);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_indices);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint),
                 indices.data(), GL_STATIC_DRAW);
}

void Mesh::drawMesh(int ModelUniform) {
    cout << "debug_ERROR: wrong call" << endl;
}

void Mesh::flushData() {
    indices.clear();
    texture_coordinates.clear();
    vertices.clear();
}