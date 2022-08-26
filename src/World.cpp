#include "include/World.h"
#include <iostream>

#define chunk_index(x,y) (x + CHUNK_SIZE*y)

World::World(){
    // chunks = new Chunk[WORLD_SIZE*WORLD_SIZE];
};

void World::initWorld(){
    initNoise();
    // for (int i = 0; i < WORLD_SIZE; i++) {
    //     for (int j = 0; j < WORLD_SIZE; j++) {
    //         chunks[chunk_index(i,j)].world_instance = this;
    //         // centra la mappa al centro
    //         chunks[chunk_index(i,j)].translateChunk(ivec3((int)WORLD_SIZE/2, -2, (int)WORLD_SIZE/2));
    //     }
    // }

    // debug_chunk = &chunks[chunk_index((int)WORLD_SIZE/2, (int)WORLD_SIZE/2)];
    debug_chunk = new Chunk();
    debug_chunk->world_instance = this;
    debug_chunk->initChunk();
}

void World::initNoise(){
	noise.SetNoiseType(FastNoiseLite::NoiseType_Perlin);
	noise.SetFrequency(0.1);

	// Gather noise data
	int index = 0;

	for (int y = 0; y < WORLD_SIZE; y++)
		for (int x = 0; x < WORLD_SIZE; x++)
			noiseData[x][y] = (int) 16 * noise.GetNoise((float)x, (float)y);
}

void World::renderWorld(int Model_Uniform){
    debug_chunk->drawChunk(Model_Uniform);
}