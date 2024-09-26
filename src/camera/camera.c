#include "camera.h"

#include <math.h>
#include <raylib.h>
#include <raymath.h>

// only modes supported
typedef enum {
    PERSPECTIVE = CAMERA_PERSPECTIVE,
    FREE = CAMERA_FREE,
} CameraModes;

static int _camera_mode = PERSPECTIVE;

Camera3D camera_create(Vector3 target, float position[3]) {
    return (Camera3D) {
        .up = (Vector3){ 0.0f, 1.0f, 0.0f },
        .target = target,
        .position = (Vector3) { position[0], position[1], position[2] },
        .fovy = 45.0f,
        .projection = PERSPECTIVE,
    };
}

void camera_update(Camera3D* camera) {
    UpdateCamera(camera, _camera_mode);
}

void camera_toggle_mode() {
    _camera_mode = _camera_mode == PERSPECTIVE ? FREE : PERSPECTIVE;

    if (_camera_mode == PERSPECTIVE) EnableCursor();
    else DisableCursor();

}


// TODO: ?
// https://adrianb.io/2016/10/01/raymarching.html
// Matrix camera_get_frustum_corners(Camera* camera) {
//     float fov = camera->fovy;
//     float aspect_ratio = (float)GetScreenWidth() / (float)GetScreenHeight();
// 
//     Matrix frustumCorners = MatrixIdentity();
// 
//     float fov_half = fov * 0.5f;
// 
//     float tan_fov = tanf(fov_half * DEG2RAD);
// 
//     // Vector3 toRight = Vector3Scale((Vector3){1, 0, 0}, tan_fov * aspect_ratio);
//     // Vector3 toTop = Vector3Scale((Vector3){0, 1, 0}, tan_fov);
// 
//     // Vector3 topLeft = Vector3Add((Vector3){-1, 0, 1}, toTop);
//     // Vector3 topRight = ;
//     // Vector3 bottomRight = (-Vector3.forward + toRight - toTop);
//     // Vector3 bottomLeft = (-Vector3.forward - toRight - toTop);
// 
//     // frustumCorners.SetRow(0, topLeft);
//     // frustumCorners.SetRow(1, topRight);
//     // frustumCorners.SetRow(2, bottomRight);
//     // frustumCorners.SetRow(3, bottomLeft);
// 
//     return frustumCorners;
// }
