#include "include/EventHandler.h"

extern Camera mainCamera;
extern mat4 Projection;

void framebuffer_size_callback(GLFWwindow* window, int width, int height) //when windows is resized, call this function
{
    glViewport(0, 0, width, height);    //window size
	mainCamera.PerspectiveSetup.aspect = (GLfloat) width / (GLfloat) height;
	Projection = perspective(radians(mainCamera.PerspectiveSetup.fovY), mainCamera.PerspectiveSetup.aspect, mainCamera.PerspectiveSetup.near_plane, mainCamera.PerspectiveSetup.far_plane);
}