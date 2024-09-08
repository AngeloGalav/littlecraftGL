// Classe del cubo
#ifndef CUBE_2_H
#define CUBE_2_H

#include "Lib.h"
#include "definitions.h"

struct Vertex {
    glm::vec3 position;
    // glm::vec3 normal;
    glm::vec4 color;
    glm::vec2 tex_coord;

    Vertex(const glm::vec3& pos, const glm::vec4& col, const glm::vec2& tex)
        : position(pos), color(col), tex_coord(tex) {}
};

class NewCube {
public:
    GLuint VBO, EBO, VAO;
    glm::vec3 position;
    std::vector<Vertex> vertices;
    std::vector<GLuint> indices;
    glm::vec4 color;
    glm::vec2 texture_coords_offset_top;
    glm::vec2 texture_coords_offset_bot;
    glm::vec2 texture_coords_offset;
    glm::mat4 Model;

    float size;

    void init();
    void setup();
    void draw(int ModelUniform);
    void translate(glm::vec3 translate_vector);
    void moveTo(glm::vec3 position);
    std::vector<Vertex>& getVertexData();
    std::vector<GLuint>& getIndices();

    NewCube();
    NewCube(glm::vec3 position);
};

// enum NewDirection { FRONT = 0, BACK, TOP, BOTTOM, LEFT, RIGHT };

/** Le facce sono organizzate in questo modo:
 *  0 - front, 1 - right, 2 - back,
 *  3 - left, 4 - up, 5 - down
 */

enum CubeTypes {
    AIR = 0,
    EARTH
};


#endif