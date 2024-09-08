#include "include/World.h"

#include <iostream>

#define chunk_index(x, y) (x + CHUNK_SIZE * y)

extern Camera mainCamera;

World::World() {
    player_in_main_chunk = false;

    for (int i = 0; i < WORLD_SIZE; i++) {
        for (int j = 0; j < WORLD_SIZE; j++) {
            modified_chunks[i][j] = NULL;
        }
    }

    Gizmos.look_cube = new Cube(LOOKCUBE_COLOR);

    block_to_add.atlas_offset[0] = block_to_add.atlas_offset[1] =
        block_to_add.atlas_offset[2] = vec2(4, 15);
}

World::~World() {
    for (int i = 0; i < DISPLAYED_CHUNKS; i++)
        delete currently_displayed_chunks[i];
}

void World::initWorld() {
    initNoise();

    for (int i = 0; i < DISPLAYED_CHUNKS; i++) {
        currently_displayed_chunks[i] = new Chunk();
        currently_displayed_chunks[i]->world_instance = this;
        currently_displayed_chunks[i]->chunk_position = curr_chunks_index[i];
        currently_displayed_chunks[i]->initChunk();
    }

    for (int i = 0; i < WORLD_SIZE; i++) {
        for (int j = 0; j < WORLD_SIZE; j++) {
            modified_chunks[i][j] = NULL;
        }
    }

    for (int i = 0; i < DISPLAYED_CHUNKS; i++) {
        has_modified_chunk[i] = false;
    }

    Gizmos.can_draw_lc = true;
    Gizmos.remove_mode = false;

    handleFacesBetweenChunks();

    Gizmos.look_cube->setScale(vec3(1.2, 1.2, 1.2));
    Gizmos.look_cube->initCube(false); // gizmo cube has no texture
    Gizmos.lc_chunk_position = ivec2(0, 0);
    Gizmos.lc_prev_position = Gizmos.look_cube->position;
}

void World::handleFacesBetweenChunks() {
    int row_length = sqrt(DISPLAYED_CHUNKS);
    for (int i = 0; i < DISPLAYED_CHUNKS - 1; i++) {
        if ((i + 1) % row_length != 0 && (DISPLAYED_CHUNKS - row_length) > i) {
            currently_displayed_chunks[i]->checkNeighbouringChunk(
                currently_displayed_chunks[i + 1], true);
            currently_displayed_chunks[i]->checkNeighbouringChunk(
                currently_displayed_chunks[i + row_length], false);
        } else if ((DISPLAYED_CHUNKS - row_length) > i &&
                   (i + 1) % row_length == 0) {
            currently_displayed_chunks[i]->checkNeighbouringChunk(
                currently_displayed_chunks[i + row_length], false);
        } else if ((DISPLAYED_CHUNKS - row_length) <= i &&
                   (i + 1) % row_length != 0) {
            currently_displayed_chunks[i]->checkNeighbouringChunk(
                currently_displayed_chunks[i + 1], true);
        }
    }
}

void World::updateGizmos() {
    // sets the position of the cube based on the direction of the camera
    vec3 lk_position = mainCamera.Front;
    Gizmos.look_cube->moveTo(
        vec3(floor(mainCamera.Position.x / UNIT_SIZE),
             floor(mainCamera.Position.y / UNIT_SIZE),
             floor(mainCamera.Position.z / UNIT_SIZE)) +
        vec3(floor(DISTANCE_FROM_CAMERA * lk_position.x),
             floor(DISTANCE_FROM_CAMERA * lk_position.y),
             floor(DISTANCE_FROM_CAMERA * lk_position.z)));
}

void World::drawGizmos(int MatModel) {
    glUniform1i(rm_mode_shader_location, 0);
    if (Gizmos.can_draw_lc) Gizmos.look_cube->drawMesh(MatModel);
}

void World::initNoise() {
    noise.SetNoiseType(FastNoiseLite::NoiseType_Perlin);
    noise.SetFrequency(0.1);

    for (int y = 0; y < WORLD_SIZE * CHUNK_SIZE; y++)
        for (int x = 0; x < WORLD_SIZE * CHUNK_SIZE; x++)
            noiseData[x][y] = (int)16 * noise.GetNoise((float)x, (float)y);

    std::cout << "\nLoaded noise" << std::endl;
}

void World::renderWorld(int Model_Uniform) {
    for (int i = 0; i < DISPLAYED_CHUNKS; i++) {
        currently_displayed_chunks[i]->drawChunk(Model_Uniform);
    }
}

void World::updateWorld() {
    // mini feedback visivo quando si tolgono/piazzano cubi

    // posizione del giocatore relativa alla mappa
    vec2 player_position_to_map =
        vec2(mainCamera.Position.x, mainCamera.Position.z);

    // c'è stato un cambio di posizione del cubo
    if (Gizmos.look_cube->position.x != Gizmos.lc_prev_position.x ||
        Gizmos.look_cube->position.y != Gizmos.lc_prev_position.y ||
        Gizmos.look_cube->position.z != Gizmos.lc_prev_position.z) {
        int i_lc =
            !(currently_displayed_chunks[Center]->chunk_position.x *
                  CHUNK_SIZE <=
              Gizmos.look_cube->position.x) *
                -1 +
            !((currently_displayed_chunks[Center]->chunk_position.x + 1) *
                  CHUNK_SIZE >=
              Gizmos.look_cube->position.x);

        int j_lc =
            !(currently_displayed_chunks[Center]->chunk_position.y *
                  CHUNK_SIZE <=
              Gizmos.look_cube->position.z) *
                -1 +
            !((currently_displayed_chunks[Center]->chunk_position.y + 1) *
                  CHUNK_SIZE >=
              Gizmos.look_cube->position.z);

        // updates the chunk of the cube
        Gizmos.lc_chunk =
            currently_displayed_chunks[(i_lc + 1) + (j_lc + 1) * 3];

        Gizmos.lc_prev_position = Gizmos.look_cube->position;
    }

    // solves
    player_in_main_chunk =
        (currently_displayed_chunks[Center]->chunk_position.x * CHUNK_SIZE *
             UNIT_SIZE <=
         player_position_to_map.x) &&
        ((currently_displayed_chunks[Center]->chunk_position.x + 1) *
             CHUNK_SIZE * UNIT_SIZE >=
         player_position_to_map.x) &&
        (currently_displayed_chunks[Center]->chunk_position.y * CHUNK_SIZE *
             UNIT_SIZE <=
         player_position_to_map.y) &&
        ((currently_displayed_chunks[Center]->chunk_position.y + 1) *
             CHUNK_SIZE * UNIT_SIZE >=
         player_position_to_map.y);

    if (!player_in_main_chunk) {
        // si salva la direzione in cui il giocatore si è spostato dal chunk
        int i = !(currently_displayed_chunks[Center]->chunk_position.x *
                      CHUNK_SIZE * UNIT_SIZE <=
                  player_position_to_map.x) *
                    -1 +
                !((currently_displayed_chunks[Center]->chunk_position.x + 1) *
                      CHUNK_SIZE * UNIT_SIZE >=
                  player_position_to_map.x);
        int j = !(currently_displayed_chunks[Center]->chunk_position.y *
                      CHUNK_SIZE * UNIT_SIZE <=
                  player_position_to_map.y) *
                    -1 +
                !((currently_displayed_chunks[Center]->chunk_position.y + 1) *
                      CHUNK_SIZE * UNIT_SIZE >=
                  player_position_to_map.y);

        // moves chunk to match noise map
        for (int k = 0; k < DISPLAYED_CHUNKS; k++) {
            // int x = currently_displayed_chunks[k]->chunk_position.x +
            // WORLD_SIZE/2 + i; int y =
            // currently_displayed_chunks[k]->chunk_position.y + WORLD_SIZE/2 +
            // j; ivec2 old_pos = currently_displayed_chunks[k]->chunk_position;

            // if (modified_chunks[x][y] == NULL) {
            //     if (has_modified_chunk[k]) {
            //         currently_displayed_chunks[k] = new Chunk();
            //     }
            //     currently_displayed_chunks[k]->translateChunkInWorld(ivec2(i,
            //     j));
            // } else {
            //     std::cout << "segfault causato da modified_chunks" << std::endl;
            //     currently_displayed_chunks[k] = modified_chunks[x][y];
            //     has_modified_chunk[k] = true;
            // }

            currently_displayed_chunks[k]->translateChunkInWorld(ivec2(i, j));
        }

        // update chunk
        for (int i = 0; i < DISPLAYED_CHUNKS; i++) {
            // if (!currently_displayed_chunks[i]->modified)
            currently_displayed_chunks[i]->updateChunk();
        }

        handleFacesBetweenChunks();
    }
}

void World::addBlock() {
    Gizmos.lc_chunk->addBlockToChunk(Gizmos.look_cube->position, block_to_add);
}

void World::removeBlock() {
    Gizmos.lc_chunk->removeBlockFromChunk(Gizmos.look_cube->position);

    // Modifies the chunk only if had actual modifications in it
    // if (Gizmos.lc_chunk->dirty) {
    //     // std::cout << "segfault causato da dirty" << std::endl;
    //     modified_chunks
    //     [Gizmos.lc_chunk->chunk_position.x + WORLD_SIZE/2]
    //     [Gizmos.lc_chunk->chunk_position.y + WORLD_SIZE/2] = Gizmos.lc_chunk;

    //     Gizmos.lc_chunk->dirty = false;
    // }
}