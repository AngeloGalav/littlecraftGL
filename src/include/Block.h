#ifndef BLOCK_H
#define BLOCK

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
    vec2 atlas_offset[3]; // ogni cubo ha solo 3 texture in Minecraft
    void initCube();
    void initCubeTextures();
    Block();
    Block(vec2 *atlas_offset);
};

#endif