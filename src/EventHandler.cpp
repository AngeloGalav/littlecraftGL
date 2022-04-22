#include "include/EventHandler.h"

extern Camera mainCamera;
extern mat4 Projection;

void update(int a)
{
	glutTimerFunc(10, update, 0);
	glutPostRedisplay();
}

void resize(int w, int h)
{
	glViewport(0, 0, w, h);
	mainCamera.PerspectiveSetup.aspect = (GLfloat)w / (GLfloat)h;
	Projection = perspective(radians(mainCamera.PerspectiveSetup.fovY), mainCamera.PerspectiveSetup.aspect, mainCamera.PerspectiveSetup.near_plane, mainCamera.PerspectiveSetup.far_plane);
}