#include "include/World.h"
#include <iostream>

#define chunk_index(x,y) (x + CHUNK_SIZE*y)

extern Camera mainCamera;

World::World(){

    player_in_main_chunk = false;

    for (int i = 0; i < WORLD_SIZE; i++) {
        for (int j = 0; j < WORLD_SIZE; j++) {
            modified_chunks[i][j] = NULL;
        }
    }
}

World::~World() {
    for (int i = 0; i < DISPLAYED_CHUNKS; i++) 
        delete currently_displayed_chunks[i];
    
    delete debug_chunk;
}

void World::initWorld(){
    initNoise();

    for (int i = 0; i < DISPLAYED_CHUNKS; i++) {
        currently_displayed_chunks[i] = new Chunk();
        currently_displayed_chunks[i]->world_instance = this;
        currently_displayed_chunks[i]->chunk_position = curr_chunks_index[i];
        currently_displayed_chunks[i]->initChunk();
    }

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
    // for (int i = 0; i < DISPLAYED_CHUNKS; i++) {
    //     currently_displayed_chunks[i]->drawChunk(Model_Uniform);
    // }

    debug_chunk->drawChunk(Model_Uniform);
}

void World::updateWorld(){

    // posizione del giocatore relativa alla mappa
    vec2 player_position_to_map = vec2(mainCamera.ViewSetup.position.x, mainCamera.ViewSetup.position.z);
    
    player_in_main_chunk = 
    (debug_chunk->chunk_position.x * CHUNK_SIZE * UNIT_SIZE <= player_position_to_map.x) 
    && ((debug_chunk->chunk_position.x + 1) * CHUNK_SIZE * UNIT_SIZE >= player_position_to_map.x)
    && (debug_chunk->chunk_position.y * CHUNK_SIZE * UNIT_SIZE <= player_position_to_map.y) 
    && ((debug_chunk->chunk_position.y + 1) * CHUNK_SIZE * UNIT_SIZE >= player_position_to_map.y);

    cout << "in chunk: " <<  player_in_main_chunk << endl;

    if (!player_in_main_chunk) {
        // si salva la direzione in cui il giocatore si è spostato dal chunk
        int i = !(debug_chunk->chunk_position.x * CHUNK_SIZE * UNIT_SIZE <= player_position_to_map.x) * -1 +
        !((debug_chunk->chunk_position.x + 1) * CHUNK_SIZE * UNIT_SIZE >= player_position_to_map.x);
        int j = !(debug_chunk->chunk_position.y * CHUNK_SIZE * UNIT_SIZE <= player_position_to_map.y) * -1 +
        !((debug_chunk->chunk_position.y + 1) * CHUNK_SIZE * UNIT_SIZE >= player_position_to_map.y);

        cout << "CHANGED CHUNK! to " << i << ", " << j << endl; 

        debug_chunk->translateChunkInWorld(ivec2(i, j));
    }

    if (debug_chunk->map_out_of_bounds) {
        cout << "OUT_OF_BOUNDS ERROR!!" << endl;
    }

    debug_chunk->updateChunk();
    cout << "chunk_position: " << debug_chunk->chunk_position.x << ", " << debug_chunk->chunk_position.y << endl; 
}