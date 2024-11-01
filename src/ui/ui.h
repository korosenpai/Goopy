#pragma once

#include <raylib.h>
#include <stdbool.h>

#include "../constants.h"
#include "../libs/raygui_style_amber.h"
#include "../config_state/config_state.h"
#include "../mouse/mouse.h"

#include "elements/toggle_group/tg.h"
#include "elements/dropdown_menu/dm.h"
#include "elements/collapsable_panel/cp.h"

#define TOP_OFFSET 10
#define LEFT_OFFSET 10

void ui_init();

void ui_close();

void ui_render_and_update(ConfigurationState* state, Mouse* mouse);
