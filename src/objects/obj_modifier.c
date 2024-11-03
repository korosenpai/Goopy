#include "obj_modifier.h"
#include "objects.h"

#include <raymath.h>
#include <stdio.h>

// NOTE: implement in ui to change
#define DEFAULT_OBJ_PLACING_DISTANCE 5.0

Object modifier_create_object(Ray* mouse_ray, OBJ_TYPE* obj_type, float* obj_placing_dist) {
    // if it remains like this something has gone wong
    Object res;

    Vector3 placing_pos = Vector3Add(
        mouse_ray->position, 
        Vector3Scale(mouse_ray->direction, *obj_placing_dist)
    );

    switch (*obj_type) {
        case SPHERE:
            res = sphere_create(placing_pos, SPHERE_DEFAULT_RADIUS, OBJ_DEFAULT_COLOR);
            break;

        case CUBE:
            res = cube_create(placing_pos, CUBE_DEFAULT_SIZE, CUBE_DEFAULT_SIZE, CUBE_DEFAULT_SIZE, OBJ_DEFAULT_COLOR);
            break;
        case OCTAHEDRON:
            printf("obj not implemented.\n");
            break;
        case CAPSULE:
            printf("obj not implemented.\n");
            break;
        case CYLINDER:
            printf("obj not implemented.\n");
            break;
        case TORUS:
            printf("obj not implemented.\n");
            break;
        case ELLIPSOID:
            printf("obj not implemented.\n");
            break;

        default: // then goes to create none
            printf("OBJ NOT FOUND!!!!!\n");
        case OBJECT_NONE: 
            res = obj_none_create();
            break;
    }
    return res;
}
