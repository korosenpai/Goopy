#pragma once

#include <raylib.h>

#include "../../../libs/raygui.h"
#include "../../../mouse/mouse.h"

typedef struct {
    Rectangle bounds;
    int option_count;
    const char* text;
    int selected;

} ToggleGroup;

ToggleGroup toggle_group_create(Rectangle bounds, int option_count, const char* text);
void toggle_group_update(ToggleGroup* tg, Mouse* mouse);

bool is_toggle_group_hovered(ToggleGroup* tg);

