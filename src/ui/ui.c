#include "ui.h"
#include "ui_elements.h"


static DropdownMenu camera_mode = {0};
static int edit_mode = 0;
static DropdownMenu selected_obj_type = {0};

void ui_init() {
    GuiLoadStyleAmber();
    GuiSetStyle(DEFAULT, TEXT_SIZE, FONT_SIZE);

    camera_mode = dropdown_menu_create((Rectangle){LEFT_OFFSET, TOP_OFFSET, 150, 50}, CAMERA_MODE_STRING);
    selected_obj_type = dropdown_menu_create((Rectangle){LEFT_OFFSET + 500, TOP_OFFSET, 150, 50}, OBJ_TYPE_STRING);
}


void ui_close() {

}

void ui_update(ConfigurationState* state) {
    state->camera_mode = (CameraModes)camera_mode.selected;
    state->selected_shape = (OBJ_TYPE)selected_obj_type.selected;
    state->edit_mode = (ObjEditModes) edit_mode;
}

// https://github.com/raysan5/raygui/issues/379
void ui_render(ConfigurationState* state) {
    dropdown_menu_update(&camera_mode);
    dropdown_menu_update(&selected_obj_type);

    GuiToggleGroup((Rectangle){LEFT_OFFSET + 170, TOP_OFFSET, 150, 50}, OBJ_EDIT_MODE_STRING, &edit_mode);
}
