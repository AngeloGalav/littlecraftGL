// #include "include/World2.h"

// NewWorld::NewWorld() {
//     renderDistance = 4;
// }

// NewWorld::~NewWorld() {
//     // Delete all chunks to prevent memory leaks
//     for (auto& pair : chunks) {
//         delete pair.second;
//     }
//     chunks.clear();
// }

// NewChunk* NewWorld::getChunk(int x, int y, int z) {
//     auto it = chunks.find(glm::ivec3(x, y, z));
//     return (it != chunks.end()) ? it->second : nullptr;
// }

// NewChunk* NewWorld::getChunkAt(glm::vec3 worldPos) {
//     glm::ivec3 chunkCoord = worldToChunkCoord(worldPos);
//     return getChunk(chunkCoord.x, chunkCoord.y, chunkCoord.z);
// }

// void NewWorld::generateChunk(int x, int y, int z) {
//     // Don't generate if already exists
//     if (getChunk(x, y, z) != nullptr) return;

//     // Create new chunk at world position
//     glm::vec3 chunkWorldPos = chunkCoordToWorld(glm::ivec3(x, y, z));
//     NewChunk* newChunk = new NewChunk(chunkWorldPos);

//     // Get adjacent chunks for seamless face culling
//     std::array<NewChunk*, 6> adjacents = getAdjacentChunks(x, y, z);

//     // Build chunk geometry
//     newChunk->build(adjacents);
//     newChunk->setup();

//     // Add to chunks map
//     chunks[glm::ivec3(x, y, z)] = newChunk;

//     std::cout << "[WORLD] Generated chunk at (" << x << ", " << y << ", " << z << ")" << std::endl;
// }

// void NewWorld::unloadChunk(int x, int y, int z) {
//     auto it = chunks.find(glm::ivec3(x, y, z));
//     if (it != chunks.end()) {
//         delete it->second;
//         chunks.erase(it);
//         std::cout << "[WORLD] Unloaded chunk at (" << x << ", " << y << ", " << z << ")" << std::endl;
//     }
// }

// void NewWorld::updateAroundPlayer(glm::vec3 playerPos) {
//     glm::ivec3 playerChunk = worldToChunkCoord(playerPos);

//     // Generate chunks in render distance around player
//     for (int x = -renderDistance; x <= renderDistance; x++) {
//         for (int y = -renderDistance; y <= renderDistance; y++) {
//             for (int z = -renderDistance; z <= renderDistance; z++) {
//                 int chunkX = playerChunk.x + x;
//                 int chunkY = playerChunk.y + y;
//                 int chunkZ = playerChunk.z + z;
//                 generateChunk(chunkX, chunkY, chunkZ);
//             }
//         }
//     }

//     // Unload chunks that are too far away
//     std::vector<glm::ivec3> chunksToUnload;

//     for (auto& pair : chunks) {
//         glm::ivec3 chunkCoord = pair.first;

//         // Calculate distance from player chunk
//         int dx = abs(chunkCoord.x - playerChunk.x);
//         int dy = abs(chunkCoord.y - playerChunk.y);
//         int dz = abs(chunkCoord.z - playerChunk.z);

//         // Use max distance (Chebyshev distance) for cubic unload area
//         int maxDistance = std::max({dx, dy, dz});

//         // Unload if beyond render distance + buffer
//         if (maxDistance > renderDistance + 2) {
//             chunksToUnload.push_back(chunkCoord);
//         }
//     }

//     // Actually unload the chunks
//     for (const auto& coord : chunksToUnload) {
//         unloadChunk(coord.x, coord.y, coord.z);
//     }
// }

// void NewWorld::rebuildChunk(int x, int y, int z) {
//     NewChunk* chunk = getChunk(x, y, z);
//     if (chunk != nullptr && chunk->getNeedsRebuild()) {
//         // Clear existing mesh
//         chunk->vertices.clear();
//         chunk->indices.clear();

//         // Rebuild with proper adjacents
//         std::array<NewChunk*, 6> adjacents = getAdjacentChunks(x, y, z);
//         chunk->build(adjacents);
//         chunk->setup();
//         chunk->setNeedsRebuild(false);
//     }
// }

// void NewWorld::rebuildAdjacentChunks(int x, int y, int z) {
//     // Rebuild all 6 adjacent chunks
//     rebuildChunk(x + 1, y, z);
//     rebuildChunk(x - 1, y, z);
//     rebuildChunk(x, y + 1, z);
//     rebuildChunk(x, y - 1, z);
//     rebuildChunk(x, y, z + 1);
//     rebuildChunk(x, y, z - 1);
// }

// void NewWorld::draw(int ModelUniform) {
//     for (auto& pair : chunks) {
//         pair.second->draw(ModelUniform);
//     }
// }

// bool NewWorld::setBlock(glm::vec3 worldPos, int blockType) {
//     NewChunk* chunk = getChunkAt(worldPos);
//     if (chunk == nullptr) return false;

//     glm::ivec3 chunkCoord = worldToChunkCoord(worldPos);
//     glm::vec3 chunkWorldPos = chunkCoordToWorld(chunkCoord);
//     glm::ivec3 localPos = glm::ivec3(worldPos - chunkWorldPos);

//     // Set block in chunk
//     if (localPos.x >= 0 && localPos.x < CHUNK_SIZE &&
//         localPos.y >= 0 && localPos.y < CHUNK_SIZE &&
//         localPos.z >= 0 && localPos.z < CHUNK_SIZE) {

//         chunk->chunk_map[localPos.x][localPos.y][localPos.z] = blockType;

//         // Rebuild this chunk and adjacent ones if needed
//         rebuildChunk(chunkCoord.x, chunkCoord.y, chunkCoord.z);
//         rebuildAdjacentChunks(chunkCoord.x, chunkCoord.y, chunkCoord.z);

//         return true;
//     }

//     return false;
// }

// int NewWorld::getBlock(glm::vec3 worldPos) {
//     NewChunk* chunk = getChunkAt(worldPos);
//     if (chunk == nullptr) return 0;

//     glm::ivec3 chunkCoord = worldToChunkCoord(worldPos);
//     glm::vec3 chunkWorldPos = chunkCoordToWorld(chunkCoord);
//     glm::ivec3 localPos = glm::ivec3(worldPos - chunkWorldPos);

//     if (localPos.x >= 0 && localPos.x < CHUNK_SIZE &&
//         localPos.y >= 0 && localPos.y < CHUNK_SIZE &&
//         localPos.z >= 0 && localPos.z < CHUNK_SIZE) {

//         return chunk->chunk_map[localPos.x][localPos.y][localPos.z];
//     }

//     return 0; // Air/empty
// }

// glm::ivec3 NewWorld::worldToChunkCoord(glm::vec3 worldPos) {
//     return glm::ivec3(
//         floor(worldPos.x / CHUNK_SIZE),
//         floor(worldPos.y / CHUNK_SIZE),
//         floor(worldPos.z / CHUNK_SIZE)
//     );
// }

// glm::vec3 NewWorld::chunkCoordToWorld(glm::ivec3 coord) {
//     return glm::vec3(
//         coord.x * CHUNK_SIZE,
//         coord.y * CHUNK_SIZE,
//         coord.z * CHUNK_SIZE
//     );
// }

// std::array<NewChunk*, 6> NewWorld::getAdjacentChunks(int x, int y, int z) {
//     return {
//         getChunk(x + 1, y, z),  // +X
//         getChunk(x - 1, y, z),  // -X
//         getChunk(x, y + 1, z),  // +Y
//         getChunk(x, y - 1, z),  // -Y
//         getChunk(x, y, z + 1),  // +Z
//         getChunk(x, y, z - 1)   // -Z
//     };
// }