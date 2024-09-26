#pragma once

// https://www.raylib.com/examples/core/loader.html?name=core_3d_camera_first_person

#include <raylib.h>

// typedef struct {
//     float A;
//     float B;
//     float C;
//     float D;
// } Plane;


// position is array bc is ray_origin
Camera3D camera_create(Vector3 target, float position[3]);

void camera_update(Camera3D* camera);

// toggle between free and perspective modes
void camera_toggle_mode();
