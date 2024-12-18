#pragma once

#include "../../constants.h"
#include "../../objects/objects.h"

#include <raylib.h>

typedef struct {
    int obj_elements_count;

    int obj_count_loc; // uniform loc
    int obj_count;

    int arr_loc; // uniform loc
    int arr_size;
    float* arr;

    // array of pointers to objs, to see which change and change them in shader
    Object** objs;

} ObjTypeShaderData;

ObjTypeShaderData obj_shader_data_create(
    int obj_element_count, Shader* shader,
    const char* obj_count_uniform, const char* elements_count_uniform, const char* arr_uniform
);

// reset arrray for next frame
void obj_shader_data_reset(ObjTypeShaderData* obj_data);

void obj_shader_data_destroy(ObjTypeShaderData* obj_data);
