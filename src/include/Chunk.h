#ifndef CHUNK_H
#define CHUNK_H

#include "Block.h"

class Chunk
{
private:
public:
    bool dirty; // if this is true, the chunk mesh must be regenerated at the next frame
    Block chunk_blocks[CHUNK_SIZE][CHUNK_SIZE][CHUNK_HEIGHT];
    vec3 position;
    bool state_changed;
    void updateChunk();
    void initChunk();
    void drawChunk(int Model_Uniform);
    void checkNeighbours();
    void chunkIndexToPosition();
    Chunk();
};


#endif