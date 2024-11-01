#include "mouse.h"
#include <raylib.h>

static bool left_down = false;
static bool left_pressed = false;
static bool left_released = false;
static bool left_ui_pressed = false;

Mouse mouse_create() {
    return (Mouse) {
        .position = GetMousePosition(),
        .left_down = false,
        .left_pressed = false,
        .left_released = false,

        .right_down = false,
        .right_pressed = false,
        .right_released = false,

        .ui_clicked = false,
    };
}

void mouse_update(Mouse* mouse) {
    mouse->position = GetMousePosition();

    mouse->left_down = IsMouseButtonDown(MOUSE_LEFT_BUTTON);
    mouse->left_pressed = IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
    mouse->left_released = IsMouseButtonReleased(MOUSE_LEFT_BUTTON);

    mouse->right_down = IsMouseButtonDown(MOUSE_RIGHT_BUTTON);
    mouse->right_pressed = IsMouseButtonPressed(MOUSE_RIGHT_BUTTON);
    mouse->right_released = IsMouseButtonReleased(MOUSE_RIGHT_BUTTON);
}

