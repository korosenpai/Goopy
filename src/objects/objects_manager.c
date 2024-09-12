#include "objects_manager.h"
#include "objects.h"
#include "selected_obj_menu.h"
#include <raylib.h>
#include <stdio.h>

// id of selected object, whom render axis and translation panels
// id is calculated as position of obj in array
static int selected_obj = -1;

void manager_unselect_obj() {
    selected_obj = -1;
}

// TODO: implement to move obj easier
// true if clicked on element and still click when out of it
// move obj to dir
// static bool dragging_obj;

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

void manager_move_selected_obj(Ray* ray) {
    if (selected_obj < 0) return;
    axis_move(ray, spheres[selected_obj].axes, &spheres[selected_obj].position);
}

void manager_render_spheres() {
    for (int i = 0; i < sphere_count; i++) {
        sphere_render(spheres + i);
        if (i == selected_obj) {
            axes_render(spheres[i].axes, spheres[i].position);
        }
    }
}

void manager_render_objects() {
    // TODO: maybe calculate everything directly here?
    manager_render_spheres();
    
}

void manager_render_selected_obj_menu(Camera3D* camera) {
    if (selected_obj < 0) return;

    selected_obj_render_menu_sphere(camera, spheres + selected_obj);
}

// determine what obj the mouse is hitting and if mouse is pressed select it
void manager_select_obj(Ray* ray) {
    if (!IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) return;

    // check if colliding with any sphere
    RayCollision obj_hit;
    for (int i = 0; i < sphere_count; i++) {
        obj_hit = GetRayCollisionSphere(*ray, spheres[i].position, spheres[i].radius);
        if (!obj_hit.hit) continue;

        selected_obj = i;
        return;
    }

    // if nothing hit
    manager_unselect_obj();

}

