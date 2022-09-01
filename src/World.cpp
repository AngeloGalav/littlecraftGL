#include "include/World.h"
#include <iostream>

#define chunk_index(x,y) (x + CHUNK_SIZE*y)

extern Camera mainCamera;
extern Cube look_cube;

World::World(){
    player_in_main_chunk = false;

    for (int i = 0; i < WORLD_SIZE; i++) {
        for (int j = 0; j < WORLD_SIZE; j++) {
            modified_chunks[i][j] = NULL;
        }
    }

    Gizmos.look_cube = new Cube(vec4(0, 1.0f, 0, 0.5f));
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

    Gizmos.can_draw_lc = true;
    Gizmos.remove_mode = false;

    handleFacesBetweenChunks();

    Gizmos.look_cube->initCube();
    Gizmos.lc_chunk_position = ivec2(0, 0);
    Gizmos.lc_prev_position = look_cube.position;
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

void World::UpdateGizmos(){
   	vec3 lk_position = raycast.get_ray_from_camera(mainCamera);
	look_cube.moveTo(vec3(mainCamera.ViewSetup.position.x/UNIT_SIZE, 
	mainCamera.ViewSetup.position.y/UNIT_SIZE, mainCamera.ViewSetup.position.z/UNIT_SIZE) 
	+ vec3(DISTANCE_FROM_CAMERA * lk_position.x, DISTANCE_FROM_CAMERA * lk_position.y, DISTANCE_FROM_CAMERA * lk_position.z));
}

void World::drawGizmos(int MatModel){
    if (Gizmos.can_draw_lc)
		look_cube.drawMesh(MatModel);
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

    if (look_cube.position.x == Gizmos.lc_prev_position.x &&  look_cube.position.y == Gizmos.lc_prev_position.y 
    && look_cube.position.z == Gizmos.lc_prev_position.z) {
        int i = !(currently_displayed_chunks[Center]->chunk_position.x * CHUNK_SIZE <= look_cube.position.x) * -1 +
        !((currently_displayed_chunks[Center]->chunk_position.x + 1) * CHUNK_SIZE >= look_cube.position.x);

        int j = !(currently_displayed_chunks[Center]->chunk_position.y * CHUNK_SIZE <= look_cube.position.z) * -1 +
        !((currently_displayed_chunks[Center]->chunk_position.y + 1) * CHUNK_SIZE >= look_cube.position.z);

        Gizmos.lc_chunk_position += ivec2(i, j);
    }
    
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

        // update chunk
        for (int i = 0; i < DISPLAYED_CHUNKS; i++) {
            currently_displayed_chunks[i]->updateChunk();
        }

        handleFacesBetweenChunks();        
    }
}