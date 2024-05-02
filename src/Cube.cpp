#include "include/Cube.h"

#include <iostream>

Cube::Cube() {
    faces[FRONT].quadColor = (vec4(0.0, 1.0f, 0.0, 1.0f));
    faces[FRONT].initQuadWithSingleColor();

    faces[RIGHT].quadColor = (vec4(1.0f, 0.0f, 0.0, 1.0f));
    faces[RIGHT].initQuadWithSingleColor();

    faces[BACK].quadColor = (vec4(0.0f, 0.0f, 1.0f, 1.0f));
    faces[BACK].initQuadWithSingleColor();

    faces[LEFT].quadColor = (vec4(0.0, 1.0f, 1.0f, 1.0f));
    faces[LEFT].initQuadWithSingleColor();

    faces[UP].quadColor = (vec4(1.0f, 1.0f, 0.0, 1.0f));
    faces[UP].initQuadWithSingleColor();

    faces[DOWN].quadColor = (vec4(1.0f, 0.0f, 1.0f, 1.0f));
    faces[DOWN].initQuadWithSingleColor();

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

    faces[UP].texture_coords_offset = atlas_offset[0];
    faces[DOWN].texture_coords_offset = atlas_offset[1];

    for (int i = 0; i < 6; i++) faces[i].initQuad(true);
}

void Cube::setScale(vec3 scalef) { scaleF = scalef; }

// REMEMBER: TRANSFORMATION ARE APPLIED IN THE REVERSE ORDER!
void Cube::initCube(bool hasTextures) {
    if (hasTextures) initTextures();

    faces[FRONT].initVAO(hasTextures);
    faces[FRONT].Model = mat4(1.0);
    faces[FRONT].Model =
        scale(faces[FRONT].Model,
              vec3(2.0f * scaleF.x, 2.0f * scaleF.y, 2.0f * scaleF.z));
    faces[FRONT].Model = translate(faces[FRONT].Model, vec3(0.0f, 0.0f, 1.0f));

    faces[RIGHT].initVAO(hasTextures);
    faces[RIGHT].Model = mat4(1.0);
    faces[RIGHT].Model =
        scale(faces[RIGHT].Model,
              vec3(2.0f * scaleF.x, 2.0f * scaleF.y, 2.0f * scaleF.z));
    faces[RIGHT].Model = translate(faces[RIGHT].Model, vec3(1.0f, 0.0, 0.0f));
    faces[RIGHT].Model =
        rotate(faces[RIGHT].Model, radians(-90.0f), vec3(0, 1, 0));
    faces[RIGHT].Model =
        rotate(faces[RIGHT].Model, radians(-180.0f), vec3(0, 1, 0));

    faces[BACK].initVAO(hasTextures);
    faces[BACK].Model = mat4(1.0);
    faces[BACK].Model =
        scale(faces[BACK].Model,
              vec3(2.0f * scaleF.x, 2.0f * scaleF.y, 2.0f * scaleF.z));
    faces[BACK].Model = translate(faces[BACK].Model, vec3(0.0, 0.0, -1.0f));
    faces[BACK].Model =
        rotate(faces[BACK].Model, radians(-180.0f), vec3(0, 1, 0));

    faces[LEFT].initVAO(hasTextures);
    faces[LEFT].Model = mat4(1.0);
    faces[LEFT].Model =
        scale(faces[LEFT].Model,
              vec3(2.0f * scaleF.x, 2.0f * scaleF.y, 2.0f * scaleF.z));
    faces[LEFT].Model = translate(faces[LEFT].Model, vec3(-1.0f, 0.0, 0.0f));
    faces[LEFT].Model =
        rotate(faces[LEFT].Model, radians(90.0f), vec3(0, 1, 0));
    faces[LEFT].Model =
        rotate(faces[LEFT].Model, radians(-180.0f), vec3(0, 1, 0));

    faces[UP].initVAO(hasTextures);
    faces[UP].Model = mat4(1.0);
    faces[UP].Model =
        scale(faces[UP].Model,
              vec3(2.0f * scaleF.x, 2.0f * scaleF.y, 2.0f * scaleF.z));
    faces[UP].Model = translate(faces[UP].Model, vec3(0, 1.0f, 0.0f));
    faces[UP].Model = rotate(faces[UP].Model, radians(90.0f), vec3(1, 0, 0));
    faces[UP].Model =
        rotate(faces[UP].Model, radians(-180.0f), vec3(0, 1, 0));

    faces[DOWN].initVAO(hasTextures);
    faces[DOWN].Model = mat4(1.0);
    faces[DOWN].Model =
        scale(faces[DOWN].Model,
              vec3(2.0f * scaleF.x, 2.0f * scaleF.y, 2.0f * scaleF.z));
    faces[DOWN].Model = translate(faces[DOWN].Model, vec3(0.0, -1.0f, 0.0f));
    faces[DOWN].Model =
        rotate(faces[DOWN].Model, radians(-90.0f), vec3(1, 0, 0));
    faces[DOWN].Model =
        rotate(faces[DOWN].Model, radians(-180.0f), vec3(0, 1, 0));

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