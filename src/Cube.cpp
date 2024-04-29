#include "include/Cube.h"

#include <iostream>

Cube::Cube() {
    faces[0].quadColor = (vec4(0.0, 1.0f, 0.0, 1.0f));
    faces[0].initQuadWithSingleColor();

    faces[1].quadColor = (vec4(1.0f, 0.0f, 0.0, 1.0f));
    faces[1].initQuadWithSingleColor();

    faces[2].quadColor = (vec4(0.0f, 0.0f, 1.0f, 1.0f));
    faces[2].initQuadWithSingleColor();

    faces[3].quadColor = (vec4(0.0, 1.0f, 1.0f, 1.0f));
    faces[3].initQuadWithSingleColor();

    faces[4].quadColor = (vec4(1.0f, 1.0f, 0.0, 1.0f));
    faces[4].initQuadWithSingleColor();

    faces[5].quadColor = (vec4(1.0f, 0.0f, 1.0f, 1.0f));
    faces[5].initQuadWithSingleColor();

    isAir = false;
    for (int i = 0; i < 6; i++) must_be_drawn[i] = true;
    position = vec3(0.0, 0.0, 0.0);
    scaleF = vec3(1.0, 1.0, 1.0);
}

// TODO: FIX THIS!! (TOO MUCH REDUNDANT CODE!)
Cube::Cube(vec4 color) {
    Cube();
    for (int i = 0; i < 6; i++) {
        faces[i].quadColor = color;
        faces[i].initQuadWithSingleColor();
    }

    isAir = false;

    for (int i = 0; i < 6; i++) must_be_drawn[i] = true;
    position = vec3(0.0, 0.0, 0.0);
    scaleF = vec3(1.0, 1.0, 1.0);
}

void Cube::initTextures() {
    // Apply texture offsets to all quads of the cube
    for (int i = 0; i < 4; i++) {
        faces[i].texture_coords_offset = atlas_offset[2];
    }

    faces[4].texture_coords_offset = atlas_offset[0];
    faces[5].texture_coords_offset = atlas_offset[1];

    for (int i = 0; i < 6; i++) faces[i].initQuadTexture();
}

void Cube::setScaleFactor(vec3 scalef) {}

void Cube::initTexturedCube() {
    initTextures();

    faces[0].initVAO_textures();
    faces[0].Model = mat4(1.0);
    faces[0].Model =
        scale(faces[0].Model,
              vec3(2.0f * scaleF.x, 2.0f * scaleF.y, 2.0f * scaleF.z));
    faces[0].Model = translate(faces[0].Model, vec3(0.0f, 0.0f, 1.0f));

    faces[1].initVAO_textures();
    faces[1].Model = mat4(1.0);
    faces[1].Model =
        scale(faces[1].Model,
              vec3(2.0f * scaleF.x, 2.0f * scaleF.y, 2.0f * scaleF.z));
    faces[1].Model = translate(faces[1].Model, vec3(1.0f, 0.0, 0.0f));
    faces[1].Model = rotate(faces[1].Model, radians(-90.0f), vec3(0, 1, 0));

    faces[2].initVAO_textures();
    faces[2].Model = mat4(1.0);
    faces[2].Model =
        scale(faces[2].Model,
              vec3(2.0f * scaleF.x, 2.0f * scaleF.y, 2.0f * scaleF.z));
    faces[2].Model = translate(faces[2].Model, vec3(0.0, 0.0, -1.0f));

    faces[3].initVAO_textures();
    faces[3].Model = mat4(1.0);
    faces[3].Model =
        scale(faces[3].Model,
              vec3(2.0f * scaleF.x, 2.0f * scaleF.y, 2.0f * scaleF.z));
    faces[3].Model = translate(faces[3].Model, vec3(-1.0f, 0.0, 0.0f));
    faces[3].Model = rotate(faces[3].Model, radians(90.0f), vec3(0, 1, 0));

    faces[4].initVAO_textures();
    faces[4].Model = mat4(1.0);
    faces[4].Model =
        scale(faces[4].Model,
              vec3(2.0f * scaleF.x, 2.0f * scaleF.y, 2.0f * scaleF.z));
    faces[4].Model = translate(faces[4].Model, vec3(0, 1.0f, 0.0f));
    faces[4].Model = rotate(faces[4].Model, radians(90.0f), vec3(1, 0, 0));

    faces[5].initVAO_textures();
    faces[5].Model = mat4(1.0);
    faces[5].Model =
        scale(faces[5].Model,
              vec3(2.0f * scaleF.x, 2.0f * scaleF.y, 2.0f * scaleF.z));
    faces[5].Model = translate(faces[5].Model, vec3(0.0, -1.0f, 0.0f));
    faces[5].Model = rotate(faces[5].Model, radians(-90.0f), vec3(1, 0, 0));

    ModelCube = mat4(1.0);
    moveTo(position);
}

void Cube::initCube() {
    faces[0].initVAO();
    faces[0].Model = mat4(1.0);
    faces[0].Model =
        scale(faces[0].Model,
              vec3(2.0f * scaleF.x, 2.0f * scaleF.y, 2.0f * scaleF.z));
    faces[0].Model = translate(faces[0].Model, vec3(0.0f, 0.0f, 1.0f));

    faces[1].initVAO();
    faces[1].Model = mat4(1.0);
    faces[1].Model =
        scale(faces[1].Model,
              vec3(2.0f * scaleF.x, 2.0f * scaleF.y, 2.0f * scaleF.z));
    faces[1].Model = translate(faces[1].Model, vec3(1.0f, 0.0, 0.0f));
    faces[1].Model = rotate(faces[1].Model, radians(-90.0f), vec3(0, 1, 0));

    faces[2].initVAO();
    faces[2].Model = mat4(1.0);
    faces[2].Model =
        scale(faces[2].Model,
              vec3(2.0f * scaleF.x, 2.0f * scaleF.y, 2.0f * scaleF.z));
    faces[2].Model = translate(faces[2].Model, vec3(0.0, 0.0, -1.0f));

    faces[3].initVAO();
    faces[3].Model = mat4(1.0);
    faces[3].Model =
        scale(faces[3].Model,
              vec3(2.0f * scaleF.x, 2.0f * scaleF.y, 2.0f * scaleF.z));
    faces[3].Model = translate(faces[3].Model, vec3(-1.0f, 0.0, 0.0f));
    faces[3].Model = rotate(faces[3].Model, radians(90.0f), vec3(0, 1, 0));

    faces[4].initVAO();
    faces[4].Model = mat4(1.0);
    faces[4].Model =
        scale(faces[4].Model,
              vec3(2.0f * scaleF.x, 2.0f * scaleF.y, 2.0f * scaleF.z));
    faces[4].Model = translate(faces[4].Model, vec3(0, 1.0f, 0.0f));
    faces[4].Model = rotate(faces[4].Model, radians(90.0f), vec3(1, 0, 0));

    faces[5].initVAO();
    faces[5].Model = mat4(1.0);
    faces[5].Model =
        scale(faces[5].Model,
              vec3(2.0f * scaleF.x, 2.0f * scaleF.y, 2.0f * scaleF.z));
    faces[5].Model = translate(faces[5].Model, vec3(0.0, -1.0f, 0.0f));
    faces[5].Model = rotate(faces[5].Model, radians(-90.0f), vec3(1, 0, 0));

    ModelCube = mat4(1.0);
    moveTo(position);  // gets initialized to the start position
}

/** Draws each face of the cube
 *
 */
void Cube::drawMesh(int Model_Uniform) {
    for (int i = 0; i < 6; i++) {
        if (must_be_drawn[i])
            faces[i].drawMeshFromParent(Model_Uniform, ModelCube);
    }
}

/** Translates cube using a vector
 *
 */
void Cube::translateCube(ivec3 translate_vector) {
    ModelCube =
        translate(ModelCube, ((float)UNIT_SIZE) * vec3(translate_vector));
}

/** Moves the cube to a determined position
 *
 */
void Cube::moveTo(ivec3 position) {
    translateCube(position - this->position);
    this->position = position;
}