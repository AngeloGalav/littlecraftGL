#include "include/World.h"
#include <iostream>

#define chunk_index(x,y) (x + CHUNK_SIZE*y)

extern Camera mainCamera;

World::World(){

    player_in_current_chunk = false;

    for (int i = 0; i < WORLD_SIZE; i++) {
        for (int j = 0; j < WORLD_SIZE; j++) {
            modified_chunks[i][j] = NULL;
        }
    }
}

World::~World() {}

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
    debug_chunk->chunk_position = ivec2(0,0);
    debug_chunk->initChunk();
}

void World::initNoise(){
	noise.SetNoiseType(FastNoiseLite::NoiseType_Perlin);
	noise.SetFrequency(0.1);

	// Gather noise data
	int index = 0;

	for (int y = 0; y < WORLD_SIZE*CHUNK_SIZE; y++)
		for (int x = 0; x < WORLD_SIZE*CHUNK_SIZE; x++)
			noiseData[x][y] = (int) 16 * noise.GetNoise((float)x, (float)y);
    
    cout << "Loaded noise" << endl;
}

void World::renderWorld(int Model_Uniform){
    debug_chunk->drawChunk(Model_Uniform);
}

void World::updateWorld(){

    // posizione del giocatore relativa alla mappa
    vec2 player_position_to_map = vec2(mainCamera.ViewSetup.position.x, mainCamera.ViewSetup.position.z);
    player_in_current_chunk = 
    (debug_chunk->chunk_position.x * UNIT_SIZE <= player_position_to_map.x) 
    && ((debug_chunk->chunk_position.x + CHUNK_SIZE) * UNIT_SIZE >= player_position_to_map.x)
    && (debug_chunk->chunk_position.y * UNIT_SIZE <= player_position_to_map.y) 
    && ((debug_chunk->chunk_position.y + CHUNK_SIZE) * UNIT_SIZE >= player_position_to_map.y);

    cout << "changed: " <<  player_in_current_chunk << endl;

    // if ()

    ///TODO: change to player position
    // ivec2 player_relative_to_chunk = debug_chunk->player_in_chunk_bounds(vec3(0,0,0));


    // debug_chunk->chunk_position = ivec3(debug_chunk->chunk_position,debug_chunk->chunk_position,0);

    // // if (player_changed_chunk_pos())
    // //  = debug_chunk;
    // if (debug_chunk->dirty) { /*change world structures*/}
}