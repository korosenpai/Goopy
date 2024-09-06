#include "collisions.h"

BoundingBox get_axis_bounding_box(Axis* axis, Vector3 position) {
    // treat axis as a cube

    float x = axis->offset.x + position.x;
    float y = axis->offset.y + position.y;
    float z = axis->offset.z + position.z;

    return (BoundingBox){
        (Vector3){
            x - axis->width/2,
            y - axis->height/2,
            z - axis->length/2
        },
        (Vector3){
            x + axis->width/2,
            y + axis->height/2,
            z + axis->length/2
        }
    };

}

RayCollision get_ray_collision_cube(Ray* ray, Cube* cube) {
    BoundingBox box = (BoundingBox){
        (Vector3){
            cube->position.x - cube->width/2,
            cube->position.y - cube->height/2,
            cube->position.z - cube->length/2
        },
        (Vector3){
            cube->position.x + cube->width/2,
            cube->position.y + cube->height/2,
            cube->position.z + cube->length/2
        }
    };

    return GetRayCollisionBox(*ray, box);
}

