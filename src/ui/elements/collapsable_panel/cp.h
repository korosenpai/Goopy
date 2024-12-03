#pragma once

#include <raylib.h>
#include <stdio.h>

#include "../../../libs/raygui.h"
#include "../../../mouse/mouse.h"
#include "../../../config_state/config_state.h"

#include "../../../constants.h"

#include "../../elements/draggable_rec/dr.h"

// must be window like GuiWindowBox but when clicking on x collapse it and show only rectangle 
// (set to invisible to not show after), must have array of pointers to bool visible param of ui elements inside

typedef struct {
    char* title;
    DraggableRect top_label;

    Rectangle bounds; // NOTE: RELATIVE TO RECTANGLE CREATED, NOT THE ONE WITH TITLE (updated automatically)

    bool collapsed;

    int visible_elements_count;
    bool** visible_elements; // array of pointers to elements

} CollapsablePanel;

CollapsablePanel collapsable_panel_create(Rectangle bounds, char* title, int fontsize);

// NOTE: update for ui_clicked and collapse in case
void collapsable_panel_render_and_update(CollapsablePanel* cp, Mouse* mouse, ConfigurationState* state);

void collapsable_panel_add_element(CollapsablePanel* cp, bool* visible);

void collapsable_pabel_destroy(CollapsablePanel* cp);
