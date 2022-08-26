#ifndef BLOCK_H
#define BLOCK_H

#include "Cube.h"


enum BlockType {
    DIRT_1,
    DIRT_2,
    STONE,
    WATER,
    WOOD,
    LEAVES 
};


class Block : public Cube {
public:
    BlockType type;
    void initCube();
    Block();
};

#endif