// when create and edit tab to edit and add obj to the scene

#pragma once

#include "objects.h"

typedef enum {
    EDIT,
    CREATE,
} ObjEditModes;
#define OBJ_EDIT_MODE_STRING "Edit;Create"

void modifier_create_object(OBJ_TYPE* obj_type);
