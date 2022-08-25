#ifndef CHUNK_H
#define CHUNK_H

#include "Block.h"
#include "World.h"

class World;

class Chunk
{
private:
public:
    bool dirty; // if this is true, the chunk mesh must be regenerated at the next frame
    Block chunk_blocks[CHUNK_SIZE][CHUNK_SIZE][CHUNK_HEIGHT];
    vec3 position;
    bool state_changed;

    World *world_instance;

    void updateChunk();
    void initChunk();
    void drawChunk(int Model_Uniform);
    void checkNeighbours(int i, int j, int k);
    void translateChunk(ivec3 vector);

    Chunk();
};


#endif