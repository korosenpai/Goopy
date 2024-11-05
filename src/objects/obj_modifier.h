// when create and edit tab to edit and add obj to the scene

#pragma once

#include <raylib.h>
#include "objects.h"

typedef enum {
    EDIT,
    CREATE,
} ObjEditModes;
#define OBJ_EDIT_MODE_STRING "Edit;Create"

#define DEFAULT_OBJ_PLACING_DISTANCE 5.0

Object modifier_create_object(Ray* mouse_ray, OBJ_TYPE* obj_type, float* obj_placing_dist);
