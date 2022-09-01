#ifndef WORLD_H
#define WORLD_H

#include "FastNoiseLite.h"
#include "Camera.h"
#include "Raycaster.h"
#include "Chunk.h"

struct Giz {
    Cube* look_cube;
    bool can_draw_lc;
    bool remove_mode;
    int look_cube_chunk;
    ivec3 lc_prev_position;
    ivec2 lc_chunk_position;
};


// Forward declaration
class Chunk;

class World {
public:
    // Modified Chunks
    Chunk* modified_chunks[WORLD_SIZE][WORLD_SIZE];

    // vanilla chunk gets translated and it's height modified. 
    Chunk *currently_displayed_chunks[DISPLAYED_CHUNKS];
    
    // World Singleton
    FastNoiseLite noise;
    int noiseData[WORLD_SIZE*CHUNK_SIZE][WORLD_SIZE*CHUNK_SIZE];

    // has the same function as displayed chunk, but displays only one at a time
    Chunk *debug_chunk;

    Giz Gizmos;
    Cube look_cube;

    Raycaster raycast;

    bool player_in_main_chunk;

    void renderWorld(int Model_Uniform);
    void initWorld();
    void initNoise();
    void UpdateGizmos();
    void drawGizmos(int MatModel);
    void updateWorld();
    void handleFacesBetweenChunks();  
    
    World();
    ~World();

    ivec2 curr_chunks_index[DISPLAYED_CHUNKS] = {
        {-1, -1},// LU
        {0, -1}, // U,
        {1, -1}, // RU,
        {-1, 0}, // L,
        {0, 0}, // Center,
        {1, 0}, // R,
        {-1, 1}, // LD,
        {0, 1}, // D,
        {1, 1}// RD,
    };
};


enum LoadedChunks{
    LU,
    U,
    RU,
    L,
    Center, 
    R,
    LD,
    D,
    RD
};


#endif