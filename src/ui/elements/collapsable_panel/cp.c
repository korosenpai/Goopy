#include "cp.h"
#include <raylib.h>
#include <stdlib.h>

CollapsablePanel collapsable_panel_create(Rectangle bounds, char* title) {
    return (CollapsablePanel) {
        .title = title,
        .bounds = bounds,
        .collapsed = false,

        .visible_elements_count = 0,
        .visible_elements = NULL,
    };
}

void collapsable_panel_render_and_update(CollapsablePanel* cp, Mouse* mouse, ConfigurationState* state) {
    //////////////// render top bar ////////////////
    float fontsize = (float) DEFAULT_FONT_SIZE * 0.85;
    GuiSetStyle(DEFAULT, TEXT_SIZE, fontsize);

    Rectangle labelsize = {
        .x = cp->bounds.x,
        .y = cp->bounds.y - fontsize - 10,
        .width = cp->bounds.width,
        .height = fontsize + 10,
    };
    DrawRectangleRec(labelsize, GRAY);
    GuiLabel(labelsize, cp->title);

    // COLLAPSE / OPEN PANEL
    if (GuiButton(
        (Rectangle){labelsize.x + labelsize.width - labelsize.height, labelsize.y, labelsize.height, labelsize.height},
        cp->collapsed ? "v" : "^") // TODO: change to add icons
    ) {
        cp->collapsed = !cp->collapsed;

        // update all visible values
        for (int i = 0; i < cp->visible_elements_count; i++) {
            // if cp is collapsed, visible must be false
            *cp->visible_elements[i] = !cp->collapsed;
        }
    }

    // if mouse there
    if (CheckCollisionPointRec(mouse->position, labelsize)) {
        mouse->ui_clicked = true;
    }

    GuiSetStyle(DEFAULT, TEXT_SIZE, DEFAULT_FONT_SIZE);

    if (cp->collapsed) return;

    //////////////// render panel ////////////////
    if (CheckCollisionPointRec(mouse->position, cp->bounds)) {
        mouse->ui_clicked = true;
    }

    DrawRectangleRec(cp->bounds, BLACK);
}


void collapsable_panel_add_element(CollapsablePanel* cp, bool* visible) {
    cp->visible_elements_count++;

    cp->visible_elements = realloc(cp->visible_elements, cp->visible_elements_count * sizeof(*cp->visible_elements));
    cp->visible_elements[cp->visible_elements_count - 1] = visible;


}


void collapsable_pabel_destroy(CollapsablePanel* cp) {
    free(cp->visible_elements);
}
