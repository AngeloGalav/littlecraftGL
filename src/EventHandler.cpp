#include "include/EventHandler.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height) //when windows is resized, call this function
{
    glViewport(0, 0, width, height);    //window size
}