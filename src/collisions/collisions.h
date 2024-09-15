#pragma once 

#include <raylib.h>
#include "../objects/objects.h"

// https://www.raylib.com/examples/models/loader.html?name=models_mesh_picking hit object

// position is center of parent obj, to know where axis is in global coords
BoundingBox get_axis_bounding_box(Axis* axis, Vector3 position);

RayCollision get_ray_collision_axis(Ray* ray, Axis* axis);
// RayCollision get_ray_collision_cube(Ray* ray, Cube* cube);
