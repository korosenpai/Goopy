#include "shader_manager.h"
#include <raylib.h>

#include "../constants.h"

static int _spheres_count_loc;
static int _spheres_count = 0;
static int _sphere_arr_size = 0;
static float _sphere_arr[MAX_OBJ_COUNT * 8];

void shader_update_obj_data(Shader* shader, Object* objs, int* obj_count) {
    // TODO: add all objs

    _spheres_count_loc = GetShaderLocation(*shader, "spheres_count");

    // NOTE: EVERYTHING GETS RECALCULATED EVERY FRAME FOR NOW
    // reset arrays;
    _sphere_arr_size = 0;
    _spheres_count = 0;

    for (int i = 0; i < *obj_count; i ++) {
        // if (!objs[i].updated) continue;

        Object* obj = objs + i;

        // NOTE: arrays should be {posx..z, color, data*}
        // WARN: only for spheres
        switch (obj->type) {
            case SPHERE:
                _spheres_count++;

                _sphere_arr[_sphere_arr_size] = obj->position.x;
                _sphere_arr[_sphere_arr_size + 1] = obj->position.y;
                _sphere_arr[_sphere_arr_size + 2] = obj->position.z;
                _sphere_arr_size += 3;

                // float arr[] = {obj->position.x, obj->position.y, obj->position.z};
                // PASS ARRAY AS {posx, posy, posz, colr, colg, colb, cola, radius}
                int _sphereInfoLoc = GetShaderLocation(*shader, "sphereInfo");
                SetShaderValueV(*shader, _sphereInfoLoc, _sphere_arr, SHADER_ATTRIB_FLOAT, _sphere_arr_size);

                break;

            default:
                break;
        
        }

        SetShaderValue(*shader, _spheres_count_loc, &_spheres_count, SHADER_UNIFORM_INT);
    }

}

