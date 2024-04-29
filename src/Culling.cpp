#include "include/Culling.h"

using namespace glm;

struct Plane
{
    // unit vector
    glm::vec3 normal = { 0.f, 1.f, 0.f };

    // distance from origin to the nearest point in the plane
    float distance = 0.f;
};

struct Frustum
{
    Plane topFace;
    Plane bottomFace;

    Plane rightFace;
    Plane leftFace;

    Plane farFace;
    Plane nearFace;
};

// Frustum createFrustumFromCamera(const Camera& cam, float aspect, float fovY,
//                                                                 float zNear, float zFar)
// {
//     Frustum     frustum;
//     const float halfVSide = zFar * tanf(fovY * .5f);
//     const float halfHSide = halfVSide * aspect;
//     const glm::vec3 frontMultFar = zFar * cam.Front;

//     frustum.nearFace = { cam.ViewSetup.position + zNear * cam.Front, cam.Front };
//     frustum.farFace = { cam.ViewSetup.position + frontMultFar, -cam.Front };
//     frustum.rightFace = { cam.ViewSetup.position,
//                             glm::cross(frontMultFar - cam.Right * halfHSide, cam.ViewSetup.upVector) };
//     frustum.leftFace = { cam.ViewSetup.position,
//                             glm::cross(cam.ViewSetup.upVector,frontMultFar + cam.Right * halfHSide) };
//     frustum.topFace = { cam.ViewSetup.position,
//                             glm::cross(cam.Right, frontMultFar - cam.ViewSetup.upVector * halfVSide) };
//     frustum.bottomFace = { cam.ViewSetup.position,
//                             glm::cross(frontMultFar + cam.ViewSetup.upVector * halfVSide, cam.Right) };

//     return frustum;
// }