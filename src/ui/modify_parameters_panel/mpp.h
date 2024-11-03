#pragma once

#include "../../mouse/mouse.h"
#include "../../config_state/config_state.h"
#include "../../utils/ui/ui_utils.h"

#include "../elements/collapsable_panel/cp.h"

typedef struct {
    float fontsize;
    CollapsablePanel panel;
} UiModifyParametersPanel;

// cannot change
#define PANEL_WIDTH 400
#define PANEL_HEIGHT 200

// can change
#define DEFAULT_PANEL_X SCREEN_WIDTH - PANEL_WIDTH - 50
#define DEFAULT_PANEL_Y 250



// bc you need to have references of all the ui elements (if returned pointers would be invalid)
void ui_modify_params_panel_init(UiModifyParametersPanel* mpp);

void ui_modify_params_panel_render_and_update(UiModifyParametersPanel* mpp, ConfigurationState* state, Mouse* mouse);
void ui_modify_params_panel_close(UiModifyParametersPanel* mpp);
