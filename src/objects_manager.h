#pragma once

#include "objects.h"
#include "constants.h"

void manager_add_sphere(Vector3 position, float radius, Color color);
void manager_render_spheres();

void manager_move_all_axis(Ray* ray);

void manager_render_objects();
