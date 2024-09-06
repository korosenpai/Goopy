#include "objects.h"
#include "collisions.h"
#include <raylib.h>
#include <raymath.h>
#include <stdbool.h>

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

void axis_render(Axis axes[3], Vector3 obj_pos) {

    for (int i = 0; i < 3; i++) {
        Axis* axis = axes + i;
        DrawCube(
            Vector3Add(obj_pos, axis->offset),
            axis->width,
            axis->height,
            axis->length,
            (!axis->is_selected ? axis->color : SELECTED_COLOR)
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

Sphere sphere_create(Vector3 position, float radius, Color color) {
    return (Sphere) {
        .position = position,
        .radius = radius,
        .color = color,
        .axes = {axis_new_x(), axis_new_y(), axis_new_z()},
    };

}

void sphere_render(Sphere* sphere) {
    DrawSphereWires(sphere->position, sphere->radius, 16, 16, sphere->color);
    axis_render(sphere->axes, sphere->position);
    DrawSphere(sphere->position, 0.1, MAGENTA); // center of sphere
}


Cube cube_create(Vector3 position, float width, float height, float length, Color color) {
    return (Cube) {
        .position = position,
        .width = width,
        .height = height,
        .length = length,
        .color = color,
        .axes = {axis_new_x(), axis_new_y(), axis_new_z()},
    };

}
void cube_render(Cube* cube) {
    DrawCubeWires(cube->position, cube->width, cube->height, cube->length, cube->color);
    axis_render(cube->axes, cube->position);
    DrawSphere(cube->position, 0.1, MAGENTA); // center of cube
}
