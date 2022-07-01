#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

#include "Camera.h"
#include "Lib.h"

void keyboardPressedEvent(unsigned char key, int x, int y);
void mouse(int button, int state, int x, int y);
void my_passive_mouse(int xpos, int ypos);
void rotateCamera(int xpos, int ypos);

// handles mouse pressure
void onMouseEvent(int button, int state, int x, int y);

// handles leftMouse event
void onLeftMouseEvent(int x, int y);

// handles rightMouse event
void onRightMouseEvent(int x, int y);
#endif
 