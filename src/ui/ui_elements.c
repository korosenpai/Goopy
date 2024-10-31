#include "ui_elements.h"
#include <stdio.h>

DropdownMenu dropdown_menu_create(Rectangle bounds, const char* text) {
    return (DropdownMenu) {
        .edit_mode = false,
        .selected = 0,
        .bounds = bounds,
        .text = text
    };
}

void dropdown_menu_update(DropdownMenu* dm, Mouse* mouse) {
    if (dm->edit_mode) {
        GuiLock();
        mouse->ui_clicked = true; // edit_mode shows if clicked on it
    }

    if (GuiDropdownBox(dm->bounds, dm->text, &dm->selected, dm->edit_mode)) {
        dm->edit_mode = !dm->edit_mode;
    }

    GuiUnlock();
}

