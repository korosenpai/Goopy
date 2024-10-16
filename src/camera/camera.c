#include "camera.h"

#include <raylib.h>
#include <raymath.h>

static int _camera_mode = STILL;

Camera3D camera_create(Vector3 target, float position[3]) {
    return (Camera3D) {
        .up = (Vector3){ 0.0f, 1.0f, 0.0f },
        .target = target,
        .position = (Vector3) { position[0], position[1], position[2] },
        .fovy = 45.0f,
        .projection = STILL,
    };
}

void camera_update(Camera3D* camera) {
    UpdateCamera(camera, _camera_mode);
}

void camera_toggle_mode() {
    _camera_mode = _camera_mode == STILL ? FREE : STILL;

    if (_camera_mode == STILL) {
        EnableCursor();
        SetMousePosition(GetScreenWidth() / 2, GetScreenHeight() / 2);
    }
    else DisableCursor();

}


void camera_update_quaternion(Camera3D* camera, float quaternion_out[4]) {

    Quaternion q = QuaternionFromMatrix(MatrixTranspose(GetCameraMatrix(*camera)));
    quaternion_out[0] = q.x;
    quaternion_out[1] = q.y;
    quaternion_out[2] = q.z;
    quaternion_out[3] = q.w;
}
