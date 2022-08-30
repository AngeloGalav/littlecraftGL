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
}

void World::initWorld(){
    initNoise();

    for (int i = 0; i < DISPLAYED_CHUNKS; i++) {
        currently_displayed_chunks[i] = new Chunk();
        currently_displayed_chunks[i]->world_instance = this;
        currently_displayed_chunks[i]->chunk_position = curr_chunks_index[i];
        currently_displayed_chunks[i]->initChunk();
    }

    for (int i = 0; i < DISPLAYED_CHUNKS; i++) {
        cout << "init_positions" << i << ": " << currently_displayed_chunks[i]->chunk_position.x 
        << ", " << currently_displayed_chunks[i]->chunk_position.y << endl;
    }

    handleFacesBetweenChunks();
}



void World::handleFacesBetweenChunks(){
    int row_length = sqrt(DISPLAYED_CHUNKS);
    for (int i = 0; i < DISPLAYED_CHUNKS - 1; i++) {
        if ((i + 1) % row_length != 0 && (DISPLAYED_CHUNKS - row_length) > i) {
            currently_displayed_chunks[i]->checkNeighbouringChunk(currently_displayed_chunks[i + 1], true);
            currently_displayed_chunks[i]->checkNeighbouringChunk(currently_displayed_chunks[i + row_length], false);
        } else if ((DISPLAYED_CHUNKS - row_length) > i && (i + 1) % row_length == 0) {
            currently_displayed_chunks[i]->checkNeighbouringChunk(currently_displayed_chunks[i + row_length], false);
        } else if ((DISPLAYED_CHUNKS - row_length) <= i && (i + 1) % row_length != 0) {
            currently_displayed_chunks[i]->checkNeighbouringChunk(currently_displayed_chunks[i + 1], true);
        }

    }
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
    for (int i = 0; i < DISPLAYED_CHUNKS; i++) {
        currently_displayed_chunks[i]->drawChunk(Model_Uniform);
    }
}

void World::updateWorld(){

    // posizione del giocatore relativa alla mappa
    vec2 player_position_to_map = vec2(mainCamera.ViewSetup.position.x, mainCamera.ViewSetup.position.z);
    // solves
    player_in_main_chunk = 
    (currently_displayed_chunks[Center]->chunk_position.x * CHUNK_SIZE * UNIT_SIZE <= player_position_to_map.x) 
    && ((currently_displayed_chunks[Center]->chunk_position.x + 1) * CHUNK_SIZE * UNIT_SIZE >= player_position_to_map.x)
    && (currently_displayed_chunks[Center]->chunk_position.y * CHUNK_SIZE * UNIT_SIZE <= player_position_to_map.y) 
    && ((currently_displayed_chunks[Center]->chunk_position.y + 1) * CHUNK_SIZE * UNIT_SIZE >= player_position_to_map.y);

    // cout << "in chunk: " <<  player_in_main_chunk << endl;

    if (!player_in_main_chunk) {
        // si salva la direzione in cui il giocatore si è spostato dal chunk
        int i = !(currently_displayed_chunks[Center]->chunk_position.x * CHUNK_SIZE * UNIT_SIZE <= player_position_to_map.x) * -1 +
        !((currently_displayed_chunks[Center]->chunk_position.x + 1) * CHUNK_SIZE * UNIT_SIZE >= player_position_to_map.x);
        int j = !(currently_displayed_chunks[Center]->chunk_position.y * CHUNK_SIZE * UNIT_SIZE <= player_position_to_map.y) * -1 +
        !((currently_displayed_chunks[Center]->chunk_position.y + 1) * CHUNK_SIZE * UNIT_SIZE >= player_position_to_map.y);


        // debug_chunk->translateChunkInWorld(ivec2(i, j));
        for (int k = 0; k < DISPLAYED_CHUNKS; k++) {
            currently_displayed_chunks[k]->translateChunkInWorld(ivec2(i, j));
        }

        cout << "CHANGED CHUNK! to " << i << ", " << j << endl; 
        cout << "main_chunk_pos: " << currently_displayed_chunks[Center]->chunk_position.x 
            << ", " << currently_displayed_chunks[Center]->chunk_position.y << endl;

        for (int i = 0; i < DISPLAYED_CHUNKS; i++) {
            cout << "positions: " << currently_displayed_chunks[i]->chunk_position.x 
            << ", " << currently_displayed_chunks[i]->chunk_position.y << endl;
        }

        // update chunk
        for (int i = 0; i < DISPLAYED_CHUNKS; i++) {
            currently_displayed_chunks[i]->updateChunk();
        }

        handleFacesBetweenChunks();        
    }

    // if (currently_displayed_chunks[Center]->map_out_of_bounds) {
    //     cout << "OUT_OF_BOUNDS ERROR!!" << endl;
    // }

    // cout << "chunk_position: " << currently_displayed_chunks[Center]->chunk_position.x << ", " << currently_displayed_chunks[Center]->chunk_position.y << endl; 
}