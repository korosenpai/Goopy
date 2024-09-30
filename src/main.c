#include <raylib.h>
#include <raymath.h>
#include <stdbool.h>
#include <stdio.h>

#include "camera/camera.h"
#include "constants.h"
#include "objects/objects.h"
#include "objects/objects_manager.h"
#include "utils/utils.h" // NOTE: bug in lsp, it is used
#include "utils/vectors/vector_operations.h"



int main(void) {

    SetTargetFPS(60);
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Goopy - 3d modeller");


    //////////////////////////// PREPARE SHADER ////////////////////
    Shader shader = LoadShader(0, "shaders/ray_marcher.glsl");

    float resolution[2] = { SCREEN_WIDTH, SCREEN_HEIGHT };
    int resolutionLoc = GetShaderLocation(shader, "resolution");
    SetShaderValue(shader, resolutionLoc, resolution, SHADER_UNIFORM_VEC2); // will only be set now

    float ray_origin[3] = {0.0f, 3.0f, -3.0f};
    int rayOriginLoc = GetShaderLocation(shader, "ro");

    float time = 0;
    int timeLoc = GetShaderLocation(shader, "time");

    int mouseLoc = GetShaderLocation(shader, "mouse");
    float mouse_pos[2] = {0, 0};

    //////////////////////////// PREPARE CAMERA ////////////////////

    Camera3D camera = camera_create((Vector3){0.0f, 0.0f, 0.0f}, ray_origin);

    float camera_quaternion[4] = {0};
    int cameraQuaternionLoc = GetShaderLocation(shader, "camera_quaternion");


    //////////////////////////// START ////////////////////

    manager_add_object(
        cube_create(
            (Vector3){1.0f, 1.0f, 0.0f},
            1, 1, 1, RED 
        )
    );
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

        camera_update(&camera);

        //////////////////////////// UPDATE SHADER UNIFORMS ////////////////////
        vector3_ptr_to_array(&camera.position, ray_origin);
        SetShaderValue(shader, rayOriginLoc, ray_origin, SHADER_UNIFORM_VEC3);

        SetShaderValue(shader, timeLoc, &time, SHADER_UNIFORM_FLOAT);

        vector2_to_array(GetMousePosition(), mouse_pos);
        SetShaderValue(shader, mouseLoc, mouse_pos, SHADER_UNIFORM_VEC2);


        camera_update_quaternion(&camera, camera_quaternion);
        SetShaderValue(shader, cameraQuaternionLoc, camera_quaternion, SHADER_UNIFORM_VEC4);


        //////////////////////////// FIGURE MOUSE COLLISIONS ////////////////////
        Ray mouse_ray = GetScreenToWorldRay(GetMousePosition(), camera);
        manager_select_obj(&mouse_ray);
        manager_move_selected_obj(&mouse_ray);


        //////////////////////////// RENDER ////////////////////

        BeginDrawing();
            ClearBackground(RAYWHITE);

            // raymarcher
            BeginShaderMode(shader);
                DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, BLACK);
            EndShaderMode();

            if (!IsCursorHidden()) {

                BeginMode3D(camera);
                    // DrawSphere((Vector3){0.0f, 0.0f, 0.0f}, .1, BLACK); // origin point

                    manager_render_objects();

                EndMode3D();
            }

            // 2d menu
            // manager_render_selected_obj_menu(&camera);


            DrawFPS(SCREEN_WIDTH - 100, 20);

        EndDrawing();

        //////////////////////////// HANDLE INPUTS ////////////////////

        if (IsKeyPressed(KEY_M)) camera_toggle_mode();



    }

    manager_destroy_objects();

    UnloadShader(shader);
    CloseWindow();

    return 0;
}
