#pragma once

#include <stdbool.h>

typedef struct {
    bool left_down;
    bool left_pressed;
    bool left_released;

    bool right_down;
    bool right_pressed;
    bool right_released;
} Mouse;

Mouse mouse_create();

void mouse_update(Mouse* mouse);
