#include "shader_manager.h"
#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "obj_shader_data/obj_shader_data.h"


// SAVE OBJS IN ObjTypeShaderData* arr
// in order of enum to send something like position generally without rewrititng it 
// in every case 
// static ObjTypeShaderData spheres;
// static ObjTypeShaderData cubes;

// constants for shader array numbers
#define POSITION_SIZE 3
#define COLOR_SIZE 4

// TODO: save in ObjTypeShaderData[7] and access proper array with arr[obj->type - 1] // -1 to remove NONE, must be in same order as objects
#define OBJ_DATA_ARRAY_COUNT 2
static ObjTypeShaderData* objDataArrays;


void shader_setup(Shader* shader) {

    objDataArrays = malloc(sizeof(ObjTypeShaderData) * OBJ_DATA_ARRAY_COUNT);
    objDataArrays[0] = obj_shader_data_create(POSITION_SIZE + COLOR_SIZE + 1, shader, "spheresCount", "sphereElementsCount", "sphereInfoArr");
    objDataArrays[1] = obj_shader_data_create(POSITION_SIZE + COLOR_SIZE + 3, shader, "cubeCount", "cubeElementsCount","cubeInfoArr"); 
    
    // TODO: implement
    // objDataArrays[1] = obj_shader_data_create(POSITION_SIZE + COLOR_SIZE + 1, shader, "octahedronCount", "octahedronElementsCount","octahedronInfoArr"); 
}

void shader_add_obj(Shader* shader, Object* obj) {
    // get correct array for obj type
    assert(obj->type <= OBJ_DATA_ARRAY_COUNT); // TODO: remove when all objs implemented
    ObjTypeShaderData* data_arr = objDataArrays + obj->type - 1;

    // add position
    data_arr->obj_count++;
    data_arr->arr[data_arr->arr_size] = obj->position.x;
    data_arr->arr[data_arr->arr_size + 1] = obj->position.y;
    data_arr->arr[data_arr->arr_size + 2] = obj->position.z;
    data_arr->arr_size += 3;

    // add vec4 color
    data_arr->arr[data_arr->arr_size] = obj->color.r;
    data_arr->arr[data_arr->arr_size + 1] = obj->color.g;
    data_arr->arr[data_arr->arr_size + 2] = obj->color.b;
    data_arr->arr[data_arr->arr_size + 3] = obj->color.a;
    data_arr->arr_size += 4;


    // pass data array
    for (int i = 0; i < obj->data_arr_length; i++) {
        data_arr->arr[data_arr->arr_size + i] = obj->data[i];
    }
    data_arr->arr_size += obj->data_arr_length;

    // update obj count and obj array (only added obj)
    SetShaderValue(*shader, data_arr->obj_count_loc, &data_arr->obj_count, SHADER_UNIFORM_INT);
    SetShaderValueV(
        *shader,
        // TODO: set only one obj value
        data_arr->arr_loc,
        data_arr->arr,
        SHADER_ATTRIB_FLOAT,
        data_arr->arr_size
    );
}

void shader_close() {

    free(objDataArrays);

}
