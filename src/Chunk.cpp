#include "include/Chunk.h"

Chunk::Chunk() {}

void Chunk::initChunk(){
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

				///!!! ATTENZIONE A QUESTA RIGA !! POTREBBE ESSERE LA CAUSA DI UN PROBLEMA FUTURO
				// CON LA POSIZIONE DEI CHUNK
				// chunk_blocks[i][j][k].moveTo(vec3(i, k, j));
				chunk_blocks[i][j][k].moveTo(vec3(i-10, - 2 - k - world_instance->noiseData[i][j], j-10));
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
		(chunk_blocks[i][j][k].position.y > chunk_blocks[i-1][j][k].position.y)
		&& (chunk_blocks[i][j][k].position.y > chunk_blocks[i-1][j][1].position.y);
	}
	if (i < CHUNK_SIZE - 1) {
		chunk_blocks[i][j][k].must_be_drawn[Right] =
		(chunk_blocks[i][j][k].position.y > chunk_blocks[i+1][j][k].position.y)
		&& (chunk_blocks[i][j][k].position.y > chunk_blocks[i+1][j][1].position.y);
	}

	if (j > 0) {
		chunk_blocks[i][j][k].must_be_drawn[Back] =
		(chunk_blocks[i][j][k].position.y > chunk_blocks[i][j-1][k].position.y)
		&& (chunk_blocks[i][j][k].position.y > chunk_blocks[i][j-1][1].position.y);
	}

	if (j < CHUNK_SIZE - 1) {
		chunk_blocks[i][j][k].must_be_drawn[Front] =
		(chunk_blocks[i][j][k].position.y > chunk_blocks[i][j+1][k].position.y)
		&& (chunk_blocks[i][j][k].position.y > chunk_blocks[i][j+1][1].position.y);
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