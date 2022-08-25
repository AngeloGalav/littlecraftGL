#ifndef WORLD_H
#define WORLD_H

#include "FastNoiseLite.h"
#include "Chunk.h"

// Forward declaration
class Chunk;

class World {
public:
    // Chunks that make up the world;
    Chunk *chunks;
    // World Singleton
    FastNoiseLite noise;
    int noiseData[WORLD_SIZE][WORLD_SIZE];

    Chunk **displayed_chunks;
    // has the same function as displayed chunk, but displays only one at a time
    Chunk *debug_chunk;

    void renderWorld(int Model_Uniform);
    void initWorld();
    void initNoise();
    World();
};

#endif