#include "camera.h"

#include <math.h>
#include <raylib.h>
#include <raymath.h>

void camera_move(Camera3D* camera, Vector3 dir) {
    camera->position = Vector3Add(camera->position, dir);
    camera->target = Vector3Add(camera->target, dir);
}


// https://www.phind.com/search?cache=vxi9al5rd7djgj9d51xpnm47
void calculate_camera_frustum(Camera *camera, Vector3 *planes) {

}

// bool is_point_in_frustum(Vector3 *point, Plane *planes) {}


// https://adrianb.io/2016/10/01/raymarching.html
Matrix camera_get_frustum_corners(Camera* camera) {
    float fov = camera->fovy;
    float aspect_ratio = (float)GetScreenWidth() / (float)GetScreenHeight();

    Matrix frustumCorners = MatrixIdentity();

    float fov_half = fov * 0.5f;

    float tan_fov = tanf(fov_half * DEG2RAD);

    // Vector3 toRight = Vector3Scale((Vector3){1, 0, 0}, tan_fov * aspect_ratio);
    // Vector3 toTop = Vector3Scale((Vector3){0, 1, 0}, tan_fov);

    // Vector3 topLeft = Vector3Add((Vector3){-1, 0, 1}, toTop);
    // Vector3 topRight = ;
    // Vector3 bottomRight = (-Vector3.forward + toRight - toTop);
    // Vector3 bottomLeft = (-Vector3.forward - toRight - toTop);

    // frustumCorners.SetRow(0, topLeft);
    // frustumCorners.SetRow(1, topRight);
    // frustumCorners.SetRow(2, bottomRight);
    // frustumCorners.SetRow(3, bottomLeft);

    return frustumCorners;
}
