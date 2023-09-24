#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

#include "Camera.h"
#include "Lib.h"

// rotates camera using the keyboard
void rotateCameraKeyboard(int x, int y);
// rotates camera using mouse
void rotateCamera(int xpos, int ypos);

void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

#endif