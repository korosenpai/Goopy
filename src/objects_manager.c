#include "objects_manager.h"
#include "objects.h"
#include <stdio.h>


static int sphere_count = 0;
static Sphere spheres[MAX_OBJ_COUNT] = {};

void manager_add_sphere(Vector3 position, float radius, Color color) {
    if (sphere_count + 1 == MAX_OBJ_COUNT) {
        printf("max sphere creation reached\n");
        return;
    }

    spheres[sphere_count] = sphere_create(position, radius, color);
    sphere_count++;
}

void manager_move_all_axis(Ray* ray) {
    for (int i = 0; i < sphere_count; i++) {
        axis_move(ray, spheres[i].axes, &spheres[i].position);
    }
}

void manager_render_spheres() {
    for (int i = 0; i < sphere_count; i++) {
        sphere_render(spheres + i);
    }
}

void manager_render_objects() {
    // TODO: maybe calculate everything directly here?
    manager_render_spheres();
}
