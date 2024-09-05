#include "objects.h"
#include <raylib.h>

Axis axis_new_x() {
    return (Axis) {
        .offset = (Vector3){AXIS_MAX_LENGTH / 2, 0, 0},
        .width = AXIS_MAX_LENGTH,
        .height = AXIS_MIN_LENGTH,
        .length = AXIS_MIN_LENGTH,
        .last_touched_position = (Vector3) {0},
    };
}
Axis axis_new_y() {
    return (Axis) {
        .offset = (Vector3){0, AXIS_MAX_LENGTH / 2, 0},
        .width = AXIS_MIN_LENGTH,
        .height = AXIS_MAX_LENGTH,
        .length = AXIS_MIN_LENGTH,
        .last_touched_position = (Vector3) {0},
    };
}
Axis axis_new_z() {
    return (Axis) {
        .offset = (Vector3){0, 0, AXIS_MAX_LENGTH / 2},
        .width = AXIS_MIN_LENGTH,
        .height = AXIS_MIN_LENGTH,
        .length = AXIS_MAX_LENGTH,
        .last_touched_position = (Vector3) {0},
    };
}
