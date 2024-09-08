#include "include/Chunk2.h"

// TODO: ADD REFERENCE TO CHUNK POSITION, AND TRANSFORM THE CHUNK ACCORDINGLY!

NewChunk::NewChunk() {}

NewChunk::NewChunk(glm::vec3 position){}

void NewChunk::setup() {

    Model = glm::mat4(1.0);

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex),
                 vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint),
                 indices.data(), GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    glEnableVertexAttribArray(0);

    // Color attribute
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                          (void*)offsetof(Vertex, color));
    glEnableVertexAttribArray(1);

    // Text attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                          (void*)offsetof(Vertex, tex_coord));
    glEnableVertexAttribArray(2);
}

void NewChunk::build() {

        
    // Chunk generation placeholder
    for (int x = 0; x < CHUNK_SIZE; x++) {
        for (int y = 0; y < CHUNK_SIZE; y++) {
            for (int z = 0; z < CHUNK_SIZE; z++) {
                if (y < CHUNK_SIZE / 2)
                    chunk_map[x][y][z] = 1;
                else
                    chunk_map[x][y][z] = 0;
            }
        }
    }

    // Chunk generation placeholder
    for (int x = 0; x < CHUNK_SIZE; x++) {
        for (int y = 0; y < CHUNK_SIZE; y++) {
            for (int z = 0; z < CHUNK_SIZE; z++) {
                if (chunk_map[x][y][z] == 1) {
                    addCube(glm::vec3(x, y, z));
                }
            }
        }
    }

    std::cout << "Finished building" << std::endl;
    std::cout << "indices size is " << indices.size() << std::endl;
    std::cout << "vertex size is " << vertices.size() << std::endl;
}

void NewChunk::addCube(glm::vec3 position) {
    NewCube cube(position);
    cube.init();
    unsigned int indexOffset = (int) vertices.size();
    std::vector<Vertex>& cube_vertices = cube.getVertexData();
    vertices.insert(vertices.end(), cube_vertices.begin(), cube_vertices.end());
    //local indices
    std::vector<GLuint>& cube_indices = cube.getIndices();

    // modify indices of chunk
    indices.resize(indices.size() + 36);
    std::transform(std::begin(cube_indices), std::end(cube_indices),
                   indices.end() - 36,
                   [indexOffset](unsigned int i) { return i + indexOffset; });
}

void NewChunk::draw(int ModelUniform) {
    glBindVertexArray(VAO);
    glUniformMatrix4fv(ModelUniform, 1, GL_FALSE, value_ptr(Model));
    glDrawElements(GL_TRIANGLES, (indices.size() - 1) * sizeof(GLuint),
                   GL_UNSIGNED_INT, 0);
    // keep it glfront for debug
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    // glPolygonMode(GL_FRONT, GL_FILL);

    glBindVertexArray(0);
}

void NewChunk::translate(glm::vec3 translate_vector) {
    Model =
        glm::translate(Model, ((float)UNIT_SIZE) * glm::vec3(translate_vector));
}

void NewChunk::moveTo(glm::vec3 position) {
    translate(position - this->position);
    this->position = position;
}