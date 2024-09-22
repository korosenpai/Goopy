#include <raylib.h>
#include <raymath.h>
#include <stdbool.h>
#include <stdio.h>

#include "constants.h"
#include "objects/objects.h"
#include "objects/objects_manager.h"



int main(void) {

    SetTargetFPS(60);
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Goopy - 3d modeller");


    // prepare shader
    Shader shader = LoadShader(0, "shaders/ray_marcher.glsl");
    int resolutionLoc = GetShaderLocation(shader, "resolution");
    float resolution[2] = { SCREEN_WIDTH, SCREEN_HEIGHT };
    SetShaderValue(shader, resolutionLoc, resolution, SHADER_UNIFORM_VEC2);

    int rayOriginLoc = GetShaderLocation(shader, "ro");
    float ray_origin[3] = {0.0f, 0.0f, -3.0f};
    SetShaderValue(shader, rayOriginLoc, ray_origin, SHADER_UNIFORM_VEC3);

    int rayDirectionLoc = GetShaderLocation(shader, "ro");
    float ray_direction[3] = {0.0f, 0.0f, -3.0f};
    SetShaderValue(shader, rayDirectionLoc, ray_direction, SHADER_UNIFORM_VEC3);

    int timeLoc = GetShaderLocation(shader, "time");
    float time = 0;
    SetShaderValue(shader, timeLoc, &time, SHADER_UNIFORM_FLOAT);

    int mouseLoc = GetShaderLocation(shader, "mouse");
    float mouse_pos[2] = {0, 0};
    SetShaderValue(shader, mouseLoc, mouse_pos, SHADER_UNIFORM_VEC2);


    Camera3D camera = {0};
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };
    camera.position = (Vector3){ray_origin[0], ray_origin[1], ray_origin[2]};
    camera.fovy = 45.0f;
    camera.projection = CAMERA_PERSPECTIVE;
    int camera_mode = CAMERA_PERSPECTIVE;

    // make it have camera static is enabled
    // DisableCursor();
    bool is_cursor_enabled = true;


    
    // manager_add_object(
    //     cube_create(
    //         (Vector3){0.0f, 0.0f, 0.0f},
    //         1, 1, 1, BLACK
    //     )
    // );
    manager_add_object(
        sphere_create((Vector3){2, 3, 5}, 2.0f, VIOLET)
    );
    manager_add_object(
        sphere_create((Vector3){0}, 1.0f, RED)
    );

    // Main game loop
    while (!WindowShouldClose()) { // esc to exit
        // deltatime = GetFrameTime();
        time = GetTime();

        UpdateCamera(&camera, camera_mode);
        // printf("position: %f %f %f\n", camera.position.x, camera.position.y, camera.position.z);

        ray_origin[0] = camera.position.x;
        ray_origin[1] = camera.position.y;
        ray_origin[2] = camera.position.z;
        SetShaderValue(shader, rayOriginLoc, ray_origin, SHADER_UNIFORM_VEC3);

        SetShaderValue(shader, timeLoc, &time, SHADER_UNIFORM_FLOAT);

        mouse_pos[0] = GetMouseX();
        mouse_pos[1] = GetMouseY();
        SetShaderValue(shader, mouseLoc, mouse_pos, SHADER_UNIFORM_VEC2);




        // collisions
        Ray mouse_ray = GetScreenToWorldRay(GetMousePosition(), camera);
        manager_select_obj(&mouse_ray);
        manager_move_selected_obj(&mouse_ray);


        BeginDrawing();
            ClearBackground(RAYWHITE);

            BeginShaderMode(shader);
                DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, BLACK);
            EndShaderMode();


            BeginMode3D(camera);
                DrawSphere((Vector3){0.0f, 0.0f, 0.0f}, .1, BLACK); // origin point

                manager_render_objects();

            EndMode3D();

            // 2d menu
            // manager_render_selected_obj_menu(&camera);


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

    manager_destroy_objects();

    UnloadShader(shader);
    CloseWindow();

    return 0;
}
