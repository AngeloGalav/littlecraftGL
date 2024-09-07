#ifndef LIB_H
#define LIB_H

#include <map>
#include <cstddef>
// #include <GL/glew.h>
#include "glad.h"
#include <GLFW/glfw3.h>
#ifdef __linux__ 
    #include <glm/glm.hpp>
    #include <glm/gtc/matrix_transform.hpp>
    #include <glm/gtc/type_ptr.hpp>
#elif _WIN32
    #include <glm.hpp>
    #include <gtc/matrix_transform.hpp>
    #include <gtc/type_ptr.hpp>
#endif
#include <vector>
#include <string>
#include <iostream>

#endif