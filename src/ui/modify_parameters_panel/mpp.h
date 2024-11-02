#pragma once

#include "../../mouse/mouse.h"
#include "../../config_state/config_state.h"

#include "../elements/collapsable_panel/cp.h"

typedef struct {
    CollapsablePanel panel;
} UiModifyParametersPanel;

// bc you need to have references of all the ui elements (if returned pointers would be invalid)
void ui_modify_params_panel_init(UiModifyParametersPanel* mpp);

void ui_modify_params_panel_render_and_update(UiModifyParametersPanel* mpp, ConfigurationState* state, Mouse* mouse);
void ui_modify_params_panel_close(UiModifyParametersPanel* mpp);
