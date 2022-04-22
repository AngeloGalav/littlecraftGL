#ifndef RAYCAST_H
#define RAYCAST_H
#include "Lib.h"
#include "definitions.h"

class Raycaster {
public:
    vec3 get_ray_from_mouse(float mouse_x, float mouse_y);
    bool ray_sphere(vec3 ray_origin_wor, vec3 ray_direction_wor, vec3 sphere_centre_wor, float sphere_radius, float* intersection_distance);
};

#endif