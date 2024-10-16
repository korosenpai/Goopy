#include "shader_manager.h"
#include <raylib.h>
#include <stdio.h>



void shader_update_obj_data(Shader* shader, Object* objs, int* obj_count) {
    // TODO: add all objs

    int sphereInfoSizeLoc = GetShaderLocation(*shader, "sphereInfoSize");
    SetShaderValue(*shader, sphereInfoSizeLoc, obj_count, SHADER_UNIFORM_INT);

    for (int i = 0; i < *obj_count; i ++) {
        if (!objs[i].updated) continue;

        Object* obj = objs + i;

        // WARN: only for spheres
        switch (obj->type) {
            case SPHERE:

                break;

            default:
                break;
        
        }

        printf("updated %d\n", i);
    }

}

