#pragma once

#include "objects.h"
#include "../constants.h"


void manager_select_obj(Ray* ray);
void manager_move_selected_obj(Ray* ray);

void manager_render_objects();
void manager_render_selected_obj_menu(Camera3D* camera);

void manager_destroy_objects();

/// objects
void manager_add_sphere(Vector3 position, float radius, Color color);
