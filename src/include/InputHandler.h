#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

#include "Camera.h"
#include "Lib.h"

void processInput(GLFWwindow *window);
void mouse_callback(GLFWwindow *window, double xposIn, double yposIn);
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);

#endif