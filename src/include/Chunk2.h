#ifndef CHUNK_2_H
#define CHUNK_2_H

#include "Cube2.h"
#include "Lib.h"
#include "FastNoiseLite.h"
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
    void build(bool dbg);
    void setup();
    void addCube(glm::vec3 position);
    // todo: finalize this so it replaces addcube
    void addFace(glm::vec3 position, glm::ivec3 direction);

    void translate(glm::vec3 translate_vector);
    void moveTo(glm::vec3 position);

    // DEBUG: remove when implementing new world class
    void quickNoisedChunk();
    FastNoiseLite noise;
    int noiseData[CHUNK_SIZE][CHUNK_SIZE];

    NewChunk();
    NewChunk(glm::vec3 position);
};

#endif