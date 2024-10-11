#pragma once

// https://www.raylib.com/examples/core/loader.html?name=core_3d_camera_first_person

#include <raylib.h>


// only modes supported
typedef enum {
    STILL = CAMERA_PERSPECTIVE,
    FREE = CAMERA_FREE,
} CameraModes;
#define CAMERA_MODE_STRING "Edit;Free roam"


// position is array bc is ray_origin
Camera3D camera_create(Vector3 target, float position[3]);

void camera_update(Camera3D* camera);

// toggle between still and free mode
void camera_toggle_mode();

void camera_update_quaternion(Camera3D* camera, float quaternion[4]);
