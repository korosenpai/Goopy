#include "camera.h"

#include <raymath.h>

void camera_move(Camera3D* camera, Vector3 dir) {
    camera->position = Vector3Add(camera->position, dir);
    camera->target = Vector3Add(camera->target, dir);
}
