#pragma once

#include "../objects/objects.h"
#include "../objects/obj_modifier.h"
#include "../camera/camera.h"

#include <raylib.h>
#include <stdbool.h>


typedef struct {
    // FOR TOP BAR
    OBJ_TYPE selected_shape;
    CameraModes camera_mode;
    ObjEditModes edit_mode;  // NOTE: only useful when camera mode is STILL


    // FOR PARAMETERS PANEL
    float obj_placing_distance;

} ConfigurationState;

ConfigurationState config_state_create();
