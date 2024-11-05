#include "cp.h"
#include <raylib.h>
#include <stdlib.h>

// bounds, title_bounds, collapsable_panel
#define UPDATE_BOUNDS(b, tb, fontsize) (Rectangle) {tb.x, tb.y + fontsize + 10, b.width, b.height}

CollapsablePanel collapsable_panel_create(Rectangle bounds, char* title, int fontsize) {
    return (CollapsablePanel) {
        .title = title,
        .title_bounds = (Rectangle) {
            bounds.x,
            bounds.y - fontsize - 10,
            .width = bounds.width,
            .height = fontsize + 10,

        },
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

    DrawRectangleRec(cp->title_bounds, GRAY);
    GuiLabel(cp->title_bounds, cp->title);

    // COLLAPSE / OPEN PANEL
    if (GuiButton(
        (Rectangle){cp->title_bounds.x + cp->title_bounds.width - cp->title_bounds.height, cp->title_bounds.y, cp->title_bounds.height, cp->title_bounds.height},
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
    if (CheckCollisionPointRec(mouse->position, cp->title_bounds)) {
        mouse->ui_clicked = true;
    }

    GuiSetStyle(DEFAULT, TEXT_SIZE, DEFAULT_FONT_SIZE);

    if (cp->collapsed) return;

    //////////////// render panel ////////////////
    // bounds is derived from title (able to drag title around and bring the panel)
    cp->bounds = UPDATE_BOUNDS(cp->bounds, cp->title_bounds, fontsize);
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
