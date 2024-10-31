#pragma once

#include <raylib.h>
#include <stdbool.h>

#include "../constants.h"
#include "../libs/raygui_style_amber.h"
#include "../config_state/config_state.h"
#include "../mouse/mouse.h"

#include "ui_elements.h"

#define FONT_SIZE 32

#define TOP_OFFSET 10
#define LEFT_OFFSET 10

void ui_init();

void ui_close();

void ui_render_and_update(ConfigurationState* state, Mouse* mouse);
