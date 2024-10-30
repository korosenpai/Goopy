#pragma once

#include "objects.h"
#include "../constants.h"
#include "../shader_manager/shader_manager.h"

// gets called at every frame start to set updated to false
void manager_reset_obj_update();

void manager_select_obj(Ray* ray);
void manager_move_selected_obj(Ray* ray);

void manager_render_objects();
void manager_render_selected_obj_menu(Camera3D* camera);

void manager_destroy_objects();

/// objects
void manager_add_object(Shader* shader, Object obj);

