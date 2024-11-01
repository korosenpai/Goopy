#pragma once

#include <raylib.h>
#include <stdbool.h>

typedef struct {
    Vector2 position;

    bool left_down;
    bool left_pressed;
    bool left_released;

    bool right_down;
    bool right_pressed;
    bool right_released;

    bool ui_clicked; // NOTE: updated in ui_render_and_update (ui.c)
} Mouse;

Mouse mouse_create();

void mouse_update(Mouse* mouse);

// ##_## to join ex: "left" with "down" in one variable (separate words with "_")
#define M_IGNORE_UI(M_BUTTON, M_STATUS) mouse.M_BUTTON ##_## M_STATUS && !mouse.ui_clicked

#define IS_LEFT_MOUSE_DOWN(mouse) M_IGNORE_UI(left, down)
#define IS_LEFT_MOUSE_PRESSED(mouse) M_IGNORE_UI(left, pressed)
#define IS_LEFT_MOUSE_RELEASED(mouse) M_IGNORE_UI(left, released)


