#include "tg.h"
#include <raylib.h>
#include <stdio.h>



ToggleGroup toggle_group_create(Rectangle bounds, int option_count,const char* text) {
    return (ToggleGroup) {
        .bounds = bounds,
        .option_count = option_count,
        .text = text,
        .selected = 0,
    };
}


void toggle_group_update(ToggleGroup* tg, Mouse* mouse) {
    GuiToggleGroup(tg->bounds, tg->text, &tg->selected);

    if (is_toggle_group_hovered(tg)) {
        mouse->ui_clicked = true;
    }

}


bool is_toggle_group_hovered(ToggleGroup* tg) {
    for (int i = 0; i < tg->option_count; i++) {

        Rectangle bound = tg->bounds;
        bound.x += i * tg->bounds.width;
        if (CheckCollisionPointRec(GetMousePosition(), bound)) {
            return true;
        }

    }

    return false;
}
