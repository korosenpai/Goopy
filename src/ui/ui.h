#pragma once

#include <raylib.h>
#include <stdbool.h>

#include "../constants.h"
#include "../libs/raygui_style_amber.h"
#include "../config_state/config_state.h"
#include "../mouse/mouse.h"


#include "modify_parameters_panel/mpp.h"
#include "top_bar/tb.h"

// #include "elements/toggle_group/tg.h"
// #include "elements/dropdown_menu/dm.h"
#include "elements/collapsable_panel/cp.h"


void ui_init();

void ui_render_and_update(ConfigurationState* state, Mouse* mouse);

void ui_close();

