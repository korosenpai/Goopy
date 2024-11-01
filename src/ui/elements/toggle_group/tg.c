#include "tg.h"



ToggleGroup toggle_group_create(Rectangle bounds, int option_count,const char* text) {
    return (ToggleGroup) {
        .bounds = bounds,
        .option_count = option_count,
        .text = text,
        .selected = 0,

        .visible = true,
    };
}

bool is_toggle_group_hovered(ToggleGroup* tg, Mouse* mouse) {
    for (int i = 0; i < tg->option_count; i++) {

        Rectangle bound = tg->bounds;
        bound.x += i * tg->bounds.width;
        if (CheckCollisionPointRec(mouse->position, bound)) {
            return true;
        }

    }

    return false;
}

void toggle_group_update(ToggleGroup* tg, Mouse* mouse) {
    if (!tg->visible) return;

    GuiToggleGroup(tg->bounds, tg->text, &tg->selected);

    if (is_toggle_group_hovered(tg, mouse)) {
        mouse->ui_clicked = true;
    }

}


