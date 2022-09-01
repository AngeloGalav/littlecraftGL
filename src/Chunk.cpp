#include "include/Chunk.h"
#include <iostream>

Chunk::Chunk() {
	chunk_position = ivec2(0,0);
}

Chunk::~Chunk() {}

void Chunk::initChunk(){
	dirty = false;
	to_move = false;
	map_out_of_bounds = false;

    for (int i = 0; i < CHUNK_SIZE; i++) {
		for (int j = 0; j < CHUNK_SIZE; j++) {
			for (int k = 0; k < CHUNK_HEIGHT; k++) {
                // setting cube texture offsets
				if (k == 0) {
					chunk_blocks[i][j][k].atlas_offset[0] = vec2(0, 15);
					chunk_blocks[i][j][k].atlas_offset[1] = vec2(2, 15);
					chunk_blocks[i][j][k].atlas_offset[2] = vec2(3, 15);
				} else if (k > 0 && k < 4) {
					chunk_blocks[i][j][k].atlas_offset[0] = 
					chunk_blocks[i][j][k].atlas_offset[1] = 
					chunk_blocks[i][j][k].atlas_offset[2] = vec2(2, 15);
				} else {
					chunk_blocks[i][j][k].atlas_offset[0] = 
					chunk_blocks[i][j][k].atlas_offset[1] = 
					chunk_blocks[i][j][k].atlas_offset[2] = vec2(1, 15);
				}
				chunk_blocks[i][j][k].initCubeTextures(); //le textures sono già state inizializ. dal costruttore
				chunk_blocks[i][j][k].initCube();
				for (int d = 0; d < 6; d++)	chunk_blocks[i][j][k].must_be_drawn[d] = false;

				applyChunkPosition(i, j, k);	
			}
		}
	}

	// dobbiamo farlo in un for separato siccome così abbiamo tutte le 
	// posizioni "riempite"
	for (int i = 0; i < CHUNK_SIZE; i++) {
		for (int j = 0; j < CHUNK_SIZE; j++) {
			for (int k = 0; k < CHUNK_HEIGHT; k++) {
				checkNeighbours(i,j,k);
			}
		}
	}
}

void Chunk::updateChunk(){

	// aggiorna il chunk se è cambiata posizione
	if (to_move && !map_out_of_bounds) {
		for (int i = 0; i < CHUNK_SIZE; i++) {
			for (int j = 0; j < CHUNK_SIZE; j++) {
				for (int k = 0; k < CHUNK_HEIGHT; k++) {
					
					map_out_of_bounds = 
					(i + (chunk_position.x + WORLD_SIZE/2) * CHUNK_SIZE) <= -1 || 
					(j + (chunk_position.y + WORLD_SIZE/2) * CHUNK_SIZE) <= -1 || 
					(i + (chunk_position.x + WORLD_SIZE/2) * CHUNK_SIZE) >= WORLD_SIZE*CHUNK_SIZE ||
					(j + (chunk_position.y + WORLD_SIZE/2) * CHUNK_SIZE) >= WORLD_SIZE*CHUNK_SIZE;
			
					if (!map_out_of_bounds) applyChunkPosition(i, j, k);
				}
			}
		}

		for (int i = 0; i < CHUNK_SIZE; i++) {
			for (int j = 0; j < CHUNK_SIZE; j++) {
				for (int k = 0; k < CHUNK_HEIGHT; k++) {
					checkNeighbours(i,j,k);
				}
			}
		}
		to_move = false;
	}

	if (dirty) {
		// code for dirty chunk management herw
		dirty = false;
	}

}

void Chunk::applyChunkPosition(int i, int j, int k) {
	chunk_blocks[i][j][k].moveTo(
	vec3(i + CHUNK_SIZE * chunk_position.x,
	- 2 - k - world_instance->noiseData
	[i + (chunk_position.x + WORLD_SIZE/2) * CHUNK_SIZE] 
	[j + (chunk_position.y + WORLD_SIZE/2) * CHUNK_SIZE], 
	j + CHUNK_SIZE * chunk_position.y));
}


void Chunk::drawChunk(int Model_Uniform){
    for (int i = 0; i < CHUNK_SIZE; i++) {
		for (int j = 0; j < CHUNK_SIZE; j++) {
			for (int k = 0; k < CHUNK_HEIGHT; k++) {
				chunk_blocks[i][j][k].drawMesh(Model_Uniform);
			}
		}
	}
}

/** Checks for neighbouring cubes, and avoids drawing faces that 
 *  arent visible based on that.  
 */
void Chunk::checkNeighbours(int i, int j, int k){

	// la faccia di sopra viene disegnata solo se è il primo strato visibile (di base)
	chunk_blocks[i][j][k].must_be_drawn[Up] = (k == 0);
	chunk_blocks[i][j][k].must_be_drawn[Down] = false;

	// Controlla i vicini. Se sono più alti dei vicini, allora devo disegnare quella faccia
	// (questo siccome semplicemente non abbiamo caverne, sennò la cosa diventava più complessa) 
	if (i > 0) {
		chunk_blocks[i][j][k].must_be_drawn[Left] =
		(chunk_blocks[i][j][k].position.y > chunk_blocks[i-1][j][0].position.y);
	}

	if (i < CHUNK_SIZE - 1) {
		chunk_blocks[i][j][k].must_be_drawn[Right] =
		(chunk_blocks[i][j][k].position.y > chunk_blocks[i+1][j][0].position.y);
	}

	if (j > 0) {
		chunk_blocks[i][j][k].must_be_drawn[Back] =
		(chunk_blocks[i][j][k].position.y > chunk_blocks[i][j-1][0].position.y);
	}

	if (j < CHUNK_SIZE - 1) {
		chunk_blocks[i][j][k].must_be_drawn[Front] =
		(chunk_blocks[i][j][k].position.y > chunk_blocks[i][j+1][0].position.y);
	}
}

void Chunk::translateChunk(ivec3 vector){
	for (int i = 0; i < CHUNK_SIZE; i++) {
		for (int j = 0; j < CHUNK_SIZE; j++) {
			for (int k = 0; k < CHUNK_HEIGHT; k++) {
				chunk_blocks[i][j][k].translateCube(vector);
			}
		}
	}
}

/** Moves chunk to a new position in the world. 
 * 	So, it is equivalent to a translation in world map coordinates (aka between 0 and WORLD_SIZE)
 */
void Chunk::translateChunkInWorld(ivec2 vector){
	if (!map_out_of_bounds) {
		chunk_position += ivec2(vector.x, vector.y);
		to_move = true;	
	}
}

/**
 * @brief same as checkneighbour(), but it is used to perform the check between the chunks. 
 * 
 * 
 * @param neighbour the neighbouring chunk
 * @param checkHorizontal if true, the check is performaned as if the neigh. was to the right, 
 * otherwise performs the check as if the neighbour was to the bottom. s
 */
void Chunk::checkNeighbouringChunk(Chunk* neighbour, bool checkHorizontal){
	
	if (checkHorizontal) {
		for (int y = 0; y < CHUNK_SIZE; y++) {
			for (int z = 0; z < CHUNK_HEIGHT; z++) {
				chunk_blocks[CHUNK_SIZE - 1][y][z].must_be_drawn[Right] =
				(chunk_blocks[CHUNK_SIZE - 1][y][z].position.y > neighbour->chunk_blocks[0][y][0].position.y);

				neighbour->chunk_blocks[0][y][z].must_be_drawn[Left] =
				(neighbour->chunk_blocks[0][y][z].position.y > chunk_blocks[CHUNK_SIZE - 1][y][0].position.y);
			}
		}
	} else {
		for (int x = 0; x < CHUNK_SIZE; x++) {
			for (int z = 0; z < CHUNK_HEIGHT; z++) {
				chunk_blocks[x][CHUNK_SIZE - 1][z].must_be_drawn[Front] =
				(chunk_blocks[x][CHUNK_SIZE - 1][z].position.y > neighbour->chunk_blocks[x][0][0].position.y);

				neighbour->chunk_blocks[x][0][z].must_be_drawn[Back] =
				(neighbour->chunk_blocks[x][0][z].position.y > chunk_blocks[x][CHUNK_SIZE - 1][0].position.y);
			}
		}
	}

}

/** Adds a specific block in defined position
 * 
 */
void Chunk::addBlockToChunk(ivec3 position, Block block_added){

	Block* new_block = new Block();
	
	for (int i = 0; i < 3; i++)
		new_block->atlas_offset[i] = block_added.atlas_offset[i];

	int i = position.x;
	int j = position.y; 

	int k = - 2 - position.z - world_instance->noiseData
	[i + (chunk_position.x + WORLD_SIZE/2) * CHUNK_SIZE] 
	[j + (chunk_position.y + WORLD_SIZE/2) * CHUNK_SIZE];
}

/** Removes a block in specified position
 * 
 */
void Chunk::removeBlockFromChunk(ivec3 position){

	int i = position.x;
	int j = position.y; 

	int k = - 2 - position.z - world_instance->noiseData
	[i + (chunk_position.x + WORLD_SIZE/2) * CHUNK_SIZE] 
	[j + (chunk_position.y + WORLD_SIZE/2) * CHUNK_SIZE];

	chunk_blocks[position.x][position.y][k].isAir = true;
	
	if (i > 0) {
		chunk_blocks[i-1][j][k].must_be_drawn[Left] = true;
	}

	if (i < CHUNK_SIZE - 1) {
		chunk_blocks[i+1][j][k].must_be_drawn[Right] = true;
	}

	if (j > 0) {
		chunk_blocks[i][j-1][k].must_be_drawn[Back] = true;
	}

	if (j < CHUNK_SIZE - 1) {
		chunk_blocks[i][j+1][k].must_be_drawn[Front] = true;
	}

	if (k > 0) {
		chunk_blocks[i][j][k-1].must_be_drawn[Down] = true;
	}

	if (k < CHUNK_HEIGHT - 1) {
		chunk_blocks[i][j][k+1].must_be_drawn[Up] = true;
	}

}