#ifndef WORLD_H
#define WORLD_H

#include "Camera.h"
#include "Chunk.h"
#include "FastNoiseLite.h"

// Forward declaration
class Chunk;

struct Giz {
    Cube* look_cube;
    bool can_draw_lc;
    bool remove_mode;
    ivec3 lc_prev_position;
    ivec2 lc_chunk_position;
    Chunk* lc_chunk;
};

class World {
   public:
    // Modified Chunks
    Chunk* modified_chunks[WORLD_SIZE][WORLD_SIZE];

    // vanilla chunk gets translated and it's height modified.
    Chunk* currently_displayed_chunks[DISPLAYED_CHUNKS];
    bool has_modified_chunk[DISPLAYED_CHUNKS];

    // World Singleton
    FastNoiseLite noise;
    int noiseData[WORLD_SIZE * CHUNK_SIZE][WORLD_SIZE * CHUNK_SIZE];

    // The block to add
    Cube block_to_add;

    Giz Gizmos;
    unsigned int rm_mode_shader_location;

    bool player_in_main_chunk;

    void renderWorld(int Model_Uniform);
    void initWorld();
    void initNoise();
    void updateGizmos();
    void drawGizmos(int MatModel);
    void updateWorld();
    void handleFacesBetweenChunks();
    void addBlock();
    void removeBlock();

    World();
    ~World();

    ivec2 curr_chunks_index[DISPLAYED_CHUNKS] = {
        {-1, -1},  // LU
        {0, -1},   // U,
        {1, -1},   // RU,
        {-1, 0},   // L,
        {0, 0},    // Center,
        {1, 0},    // R,
        {-1, 1},   // LD,
        {0, 1},    // D,
        {1, 1}     // RD,
    };
};

enum LoadedChunks { LU, U, RU, L, Center, R, LD, D, RD };

#endif