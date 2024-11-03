#include "mpp.h"
#include <stdio.h>

void ui_modify_params_panel_init(UiModifyParametersPanel* mpp) {
    *mpp = (UiModifyParametersPanel){
        .fontsize = (float)DEFAULT_FONT_SIZE * 0.85,
        .panel = collapsable_panel_create(
            (Rectangle){DEFAULT_PANEL_X, DEFAULT_PANEL_Y, PANEL_WIDTH, PANEL_HEIGHT},
            "parameters"
        ),
    };

    // collapsable_panel_add_element(&modify_parameters_panel, &edit_mode.visible);
}

void ui_modify_params_panel_render_and_update(UiModifyParametersPanel* mpp, ConfigurationState* state, Mouse* mouse) {

    collapsable_panel_render_and_update(&mpp->panel, mouse, state);

    if (mpp->panel.collapsed) return;

    // position of everything decided by panel bounds
    // draw everything else
    float* offset_x = &mpp->panel.bounds.x;
    float* offset_y = &mpp->panel.bounds.y;
    float* panel_width = &mpp->panel.bounds.width;
    float* panel_height = &mpp->panel.bounds.height;

    // if (GuiButton((Rectangle){*offset_x, *offset_y, 50, 50}, "nigga")) {
    //     printf("nigga\n");
    // }

    SET_FONT_SIZE(mpp->fontsize);

    ////////// placing distance
    GuiLabel((Rectangle){*offset_x + 20, *offset_y + 20, 999, 20}, "placing distance");

    // NOTE: ignore warning, we need only 3 spaces of precision ("." included)
    static char placing_dist_val[4];
    snprintf(placing_dist_val, sizeof(placing_dist_val), "%f", state->obj_placing_distance, 4);
    GuiLabel((Rectangle){*offset_x + *panel_width - 170, *offset_y + 20, 999, 20}, placing_dist_val);

    GuiSliderBar((Rectangle){*offset_x + *panel_width - 110, *offset_y + 20, 90, 20}, "", "", &state->obj_placing_distance, 1, 10);

    RESET_FONT_SIZE;
}

void ui_modify_params_panel_close(UiModifyParametersPanel* mpp) {
    collapsable_pabel_destroy(&mpp->panel);

}
