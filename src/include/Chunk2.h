#ifndef CHUNK_2_H
#define CHUNK_2_H

#include "Cube2.h"
#include "Lib.h"
// #include "World.h"

class NewChunk {
   private:
   public:
    GLuint VBO, EBO, VAO;
    glm::vec3 position;
    std::vector<Vertex> vertices;
    std::vector<GLuint> indices;
    glm::vec4 color;
    glm::mat4 Model;
    int chunk_map[CHUNK_SIZE][CHUNK_SIZE][CHUNK_SIZE];
    void draw(int MatModel);
    void build();
    void setup();
    void addCube(glm::vec3 position);

    void translate(glm::vec3 translate_vector);
    void moveTo(glm::vec3 position);

    NewChunk();
    NewChunk(glm::vec3 position);
};

#endif