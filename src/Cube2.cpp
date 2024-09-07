#include "include/Cube2.h"

NewCube::NewCube() {
    size = 3.0f;
    color = glm::vec4(1.0, 0.0, 0.0, 1.0);
    position = glm::vec3(11, -5, 0);
    texture_coords_offset = glm::vec2(1, 15);
}

NewCube::NewCube(glm::vec3 position) : position(position) {
    size = 3.0f;
    texture_coords_offset = glm::vec2(1, 15);
}

void NewCube::init() {
    float halfSize = size / 2.0f;

    std::vector<glm::vec3> positions = {
        // front face (pos z)
        glm::vec3(-halfSize, -halfSize, halfSize),
        glm::vec3(halfSize, -halfSize, halfSize),
        glm::vec3(halfSize, halfSize, halfSize),
        glm::vec3(-halfSize, halfSize, halfSize),
        // // back face (neg z)
        glm::vec3(-halfSize, -halfSize, -halfSize),
        glm::vec3(halfSize, -halfSize, -halfSize),
        glm::vec3(halfSize, halfSize, -halfSize),
        glm::vec3(-halfSize, halfSize, -halfSize)
    };

    std::vector<glm::vec4> colors = {
        glm::vec4(1.0, 0.0, 0.0, 1.0),
        glm::vec4(0.0, 0.0, 1.0, 1.0),
        glm::vec4(0.0, 0.0, 1.0, 1.0),
        glm::vec4(0.0, 0.0, 1.0, 1.0),
        // back face (neg z)
        glm::vec4(0.0, 1.0, 0.5, 1.0),
        glm::vec4(0.0, 0.0, 0.5, 1.0),
        glm::vec4(0.0, 0.5, 0.5, 1.0),
        glm::vec4(0.0, 1.0, 1.0, 1.0),
    };

    std::vector<glm::vec2> tex_coords = {
        glm::vec2((0.0 + texture_coords_offset.x) / TEX_ATLAS_UNIT_SIZE,
                (0.0 + texture_coords_offset.y) / TEX_ATLAS_UNIT_SIZE),
        glm::vec2((0.0 + texture_coords_offset.x) / TEX_ATLAS_UNIT_SIZE,
                (1.0 + texture_coords_offset.y) / TEX_ATLAS_UNIT_SIZE),
        glm::vec2((1.0 + texture_coords_offset.x) / TEX_ATLAS_UNIT_SIZE,
                (1.0 + texture_coords_offset.y) / TEX_ATLAS_UNIT_SIZE),
        glm::vec2((1.0 + texture_coords_offset.x) / TEX_ATLAS_UNIT_SIZE,
                (0.0 + texture_coords_offset.y) / TEX_ATLAS_UNIT_SIZE),
    };

        // vertex properties
    int i = 0;
    for (auto& pos : positions) {
        glm::vec3 worldPos = pos + position;
        // vertices.emplace_back(worldPos, glm::vec3(0, 0, 1), color,
        // glm::glm::vec2(0.0f, 0.0f));
        if (i >= (int)tex_coords.size() - 1) i = 0;
        vertices.emplace_back(worldPos, colors[i], tex_coords[i]);
        i++;
    }

    indices = {
      // front
      0, 1, 2,
      2, 3, 0,

      // Left
      0, 3, 7,
      7, 4, 0,

      // Top
      2, 6, 7,
      7, 3, 2,

      // Right
      1, 5, 6,
      6, 2, 1,

      // Back
      4, 7, 6,
      6, 5, 4,

      // Bottom
      5, 1, 0,
      0, 4, 5,
    };

    Model = glm::mat4(1.0);

    setup();
}

void NewCube::setup() {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    glEnableVertexAttribArray(0);

    // Color attribute
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));
    glEnableVertexAttribArray(1);

    // Text attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, tex_coord));
    glEnableVertexAttribArray(2);
}

// std::vector<Vertex> &NewCube::getVertexData() { return vertices; }

void NewCube::draw(int ModelUniform) {
    // glBindVertexArray(VAO);
    // glUniformMatrix4fv(ModelUniform, 1, GL_FALSE, value_ptr(Model));
    // glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    // glDrawArrays(GL_TRIANGLES, 0, 36);
    // glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    glBindVertexArray(VAO);
    glUniformMatrix4fv(ModelUniform, 1, GL_FALSE, value_ptr(Model));
    glDrawElements(GL_TRIANGLES, (indices.size() - 1) * sizeof(GLuint),
                   GL_UNSIGNED_INT, 0);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glBindVertexArray(0);
}

void NewCube::translate(glm::vec3 translate_vector) {
    Model =
        glm::translate(Model, ((float)UNIT_SIZE) * glm::vec3(translate_vector));
}

/** Moves the cube to a determined position
 *
 */
void NewCube::moveTo(glm::vec3 position) {
    translate(position - this->position);
    this->position = position;
}