#include "collisions.h"
#include <raylib.h>


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

