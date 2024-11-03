#include "ui.h"


static UiTopBar top_bar = {0};

static UiModifyParametersPanel modify_parameters_panel = {0};

void ui_init() {
    GuiLoadStyleAmber();
    GuiSetStyle(DEFAULT, TEXT_SIZE, DEFAULT_FONT_SIZE);

    ui_top_bar_init(&top_bar);

    ui_modify_params_panel_init(&modify_parameters_panel);
}



void ui_render_and_update(ConfigurationState* state, Mouse* mouse) {
    mouse->ui_clicked = false;


    ui_top_bar_render_and_update(&top_bar, state, mouse);

    ui_modify_params_panel_render_and_update(&modify_parameters_panel, state, mouse);

}


void ui_close() {

    ui_top_bar_close(&top_bar);

    ui_modify_params_panel_close(&modify_parameters_panel);

}

