#ifndef CHUNK_H
#define CHUNK_H

#include "Block.h"

class Chunk
{
private:
public:
    BlockType chunk_blocks[16][16][128];
};


#endif