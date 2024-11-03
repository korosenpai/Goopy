#pragma once

#include "../../mouse/mouse.h"
#include "../../config_state/config_state.h"

#include "../elements/dropdown_menu/dm.h"
#include "../elements/toggle_group/tg.h"

#define TB_TOP_OFFSET 10
#define TB_LEFT_OFFSET 10

typedef struct {
    DropdownMenu camera_mode;
    ToggleGroup edit_mode;
    DropdownMenu selected_obj_type;

} UiTopBar;

void ui_top_bar_init(UiTopBar* tp);
void ui_top_bar_render_and_update(UiTopBar* tp, ConfigurationState* state, Mouse* mouse);
void ui_top_bar_close(UiTopBar* tp);
