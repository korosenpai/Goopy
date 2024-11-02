#include "mpp.h"


void ui_modify_params_panel_init(UiModifyParametersPanel* mpp) {
    *mpp = (UiModifyParametersPanel){
        .panel = collapsable_panel_create((Rectangle){SCREEN_WIDTH - 300, 250, 250, 200}, "parameters"),
    };

    // collapsable_panel_add_element(&modify_parameters_panel, &edit_mode.visible);
}

void ui_modify_params_panel_render_and_update(UiModifyParametersPanel* mpp, ConfigurationState* state, Mouse* mouse) {

    collapsable_panel_render_and_update(&mpp->panel, mouse, state);
}

void ui_modify_params_panel_close(UiModifyParametersPanel* mpp) {
    collapsable_pabel_destroy(&mpp->panel);

}
