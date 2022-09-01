#ifndef CAMERA_H
#define CAMERA_H
#include "Lib.h"

extern int width, height;

class Camera {
public:
    struct {
        vec4 position;
        vec4 target;
        vec4 upVector;
        vec4 direction;
    } ViewSetup; // camera setup


    vec3 cameraRotation;

    struct {
        float fovY, aspect, near_plane, far_plane;
    } PerspectiveSetup;

    float playerSpeed;

    void moveCameraLeft();
    void moveCameraRight();
    void moveCameraForward();
    void moveCameraBack();
    void initCamera();
    
    //constructor
    Camera();
};


#endif