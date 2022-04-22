
#include "include/Quad.h"

Quad::Quad(vec4 color) {
    this->quadColor = color;
    initQuad();
}

void Quad::initQuad(){
    
	vertici.push_back(vec3(-1.0, -1.0, 1.0));
	colori.push_back(vec4(1.0, 0.0, 0.0, 1.0));
	vertici.push_back(vec3(1.0, -1.0, 1.0));
	colori.push_back(vec4(0.0, 1.0, 0.0, 1.0));
	vertici.push_back(vec3(1.0, 1.0, 1.0));
	colori.push_back(vec4(0.0, 0.0, 1.0, 1.0));
	vertici.push_back(vec3(-1.0, 1.0, 1.0));
	colori.push_back(vec4(1.0, 0.0, 1.0, 1.0));

	indici.push_back(0); indici.push_back(1); indici.push_back(2);
	indici.push_back(2); indici.push_back(3); indici.push_back(0);
}





