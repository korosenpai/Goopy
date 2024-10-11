#include "ui_elements.h"

DropdownMenu dropdown_menu_create(Rectangle bounds, const char* text) {
    return (DropdownMenu) {
        .edit_mode = false,
        .selected = 0,
        .bounds = bounds,
        .text = text
    };
}

void dropdown_menu_update(DropdownMenu* dm) {
    if (dm->edit_mode) GuiLock();

    if (GuiDropdownBox(dm->bounds, dm->text, &dm->selected, dm->edit_mode)) {
        dm->edit_mode = !dm->edit_mode;
    }

    GuiUnlock();
}

