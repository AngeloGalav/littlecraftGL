#include "include/Block.h"

Block::Block() : Cube(){}

Block::Block(vec2 *atlas_offset_){
    for (int i = 0; i < 3; i++) {
        atlas_offset[i] = atlas_offset_[i];
    }
}

void Block::initCube(){
    faces[0].crea_VAO_Vector_textures();
	faces[0].Model = mat4(1.0);
	faces[0].Model = scale(faces[0].Model, vec3(2.0f, 2.0f, 2.0f));
	faces[0].Model = translate(faces[0].Model, vec3(0.0f, 0.0f, 1.0f));

	faces[1].crea_VAO_Vector_textures();
	faces[1].Model = mat4(1.0);
	faces[1].Model = scale(faces[1].Model, vec3(2.0f, 2.0f, 2.0f));
	faces[1].Model = translate(faces[1].Model, vec3(1.0f, 0.0, 0.0f));
	faces[1].Model = rotate(faces[1].Model, radians(-90.0f), vec3(0, 1, 0));

	faces[2].crea_VAO_Vector_textures();
	faces[2].Model = mat4(1.0);
	faces[2].Model = scale(faces[2].Model, vec3(2.0f, 2.0f, 2.0f));
	faces[2].Model = translate(faces[2].Model, vec3(0.0, 0.0, -1.0f));

	faces[3].crea_VAO_Vector_textures();
	faces[3].Model = mat4(1.0);
	faces[3].Model = scale(faces[3].Model, vec3(2.0f, 2.0f, 2.0f));
	faces[3].Model = translate(faces[3].Model, vec3(-1.0f, 0.0, 0.0f));
	faces[3].Model = rotate(faces[3].Model, radians(90.0f), vec3(0, 1, 0));

	faces[4].crea_VAO_Vector_textures();
	faces[4].Model = mat4(1.0);
	faces[4].Model = scale(faces[4].Model, vec3(2.0f, 2.0f, 2.0f));
	faces[4].Model = translate(faces[4].Model, vec3(0, 1.0f, 0.0f));
	faces[4].Model = rotate(faces[4].Model, radians(90.0f), vec3(1, 0, 0));

	faces[5].crea_VAO_Vector_textures();
	faces[5].Model = mat4(1.0);
	faces[5].Model = scale(faces[5].Model, vec3(2.0f, 2.0f, 2.0f));
	faces[5].Model = translate(faces[5].Model, vec3(0.0, -1.0f, 0.0f));
	faces[5].Model = rotate(faces[5].Model, radians(-90.0f), vec3(1, 0, 0));

	ModelCube = mat4(1.0);
	moveTo(position);
}

void Block::initCubeTextures(){
	// Add texture offsets to all quads of the cube
	for (int i = 0; i < 4; i++){
		faces[i].texture_coords_offset = atlas_offset[2];
	}

	faces[4].texture_coords_offset = atlas_offset[0];
	faces[5].texture_coords_offset = atlas_offset[1];
	for (int i = 0; i < 6; i++)
	{
		if (true) { //TODO: change it to the textureBool
			faces[i].initQuadTexture();
		}
	}
}