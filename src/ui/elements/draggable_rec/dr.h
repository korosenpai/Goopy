#pragma once

#include <raylib.h>

// inspo: https://www.raylib.com/examples/shapes/loader.html?name=shapes_lines_bezier

typedef struct {
    Color color;
    bool is_dragging;
    Rectangle bounds;

} DraggableRect;

DraggableRect draggable_rect_create(int x, int y, int width, int height, Color color);

void draggable_rect_render_and_update(DraggableRect* dr);
