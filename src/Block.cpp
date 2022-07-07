#include "include/Block.h"


Block::Block() : Cube(){
    
}

Block::Block(vec2 *atlas_offset_){
    for (int i = 0; i < 3; i++) {
        atlas_offset[i] = atlas_offset_[i];
    }
}

void Block::draw(int ModelUniform){
    drawMesh(ModelUniform);
}