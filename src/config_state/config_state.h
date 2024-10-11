#pragma once

#include "../objects/objects.h"
#include "../objects/obj_modifier.h"
#include "../camera/camera.h"

#include <raylib.h>
#include <stdbool.h>


typedef struct {
    OBJ_TYPE selected_shape;
    CameraModes camera_mode;
    ObjEditModes edit_mode;  // NOTE: only useful when camera mode is STILL
} ConfigurationState;

ConfigurationState config_state_create();
