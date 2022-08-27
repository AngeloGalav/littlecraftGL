#ifndef WORLD_H
#define WORLD_H

#include "FastNoiseLite.h"
#include "Camera.h"
#include "Chunk.h"

// Forward declaration
class Chunk;

class World {
public:
    // Modified Chunks;
    Chunk *modified_chunks[WORLD_SIZE][WORLD_SIZE];

    // vanilla chunk gets translated and it's height modified. 
    Chunk *reused_chunk;
    // World Singleton
    FastNoiseLite noise;
    int noiseData[WORLD_SIZE*CHUNK_SIZE][WORLD_SIZE*CHUNK_SIZE];

    vector<Chunk*> displayed_chunks;
    // has the same function as displayed chunk, but displays only one at a time
    Chunk *debug_chunk;

    bool player_in_current_chunk;

    void renderWorld(int Model_Uniform);
    void initWorld();
    void initNoise();
    void updateWorld();
    World();
    ~World();
};

#endif