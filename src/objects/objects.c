#include "objects.h"

#include "../collisions/collisions.h"

#include <raylib.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

Axis axis_new_x() {
    return (Axis) {
        .offset = (Vector3){AXIS_MAX_LENGTH / 2, 0, 0},
        .width = AXIS_MAX_LENGTH,
        .height = AXIS_MIN_LENGTH,
        .length = AXIS_MIN_LENGTH,
        .color = RED,
        .is_selected = false,
        .last_touched_position = 0,
    };
}
Axis axis_new_y() {
    return (Axis) {
        .offset = (Vector3){0, AXIS_MAX_LENGTH / 2, 0},
        .width = AXIS_MIN_LENGTH,
        .height = AXIS_MAX_LENGTH,
        .length = AXIS_MIN_LENGTH,
        .color = GREEN,
        .is_selected = false,
        .last_touched_position = 0,
    };
}
Axis axis_new_z() {
    return (Axis) {
        .offset = (Vector3){0, 0, AXIS_MAX_LENGTH / 2},
        .width = AXIS_MIN_LENGTH,
        .height = AXIS_MIN_LENGTH,
        .length = AXIS_MAX_LENGTH,
        .color = BLUE,
        .is_selected = false,
        .last_touched_position = 0,
    };
}

void axes_render(Axis axes[3], Vector3 obj_pos) {

    for (int i = 0; i < 3; i++) {
        Axis* axis = axes + i;
        DrawCube(
            Vector3Add(obj_pos, axis->offset),
            axis->width,
            axis->height,
            axis->length,
            (!axis->is_selected ? axis->color : OBJ_SELECTED_COLOR)
        );
    }
}

void axis_move(Ray* ray, Axis axes[3], Vector3* obj_pos) {
    bool is_mouse_button_down = IsMouseButtonDown(MOUSE_BUTTON_LEFT);

    RayCollision x_hit = GetRayCollisionBox(*ray, get_axis_bounding_box(axes, *obj_pos));
    if (x_hit.hit && is_mouse_button_down) {

        // skip first touching frame so last_touched_position is set
        if (axes[0].is_selected) {

            obj_pos->x += x_hit.point.x - axes[0].last_touched_position;
        }
        axes[0].last_touched_position = x_hit.point.x;
        axes[0].is_selected = true;
    }
    else axes[0].is_selected = false;

    RayCollision y_hit = GetRayCollisionBox(*ray, get_axis_bounding_box(axes + 1, *obj_pos));
    if (y_hit.hit && is_mouse_button_down) {

        // skip first touching frame so last_touched_position is set
        if (axes[1].is_selected) {

            obj_pos->y += y_hit.point.y - axes[1].last_touched_position;
        }
        axes[1].last_touched_position = y_hit.point.y;
        axes[1].is_selected = true;
    }
    else axes[1].is_selected = false;

    RayCollision z_hit = GetRayCollisionBox(*ray, get_axis_bounding_box(axes + 2, *obj_pos));
    if (z_hit.hit && is_mouse_button_down) {

        // skip first touching frame so last_touched_position is set
        if (axes[2].is_selected) {

            obj_pos->z += z_hit.point.z - axes[2].last_touched_position;
        }
        axes[2].last_touched_position = z_hit.point.z;
        axes[2].is_selected = true;
    }
    else axes[2].is_selected = false;
}



float* obj_set_data_array(int n_elems, ...) {
    float* data = malloc(sizeof(float) * n_elems);

    va_list lst;
    va_start(lst, n_elems);
    for (int i = 0; i < n_elems; i++) {
        data[i] = (float)va_arg(lst, double);
    }
    va_end(lst);

    return data;
}


//////////////////// SPHERES ////////////////////
// data = { radius }
void sphere_render(const Object* sphere, bool is_selected) {
    DrawSphereWires(sphere->position, sphere->data[0], 16, 16, is_selected ? OBJ_SELECTED_COLOR : sphere->color);
    DrawSphere(sphere->position, 0.1, MAGENTA); // center of sphere
}
RayCollision sphere_select(const Object* sphere, const Ray* ray) {
    return GetRayCollisionSphere(*ray, sphere->position, sphere->data[0]);
}

Object sphere_create(Vector3 position, float radius, Color color) {
    return (Object) {
        .type = SPHERE,
        .position = position,
        .axes = {axis_new_x(), axis_new_y(), axis_new_z()},
        .color = color,
        .data = obj_set_data_array(1, radius),
        .updated = false,
        .move = NULL,
        .select = sphere_select,
        .render = sphere_render,
    };

}

//////////////////// CUBES  ////////////////////



void object_destroy(Object* obj) {
    free(obj->data);
}
