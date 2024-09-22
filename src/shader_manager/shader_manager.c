#include "shader_manager.h"

#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>

// allow use of multiple shaders
Shader* _loaded_shader = NULL;

int resolutionLoc = -1;

void shader_load(const char* vs_file, const char* fsfile) {
    if (_loaded_shader != NULL) {
        UnloadShader(*_loaded_shader);
    }

    *_loaded_shader = LoadShader(vs_file, fsfile);

    resolutionLoc = GetShaderLocation(*_loaded_shader, "resolution");

}

void shader_set_uniforms() {

}
