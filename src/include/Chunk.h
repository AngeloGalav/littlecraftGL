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
    bool to_move;
    bool map_out_of_bounds;
    Block chunk_blocks[CHUNK_SIZE][CHUNK_SIZE][CHUNK_HEIGHT];
    ivec2 chunk_position; // position of the chunk between 0 and WORLD_SIZE-1
    bool state_changed;

    World *world_instance;

    void updateChunk();
    void applyChunkPosition(int i, int j, int k);
    void initChunk();
    void drawChunk(int Model_Uniform);
    void checkNeighbours(int i, int j, int k);
    void translateChunk(ivec3 vector);
    void translateChunkInWorld(ivec2 vector);
    ivec2 player_in_chunk_bounds(vec3 player_position);
    void checkNeighbouringChunk(Chunk* neighbour, bool checkHorizontal);

    Chunk();
    ~Chunk();
};


#endif