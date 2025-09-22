#ifndef WORLD_2_H
#define WORLD_2_H

#include "Chunk2.h"
#include "Lib.h"
#include <unordered_map>
// #include "World.h"

struct ChunkCoordHash {
    // operator() rende questo struct callable come una funzione
    std::size_t operator()(const glm::ivec3& coord) const {

        // Prende hash di ogni coordinata
        std::size_t hash_x = std::hash<int>()(coord.x);           // Hash di X
        std::size_t hash_y = std::hash<int>()(coord.y) << 1;      // Hash di Y shiftato 1 bit
        std::size_t hash_z = std::hash<int>()(coord.z) << 2;      // Hash di Z shiftato 2 bit

        // Li combina con XOR (^)
        return hash_x ^ hash_y ^ hash_z;
    }
};

class NewWorld {
private:
    std::unordered_map<glm::ivec3, NewChunk*, ChunkCoordHash> chunks;
    int renderDistance = 4; // chunks to render around player

public:
    NewWorld();
    ~NewWorld();

    // Chunk management
    NewChunk* getChunk(int x, int y, int z);
    NewChunk* getChunkAt(glm::vec3 worldPos);
    void generateChunk(int x, int y, int z);
    void unloadChunk(int x, int y, int z);

    // World operations
    void updateAroundPlayer(glm::vec3 playerPos);
    void rebuildChunk(int x, int y, int z);
    void rebuildAdjacentChunks(int x, int y, int z);

    // Rendering
    void draw(int ModelUniform);

    // Block operations
    bool setBlock(glm::vec3 worldPos, int blockType);
    int getBlock(glm::vec3 worldPos);

    // Utility
    glm::ivec3 worldToChunkCoord(glm::vec3 worldPos);
    glm::vec3 chunkCoordToWorld(glm::ivec3 coord);
    std::array<NewChunk*, 6> getAdjacentChunks(int x, int y, int z);
};

#endif