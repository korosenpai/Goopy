#include "dr.h"
#include <raylib.h>


DraggableRect draggable_rect_create(int x, int y, int width, int height, Color color) {
    return (DraggableRect) {
        .color = color,
        .is_dragging = false,
        .bounds = (Rectangle) {
            x, y, width, height
        }
    };
}



void draggable_rect_render_and_update(DraggableRect* dr) {


    DrawRectangleRec(dr->bounds, dr->color);

}
