#include "dr.h"
#include <raymath.h>

DraggableRect draggable_rect_create(int x, int y, int width, int height, Color color) {
    return (DraggableRect) {
        .color = color,
        .is_dragging = false,
        .bounds = (Rectangle) {
            x, y, width, height
        }
    };
}



void draggable_rect_render_and_update(DraggableRect* dr, Mouse* mouse) {
    if (dr->is_dragging) {
        Vector2 delta = GET_DELTA_MOUSE_MOVEMENT(mouse);

        dr->bounds.x += delta.x;
        dr->bounds.y += delta.y;

        // clamp values to never make rect go out of screen
        if (dr->bounds.x < 0) {
            dr->bounds.x = 0;
        }
        if (dr->bounds.x + dr->bounds.width > SCREEN_WIDTH) {
            dr->bounds.x = SCREEN_WIDTH - dr->bounds.width;
        }

        if (dr->bounds.y < 0) {
            dr->bounds.y = 0;
        }
        if (dr->bounds.y + dr->bounds.height > SCREEN_HEIGHT) {
            dr->bounds.y = SCREEN_HEIGHT - dr->bounds.height;
        }
    }


    dr->is_dragging = false;



    if (IS_LEFT_MOUSE_DOWN((*mouse)) && CheckCollisionPointRec(mouse->position, dr->bounds)) {
        mouse->ui_clicked = true;
        dr->is_dragging = true;
    }

    DrawRectangleRec(dr->bounds, dr->color);

}
