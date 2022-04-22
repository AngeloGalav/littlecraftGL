#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

#include "Camera.h"
#include "Lib.h"

void keyboardPressedEvent(unsigned char key, int x, int y);
void mouse(int button, int state, int x, int y);
void my_passive_mouse(int xpos, int ypos);

#endif
 