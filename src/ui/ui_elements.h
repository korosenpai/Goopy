#pragma once

#include <raylib.h>
#include <stdbool.h>

#include "../libs/raygui.h"

typedef struct {
    bool edit_mode;
    int selected;
    Rectangle bounds;
    const char* text;
} DropdownMenu;

DropdownMenu dropdown_menu_create(Rectangle bounds, const char* text);

void dropdown_menu_update(DropdownMenu* dropdown_menu);
