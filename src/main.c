#include <raylib.h>
#include <raymath.h>
#include <stdbool.h>
#include <stdio.h>

#include "constants.h"
#include "objects/objects_manager.h"


int main(void) {

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Goopy - 3d modeller");
    SetTargetFPS(60);

    float time = 0;

    // prepare shader
    Shader shader = LoadShader(0, "shaders/fragmentShader.glsl");
    int resolutionLoc = GetShaderLocation(shader, "resolution");
    float resolution[2] = { SCREEN_WIDTH, SCREEN_HEIGHT };
    SetShaderValue(shader, resolutionLoc, resolution, SHADER_UNIFORM_VEC2);

    const Vector3 origin = (Vector3){0.0, 0.0, 0.0};

    // camera
    Camera3D camera = { 
        .position = (Vector3){ 0.0f, 10.0f, 10.0f },
        .up = (Vector3){ 0.0f, 1.0f, 0.0f },
        .target = origin,
        .fovy = 45.0f,
        .projection = CAMERA_PERSPECTIVE,
    };
    int camera_mode = CAMERA_FREE;

    // make it have camera static is enabled
    DisableCursor();
    bool is_cursor_enabled = false;


    manager_add_sphere(origin, 2.0f, BLACK);
    manager_add_sphere((Vector3){2, 3, 5}, 2.0f, VIOLET);
    // Cube cube = cube_create((Vector3){-2, -3, -5}, 1.0f, 1.0f, 2.0f, BLACK);


    // Main game loop
    while (!WindowShouldClose()) { // esc to exit
        time = GetFrameTime();

        UpdateCamera(&camera, camera_mode);


        // collisions
        Ray mouse_ray = GetScreenToWorldRay(GetMousePosition(), camera);
        manager_select_obj(&mouse_ray);
        manager_move_selected_obj(&mouse_ray);


        BeginDrawing();
            ClearBackground(RAYWHITE);

            // BeginShaderMode(shader);
            //     DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, BLACK);
            // EndShaderMode();


            BeginMode3D(camera);
                DrawSphere(origin, .1, BLACK); // origin point

                manager_render_objects();

            EndMode3D();

            // 2d menu
            manager_render_selected_obj_menu(&camera);


            DrawFPS(SCREEN_WIDTH - 100, 20);

        EndDrawing();

        if (IsKeyPressed(KEY_M)) {
            if (!is_cursor_enabled) {
                camera_mode = CAMERA_PERSPECTIVE;
                EnableCursor();
            }
            else {
                camera_mode = CAMERA_FREE;
                DisableCursor();
            }
            is_cursor_enabled = !is_cursor_enabled;
        }



    }

    UnloadShader(shader);
    CloseWindow();

    return 0;
}
