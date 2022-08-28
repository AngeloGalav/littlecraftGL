#ifndef WORLD_H
#define WORLD_H

#include "FastNoiseLite.h"
#include "Camera.h"
#include "Chunk.h"

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

    bool player_in_main_chunk;

    void renderWorld(int Model_Uniform);
    void initWorld();
    void initNoise();
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