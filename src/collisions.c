#include "collisions.h"
#include <raylib.h>


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
