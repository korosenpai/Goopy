#include "objects.h"

#include "../collisions/collisions.h"

#include <raylib.h>
#include <stdarg.h>
#include <stdbool.h>
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

void axes_move(Ray* ray, Axis axes[3], Vector3* obj_pos) {
    bool is_mouse_button_down = IsMouseButtonDown(MOUSE_BUTTON_LEFT);
    
    Axis* x_axis = axes;
    Axis* y_axis = axes + 1;
    Axis* z_axis = axes + 2;

    // axis but cursor not on the obj
    RayCollision x_hit = GetRayCollisionBox(*ray, get_axis_bounding_box(axes, *obj_pos));
    if (is_mouse_button_down && (x_hit.hit || x_axis->is_selected)) {

        // skip first touching frame so last_touched_position is set
        if (x_axis->is_selected) {

            obj_pos->x += x_hit.point.x - x_axis->last_touched_position;
        }
        x_axis->last_touched_position = x_hit.point.x;
        x_axis->is_selected = true;
        y_axis->is_selected = false; // select only one axis
        z_axis->is_selected = false;
    }
    else x_axis->is_selected = false;

    RayCollision y_hit = GetRayCollisionBox(*ray, get_axis_bounding_box(axes + 1, *obj_pos));
    if (is_mouse_button_down && (y_hit.hit || y_axis->is_selected)) {

        // skip first touching frame so last_touched_position is set
        if (y_axis->is_selected) {

            obj_pos->y += y_hit.point.y - y_axis->last_touched_position;
        }
        y_axis->last_touched_position = y_hit.point.y;
        y_axis->is_selected = true;
        x_axis->is_selected = false;
        z_axis->is_selected = false;
    }
    else y_axis->is_selected = false;

    RayCollision z_hit = GetRayCollisionBox(*ray, get_axis_bounding_box(axes + 2, *obj_pos));
    if (is_mouse_button_down && (z_hit.hit || z_axis->is_selected)) {

        // skip first touching frame so last_touched_position is set
        if (z_axis->is_selected) {

            obj_pos->z += z_hit.point.z - z_axis->last_touched_position;
        }
        z_axis->last_touched_position = z_hit.point.z;
        z_axis->is_selected = true;
        y_axis->is_selected = false;
        x_axis->is_selected = false;
    }
    else z_axis->is_selected = false;
}



void object_destroy(Object* obj) {
    free(obj->data);
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

void draw_obj_center(const Vector3* position) {
    DrawSphere(*position, 0.1, MAGENTA); // center of obj
}

//////////////////// SPHERES ////////////////////
// data = { radius }
void sphere_render(const Object* sphere, bool is_selected) {
    DrawSphereWires(sphere->position, sphere->data[0], 16, 16, is_selected ? OBJ_SELECTED_COLOR : sphere->color);
    draw_obj_center(&sphere->position);
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

void cube_render(const Object* cube, bool is_selected) {
    float width = cube->data[0];
    float height = cube->data[1];
    float length = cube->data[2];
    DrawCubeWires(cube->position, width, height, length, is_selected ? OBJ_SELECTED_COLOR : cube->color);
    draw_obj_center(&cube->position);
}

RayCollision cube_select(const Object* cube, const Ray* ray) {
    float width = cube->data[0];
    float height = cube->data[1];
    float length = cube->data[2];
    BoundingBox box = (BoundingBox){
        (Vector3){
            cube->position.x - width/2,
            cube->position.y - height/2,
            cube->position.z - length/2
        },
        (Vector3){
            cube->position.x + width/2,
            cube->position.y + height/2,
            cube->position.z + length/2
        }
    };

    return GetRayCollisionBox(*ray, box);
}

Object cube_create(Vector3 position, float width, float height, float length, Color color) {
    return (Object) {
        .type = CUBE,
        .position = position,
        .axes = {axis_new_x(), axis_new_y(), axis_new_z()},
        .color = color,
        .data = obj_set_data_array(3, width, height, length),
        .updated = false,
        .move = NULL,
        .select = cube_select,
        .render = cube_render,
    };

}


