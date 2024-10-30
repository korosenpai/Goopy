#pragma once

#include "../objects/objects.h"

void shader_setup(Shader* shader);

// called from manager
void shader_update_obj_data(Shader* shader, Object* objs, int* obj_count);

void shader_add_obj(Shader* shader, Object* obj);
void shader_delete_obj(); // reload all array?
void shader_update_selected_obj();

void shader_close();
