#include <iostream>

#include "include/Camera.h"
#include "include/Chunk.h"
#include "include/EventHandler.h"
#include "include/FastNoiseLite.h"
#include "include/InputHandler.h"
#include "include/Lib.h"
#include "include/Mesh.h"
#include "include/ShaderMaker.h"
#include "include/Texture.h"
#include "include/definitions.h"

// new code
#include "include/Cube2.h"
#include "include/Chunk2.h"

int width = SCREEN_WIDTH;
int height = SCREEN_HEIGHT;

static unsigned int programId, MatrixProj, MatModel, MatView;
static unsigned int texture_programId, MatrixProj_texture, MatModel_texture,
    MatView_texture;

World main_world;

Texture textureMaker;

// camera
Camera mainCamera(vec3(0.0f, 0.0f, 3.0f));

// timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;

// model matrix
mat4 Model;

//  DEBUG STUFF
Cube test_cube;
NewCube test_cube2;
NewCube test_cube3(glm::vec3(15, -5, 0));
NewChunk test_chunk;

void init(void) {
    char *vertexShader = (char *)"shaders/plain.vert.glsl";
    char *fragmentShader = (char *)"shaders/plain.frag.glsl";
    char *fragmentShader_texture = (char *)"shaders/texture.frag.glsl";
    char *vertexShader_texture = (char *)"shaders/texture.vert.glsl";

    programId = ShaderMaker::createProgram(vertexShader, fragmentShader);
    texture_programId = ShaderMaker::createProgram(vertexShader_texture,
                                                   fragmentShader_texture);
    glUseProgram(programId);

    // inizializza la texture usando il programId dello shader
    textureMaker.initTexture(&texture_programId);

    main_world.initWorld();

    test_cube.initCube(false);
    test_cube.translateCube(ivec3(10, -4, 0));


    // new cube
    test_cube2.init();
    test_cube2.setup();
    test_cube3.init();
    test_cube3.setup();

    // NEW CHUNK
    test_chunk.build();
    test_chunk.setup();
}

void drawScene(GLFWwindow *window) {
    glClearColor(SKY_COLOR);
    glClear(GL_COLOR_BUFFER_BIT |
            GL_DEPTH_BUFFER_BIT);  // GL_DEPTH_BUFFER_BIT risolve il bug dello
                                   // z-indexing su linux

    mainCamera.updateCameraMatrices();

    // draw world
    glUseProgram(texture_programId);
    glUniformMatrix4fv(MatrixProj_texture, 1, GL_FALSE, value_ptr(mainCamera.ProjectionMatrix));
    glUniformMatrix4fv(MatView_texture, 1, GL_FALSE, value_ptr(mainCamera.ViewMatrix));
    // textureMaker.useTexture();
    // main_world.renderWorld(MatModel_texture);
    test_cube3.draw(MatModel);
    test_chunk.draw(MatModel);


    test_cube3.draw(MatModel);
    test_chunk.draw(MatModel);


    // enable blending to draw transparency
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // draw gizmo cube
    glUseProgram(programId);

    glUniformMatrix4fv(MatrixProj, 1, GL_FALSE, value_ptr(mainCamera.ProjectionMatrix));
    glUniformMatrix4fv(MatView, 1, GL_FALSE, value_ptr(mainCamera.ViewMatrix));

    // draw and update gizmo cube (the cube to set other cubes)
    main_world.updateGizmos();
    main_world.drawGizmos(MatModel);
    test_cube.drawMesh(MatModel);

    test_cube2.draw(MatModel);


    // main_world.updateWorld();
}

int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,
                   3);  // this tells us that we are using version 3.3 of glfw
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    GLFWwindow *window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT,
                                          "littleCraft", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    // set as non resizable for now
    glfwSetWindowAttrib(window, GLFW_RESIZABLE, false);
    glfwMakeContextCurrent(window);
    // removes vsync
    glfwSwapInterval(0);
    glfwSetFramebufferSizeCallback(
        window, framebuffer_size_callback);  // calls the function whenever the
                                             // framebuffer size (window size)
                                             // is changed

    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);
    // mouse capture
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    init();

    glEnable(GL_BLEND);

    glEnable(GL_DEPTH_TEST);

    // enables front face culling
    glEnable(GL_CULL_FACE);

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    MatrixProj = glGetUniformLocation(programId, "Projection");
    MatrixProj_texture = glGetUniformLocation(texture_programId, "Projection");

    MatModel = glGetUniformLocation(programId, "Model");
    MatModel_texture = glGetUniformLocation(texture_programId, "Model");

    MatView = glGetUniformLocation(programId, "View");
    MatView_texture = glGetUniformLocation(texture_programId, "View");

    while (!glfwWindowShouldClose(window)) {
        //  frame dependent movement
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        // process input first
        processInput(window);
        drawScene(window);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
}

