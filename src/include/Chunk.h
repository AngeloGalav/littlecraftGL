#ifndef CHUNK_H
#define CHUNK_H

#include "Block.h"

class Chunk
{
private:
public:
    bool dirty; // if this is true, the chunk mesh must be regenerated at the next frame
    BlockType chunk_blocks[16][16][128];
    vec3 position;
};


#endif