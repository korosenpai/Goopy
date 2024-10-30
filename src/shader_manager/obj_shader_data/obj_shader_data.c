#include "obj_shader_data.h"

#include <raylib.h>
#include <stdlib.h>

// TODO: change to not pass loc but uniform name, and then you call the getshaderlocation function
ObjTypeShaderData obj_shader_data_create(int obj_element_count, Shader* shader, const char* obj_count_uniform, const char* arr_uniform) {
    return (ObjTypeShaderData){
        .obj_elements_count  = obj_element_count,

        .obj_count_loc = GetShaderLocation(*shader, obj_count_uniform),
        .obj_count = 0,

        .arr_loc = GetShaderLocation(*shader, arr_uniform),
        .arr_size = 0,
        .arr = malloc(sizeof(float) * obj_element_count * MAX_OBJ_COUNT),

    };

}

void obj_shader_data_reset(ObjTypeShaderData* obj_data) {
    obj_data->arr_size = 0;
    obj_data->obj_count = 0;
}

void obj_shader_data_destroy(ObjTypeShaderData* obj_data) {
    free(obj_data->arr);
}
