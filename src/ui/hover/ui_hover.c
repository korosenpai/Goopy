#include "ui_hover.h"
#include <raylib.h>
#include <stddef.h>

static size_t _ui_bounds_length = 0;
static Rectangle* _ui_bounds[MAX_UI_ELEMENTS]; // arr of pointer to ui bounds


