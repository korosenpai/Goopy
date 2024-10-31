#include "ui.h"
#include "elements/toggle_group/tg.h"
#include "ui_elements.h"
#include <stdio.h>


static DropdownMenu camera_mode = {0};
// static int edit_mode = 0;
static ToggleGroup edit_mode = {0};
static DropdownMenu selected_obj_type = {0};

static bool is_ui_clicked = false;

void ui_init() {
    GuiLoadStyleAmber();
    GuiSetStyle(DEFAULT, TEXT_SIZE, FONT_SIZE);

    camera_mode = dropdown_menu_create((Rectangle){LEFT_OFFSET, TOP_OFFSET, 150, 50}, CAMERA_MODE_STRING);
    edit_mode = toggle_group_create((Rectangle){LEFT_OFFSET + 170, TOP_OFFSET, 150, 50}, 2, OBJ_EDIT_MODE_STRING);
    selected_obj_type = dropdown_menu_create((Rectangle){LEFT_OFFSET + 500, TOP_OFFSET, 150, 50}, OBJ_TYPE_STRING);
}


void ui_close() {

}


// https://github.com/raysan5/raygui/issues/379
void ui_render_and_update(ConfigurationState* state, Mouse* mouse) {
    mouse->ui_clicked = false;

    dropdown_menu_update(&camera_mode, mouse);
    state->camera_mode = (CameraModes)camera_mode.selected;

    dropdown_menu_update(&selected_obj_type, mouse);
    state->selected_shape = (OBJ_TYPE)selected_obj_type.selected;

    toggle_group_update(&edit_mode, mouse);
    state->edit_mode = (ObjEditModes) edit_mode.selected;
}
