#include "tb.h"


UiTopBar ui_top_bar_init() {
    return (UiTopBar){

        .camera_mode = dropdown_menu_create(
            (Rectangle){TB_LEFT_OFFSET, TB_TOP_OFFSET, 150, 50}, CAMERA_MODE_STRING
        ),

        .edit_mode = toggle_group_create(
            (Rectangle){TB_LEFT_OFFSET + 170, TB_TOP_OFFSET, 150, 50}, 2, OBJ_EDIT_MODE_STRING
        ),

        .selected_obj_type = dropdown_menu_create(
            (Rectangle){TB_LEFT_OFFSET + 500, TB_TOP_OFFSET, 150, 50}, OBJ_TYPE_STRING
        ),
    };

}

void ui_top_bar_render_and_update(UiTopBar* tp, ConfigurationState* state, Mouse* mouse) {

    dropdown_menu_update(&tp->camera_mode, mouse);
    state->camera_mode = (CameraModes)tp->camera_mode.selected;

    dropdown_menu_update(&tp->selected_obj_type, mouse);
    state->selected_shape = (OBJ_TYPE)tp->selected_obj_type.selected;

    toggle_group_update(&tp->edit_mode, mouse);
    state->edit_mode = (ObjEditModes) tp->edit_mode.selected;
}

void ui_top_bar_close(UiTopBar* tp) {

}
