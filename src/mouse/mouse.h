#pragma once

#include <raylib.h>
#include <raymath.h>
#include <stdbool.h>

typedef struct {
    Vector2 position;
    Vector2 previous_pos;

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

// vector of moouse where it moved since last frame
#define GET_DELTA_MOUSE_MOVEMENT(MOUSE_PTR) Vector2Subtract(MOUSE_PTR->position, MOUSE_PTR->previous_pos)


// ##_## to join ex: "left" with "down" in one variable (separate words with "_")
#define M_IGNORE_UI(MOUSE, M_BUTTON, M_STATUS) MOUSE.M_BUTTON ##_## M_STATUS && !MOUSE.ui_clicked

#define IS_LEFT_MOUSE_DOWN(MOUSE) M_IGNORE_UI(MOUSE, left, down)
#define IS_LEFT_MOUSE_PRESSED(MOUSE) M_IGNORE_UI(MOUSE, left, pressed)
#define IS_LEFT_MOUSE_RELEASED(MOUSE) M_IGNORE_UI(MOUSE, left, released)


