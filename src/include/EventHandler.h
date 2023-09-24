#ifndef EVENT_HANDLER_H
#define EVENT_HANDLER_H

#include "Camera.h"
#include "Lib.h"

void update(int a);
void resize(int w, int h);
//when windows is resized, call this function
void framebuffer_size_callback(GLFWwindow* window, int width, int height);


#endif