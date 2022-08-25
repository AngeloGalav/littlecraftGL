#include "include/Chunk.h"

Chunk::Chunk() {}

void Chunk::initChunk(){
    for (int i = 0; i < CHUNK_SIZE; i++) {
		for (int j = 0; j < CHUNK_SIZE; j++) {
			for (int k = 0; k < 1; k++) {
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
				chunk_blocks[i][j][k].moveTo(vec3(i-10,-2-k,j-10));
			}
		}
	}
}

void Chunk::updateChunk(){

}


void Chunk::drawChunk(int Model_Uniform){
    for (int i = 0; i < CHUNK_SIZE; i++) {
		for (int j = 0; j < CHUNK_SIZE; j++) {
			for (int k = 0; k < 1; k++) {
				chunk_blocks[i][j][k].drawMesh(Model_Uniform);
			}
		}
	}
}

/** Checks for neighbouring cubes, and avoids drawing faces that 
 *  arent visible based on that.  
 */
void Chunk::checkNeighbours(){

}

void Chunk::chunkIndexToPosition(){

}