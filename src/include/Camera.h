#ifndef CAMERA_H
#define CAMERA_H
#include "Lib.h"

extern int width, height;
using namespace glm;

class Camera {
public:
    struct {
        vec4 position;
        vec4 target; // target is always position + direction
        vec4 upVector;
        vec4 direction;
    } ViewSetup; // camera setup

    struct {
        vec3 cameraPos;
        vec3 cameraUp;
        vec3 cameraRigh;
        vec3 cameraForward;
    } ExtendedViewSetup;


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
    vec3 get_ray_from_camera();

    //constructor
    Camera();
};


#endif