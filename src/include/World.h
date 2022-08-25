#ifndef WORLD_H
#define WORLD_H

#include "Chunk.h"

class World {
    // Chunks that make up the world;
    Chunk **chunks;
    // World Singleton
    World* current_world_instance;
    void init();
    ///TODO: Move perlin noise code here
};

#endif