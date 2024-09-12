#include "geometry.h"
#include <raylib.h>


Vector2 geometry_project_3d_to_2d(Vector3* pos, Camera3D* camera) {
    Matrix projection_matrix = GetCameraMatrix(*camera);
    // multiply point with matrix projection for every point
    Vector2 p = {0};

    return p;
}

