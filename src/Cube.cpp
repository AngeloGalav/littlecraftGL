#include "include/Cube.h"
#include <iostream>


Cube::Cube(){
    faces[0].quadColor = (vec4(0.0, 1.0f, 0.0, 1.0f));
    faces[0].initQuadWithSingleColor();

    faces[1].quadColor = (vec4(1.0f, 0.0f, 0.0, 1.0f));
    faces[1].initQuadWithSingleColor();

    faces[2].quadColor = (vec4(0.0f, 0.0f, 1.0f, 1.0f));
    faces[2].initQuadWithSingleColor();

    faces[3].quadColor = (vec4(0.0, 1.0f, 1.0f, 1.0f));
    faces[3].initQuadWithSingleColor();
    
    faces[4].quadColor = (vec4(1.0f, 1.0f, 0.0, 1.0f));
    faces[4].initQuadWithSingleColor();
    
    faces[5].quadColor = (vec4(1.0f, 0.0f, 1.0f, 1.0f));
    faces[5].initQuadWithSingleColor();


	position = vec3(0.0, 0.0, 0.0);
}


void Cube::initCube(){
    faces[0].crea_VAO_Vector();
	faces[0].Model = mat4(1.0);
	faces[0].Model = scale(faces[0].Model, vec3(2.0f, 2.0f, 2.0f));
	faces[0].Model = translate(faces[0].Model, vec3(0.0f, 0.0f, 1.0f));

	faces[1].crea_VAO_Vector();
	faces[1].Model = mat4(1.0);
	faces[1].Model = scale(faces[1].Model, vec3(2.0f, 2.0f, 2.0f));
	faces[1].Model = translate(faces[1].Model, vec3(1.0f, 0.0, 0.0f));
	faces[1].Model = rotate(faces[1].Model, radians(-90.0f), vec3(0, 1, 0));

	faces[2].crea_VAO_Vector();
	faces[2].Model = mat4(1.0);
	faces[2].Model = scale(faces[2].Model, vec3(2.0f, 2.0f, 2.0f));
	faces[2].Model = translate(faces[2].Model, vec3(0.0, 0.0, -1.0f));

	faces[3].crea_VAO_Vector();
	faces[3].Model = mat4(1.0);
	faces[3].Model = scale(faces[3].Model, vec3(2.0f, 2.0f, 2.0f));
	faces[3].Model = translate(faces[3].Model, vec3(-1.0f, 0.0, 0.0f));
	faces[3].Model = rotate(faces[3].Model, radians(90.0f), vec3(0, 1, 0));

	faces[4].crea_VAO_Vector();
	faces[4].Model = mat4(1.0);
	faces[4].Model = scale(faces[4].Model, vec3(2.0f, 2.0f, 2.0f));
	faces[4].Model = translate(faces[4].Model, vec3(0, 1.0f, 0.0f));
	faces[4].Model = rotate(faces[4].Model, radians(90.0f), vec3(1, 0, 0));

	faces[5].crea_VAO_Vector();
	faces[5].Model = mat4(1.0);
	faces[5].Model = scale(faces[5].Model, vec3(2.0f, 2.0f, 2.0f));
	faces[5].Model = translate(faces[5].Model, vec3(0.0, -1.0f, 0.0f));
	faces[5].Model = rotate(faces[5].Model, radians(-90.0f), vec3(1, 0, 0));

	ModelCube = mat4(1.0);
	ModelCube = translate(ModelCube, vec3(4.0, 4.0, 4.0));
}

void Cube::drawMesh(int Model_Uniform){


    for (int i = 0; i < 6; i++){
		faces[i].drawMesh(Model_Uniform);
        faces[i].drawMeshDebug(Model_Uniform, ModelCube);
	}
}


void Cube::translateCube(vec3 translate_vector){
	ModelCube = translate(ModelCube, translate_vector);
}

void Cube::moveTo(vec3 position){

}
