#pragma once

#include <raylib.h>

typedef struct {
    float A;
    float B;
    float C;
    float D;
} Plane;

// https://www.raylib.com/examples/core/loader.html?name=core_3d_camera_first_person
//
void camera_move(Camera3D* camera, Vector3 dir);

Matrix camera_get_frustum_corners(Camera* camera);
