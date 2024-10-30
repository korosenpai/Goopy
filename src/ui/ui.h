#pragma once

#include <raylib.h>
#include <stdbool.h>

#include "../constants.h"
#include "../libs/raygui_style_amber.h"
#include "../config_state/config_state.h"
#include "ui_elements.h"

#define FONT_SIZE 32

#define TOP_OFFSET 10
#define LEFT_OFFSET 10

void ui_init();

void ui_close();

// NOTE: render and udpate
void ui_render(ConfigurationState* state);
