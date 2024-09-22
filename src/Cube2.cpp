#include "include/Cube2.h"

NewCube::NewCube() {
    size = 1.0f;
    color = glm::vec4(1.0, 0.0, 0.0, 1.0);
    position = glm::vec3(11, -5, 0);
    texture_coords_offset = glm::vec2(1, 15);
}

NewCube::NewCube(glm::vec3 position) : position(position) {
    size = 1.0f;
    texture_coords_offset = glm::vec2(3, 15);
    texture_coords_offset_top = glm::vec2(0, 15);
    texture_coords_offset_bot = glm::vec2(2, 15);
}

void NewCube::init() {
    float halfSize = size / 2.0f;

    // need 24 vertices instead of just 8 for texturing purposes...
    std::vector<glm::vec3> positions = {
        // Front
        glm::vec3(-halfSize, -halfSize, halfSize),  // 0
        glm::vec3(halfSize, -halfSize, halfSize),   // 1
        glm::vec3(halfSize, halfSize, halfSize),    // 2
        glm::vec3(-halfSize, halfSize, halfSize),   // 3
        // Back face
        glm::vec3(-halfSize, -halfSize, -halfSize), // 4
        glm::vec3(halfSize, -halfSize, -halfSize),  // 5
        glm::vec3(halfSize, halfSize, -halfSize),   // 6
        glm::vec3(-halfSize, halfSize, -halfSize),  // 7
        // Top face
        glm::vec3(-halfSize, halfSize, halfSize),   // 8  (3)
        glm::vec3(halfSize, halfSize, halfSize),    // 9  (2)
        glm::vec3(halfSize, halfSize, -halfSize),   // 10 (6)
        glm::vec3(-halfSize, halfSize, -halfSize),  // 11 (7)
        // Bottom face
        glm::vec3(-halfSize, -halfSize, halfSize),  // 12 (0)
        glm::vec3(halfSize, -halfSize, halfSize),   // 13 (1)
        glm::vec3(halfSize, -halfSize, -halfSize),  // 14 (5)
        glm::vec3(-halfSize, -halfSize, -halfSize), // 15 (4)
        // Left face
        glm::vec3(-halfSize, -halfSize, halfSize),  // 16 (0)
        glm::vec3(-halfSize, -halfSize, -halfSize), // 17 (4)
        glm::vec3(-halfSize, halfSize, -halfSize),  // 18 (7)
        glm::vec3(-halfSize, halfSize, halfSize),   // 19 (3)
        // Right face
        glm::vec3(halfSize, -halfSize, halfSize),   // 20 (1)
        glm::vec3(halfSize, -halfSize, -halfSize),  // 21 (5)
        glm::vec3(halfSize, halfSize, -halfSize),   // 22 (6)
        glm::vec3(halfSize, halfSize, halfSize)     // 23 (2)
    };

    std::vector<glm::vec4> colors = {
        glm::vec4(1.0, 0.0, 0.0, 1.0),
        glm::vec4(0.0, 1.0, 1.0, 1.0),
        glm::vec4(0.0, 0.0, 1.0, 1.0),
        glm::vec4(1.0, 0.0, 1.0, 1.0),
    };

    std::vector<glm::vec2> tex_coords = {
        glm::vec2((1.0 + texture_coords_offset.x) / TEX_ATLAS_UNIT_SIZE,
                (0.0 + texture_coords_offset.y) / TEX_ATLAS_UNIT_SIZE),
        glm::vec2((0.0 + texture_coords_offset.x) / TEX_ATLAS_UNIT_SIZE,
                (0.0 + texture_coords_offset.y) / TEX_ATLAS_UNIT_SIZE),
        glm::vec2((0.0 + texture_coords_offset.x) / TEX_ATLAS_UNIT_SIZE,
                (1.0 + texture_coords_offset.y) / TEX_ATLAS_UNIT_SIZE),
        glm::vec2((1.0 + texture_coords_offset.x) / TEX_ATLAS_UNIT_SIZE,
                (1.0 + texture_coords_offset.y) / TEX_ATLAS_UNIT_SIZE),
    };

    std::vector<glm::vec2> tex_coords_top = {
        glm::vec2((0.0 +  texture_coords_offset_top.x) / TEX_ATLAS_UNIT_SIZE,
                (0.0 +  texture_coords_offset_top.y) / TEX_ATLAS_UNIT_SIZE),
        glm::vec2((0.0 +  texture_coords_offset_top.x) / TEX_ATLAS_UNIT_SIZE,
                (1.0 +  texture_coords_offset_top.y) / TEX_ATLAS_UNIT_SIZE),
        glm::vec2((1.0 +  texture_coords_offset_top.x) / TEX_ATLAS_UNIT_SIZE,
                (1.0 +  texture_coords_offset_top.y) / TEX_ATLAS_UNIT_SIZE),
        glm::vec2((1.0 +  texture_coords_offset_top.x) / TEX_ATLAS_UNIT_SIZE,
                (0.0 +  texture_coords_offset_top.y) / TEX_ATLAS_UNIT_SIZE),
    };

    std::vector<glm::vec2> tex_coords_bot = {
        glm::vec2((0.0 +  texture_coords_offset_bot.x) / TEX_ATLAS_UNIT_SIZE,
                (0.0 +  texture_coords_offset_bot.y) / TEX_ATLAS_UNIT_SIZE),
        glm::vec2((0.0 +  texture_coords_offset_bot.x) / TEX_ATLAS_UNIT_SIZE,
                (1.0 +  texture_coords_offset_bot.y) / TEX_ATLAS_UNIT_SIZE),
        glm::vec2((1.0 +  texture_coords_offset_bot.x) / TEX_ATLAS_UNIT_SIZE,
                (1.0 +  texture_coords_offset_bot.y) / TEX_ATLAS_UNIT_SIZE),
        glm::vec2((1.0 +  texture_coords_offset_bot.x) / TEX_ATLAS_UNIT_SIZE,
                (0.0 +  texture_coords_offset_bot.y) / TEX_ATLAS_UNIT_SIZE),
    };

    // vertex properties
    int i = 0, j = 0;
    for (auto& pos : positions) {
        glm::vec3 worldPos = pos + position;
        // hacky way for top & bot
        if (7 < j  && j < 12) vertices.emplace_back(worldPos, colors[i], tex_coords_top[i]);
        else if (11 < j && j < 16) vertices.emplace_back(worldPos, colors[i], tex_coords_bot[i]);
        else vertices.emplace_back(worldPos, colors[i], tex_coords[i]);
        i++;
        j++;
        if ((int)tex_coords.size() <= i) i = 0;
    }

    indices = {
        // Top face
        8, 9, 10, 8, 10, 11,
        // Bottom face
        12, 14, 13, 12, 15, 14,
        // Front face
        0, 1, 2, 0, 2, 3,
        // Back face
        4, 6, 5, 4, 7, 6,
        // Left face
        16, 18, 17, 16, 19, 18,
        // Right face
        20, 21, 22, 20, 22, 23
    };

    Model = glm::mat4(1.0);
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

void NewCube::draw(int ModelUniform) {
    glBindVertexArray(VAO);
    glUniformMatrix4fv(ModelUniform, 1, GL_FALSE, value_ptr(Model));
    glDrawElements(GL_TRIANGLES, (indices.size() - 1) * sizeof(GLuint),
                   GL_UNSIGNED_INT, 0);
    // keep it glfront for debug
    // glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glPolygonMode(GL_FRONT, GL_FILL);

    glBindVertexArray(0);
}

void NewCube::translate(glm::vec3 translate_vector) {
    Model =
        glm::translate(Model, ((float)UNIT_SIZE) * glm::vec3(translate_vector));
}

std::vector<GLuint>& NewCube::getIndices() {
    return indices;
}


std::vector<Vertex>& NewCube::getVertexData() {
    return vertices;
}
/** Moves the cube to a determined position
 *
 */
void NewCube::moveTo(glm::vec3 position) {
    translate(position - this->position);
    this->position = position;
}