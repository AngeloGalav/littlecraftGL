#ifndef TEXT_HANDLER_H
#define TEXT_HANDLER_H

#include "Lib.h"
#include <string>

void Init_Freetype(void);
void RenderText(int Program, mat4 Projection_Text, std::string text, unsigned int VAO_Text, unsigned int VBO_Text,float x, float y, float scale, glm::vec3 color);

#endif