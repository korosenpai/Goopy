#include <raylib.h>
#include <raymath.h>
#include <stdbool.h>
#include <stdio.h>

#include "constants.h"
#include "camera/camera.h"
#include "mouse/mouse.h"
#include "config_state/config_state.h"

#include "objects/obj_modifier.h"
#include "objects/objects.h"
#include "objects/objects_manager.h"
#include "shader_manager/shader_manager.h"

#include "ui/ui.h"
#include "utils/utils.h" // NOTE: bug in lsp, it is used
#include "utils/vectors/vector_operations.h"



int main(void) {

    SetTargetFPS(60);
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Goopy - 3d modeller");


    //////////////////////////// PREPARE SHADER ////////////////////
    Shader shader = LoadShader(0, "shaders/ray_marcher.glsl");

    shader_setup(&shader);

    float resolution[2] = { SCREEN_WIDTH, SCREEN_HEIGHT };
    int resolutionLoc = GetShaderLocation(shader, "resolution");
    SetShaderValue(shader, resolutionLoc, resolution, SHADER_UNIFORM_VEC2); // will only be set now

    float ray_origin[3] = {0.0f, 3.0f, -3.0f};
    int rayOriginLoc = GetShaderLocation(shader, "ro");

    float time = 0;
    int timeLoc = GetShaderLocation(shader, "time");

    int mouseLoc = GetShaderLocation(shader, "mouse");
    float mouse_pos[2] = {0, 0};

    //////////////////////////// PREPARATIONS ////////////////////

    Camera3D camera = camera_create((Vector3){0.0f, 0.0f, 0.0f}, ray_origin);

    float camera_quaternion[4] = {0};
    int cameraQuaternionLoc = GetShaderLocation(shader, "camera_quaternion");

    ConfigurationState config_state = config_state_create();

    ui_init();

    Mouse mouse = mouse_create();

    //////////////////////////// START ////////////////////


    manager_add_object(
        &shader,
        cube_create(
            (Vector3){1.0f, 1.0f, 0.0f},
            1, 2, 3, RED 
        )
    );
    manager_add_object(
        &shader,
        cube_create(
            (Vector3){-3.0f, 1.0f, 2.0f},
            1, 1, 1, RED 
        )
    );
    manager_add_object(
        &shader,
        sphere_create((Vector3){2, 3, 5}, 2.0f, VIOLET)
    );
    manager_add_object(
        &shader,
        sphere_create((Vector3){0}, 1.0f, RED)
    );


    // Main game loop
    while (!WindowShouldClose()) { // esc to exit
        // deltatime = GetFrameTime();
        time = GetTime();

        mouse_update(&mouse);

        camera_update(&camera);

        manager_reset_obj_update();

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



        //////////////////////////// RENDER ////////////////////

        BeginDrawing();
            ClearBackground(RAYWHITE);


            // raymarcher on whole screen
            BeginShaderMode(shader);
                DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, BLACK);
            EndShaderMode();

            if (!IsCursorHidden()) {

                BeginMode3D(camera);

                    manager_render_objects();

                    // draw preview of where center of obj will be placed
                    // TODO: add better
                    if (config_state.edit_mode == CREATE) {
                        DrawSphereWires(
                            Vector3Add(
                                mouse_ray.position, 
                                Vector3Scale(mouse_ray.direction, config_state.obj_placing_distance)
                            ),
                            SPHERE_DEFAULT_RADIUS, 8, 8, GOLD 
                        );

                    }

                EndMode3D();
            }

            // 2d menu
            ui_render_and_update(&config_state, &mouse);


            // FPS screen
            DrawRectangle(SCREEN_WIDTH - 120, 10, 110, 40, BLACK);
            DrawFPS(SCREEN_WIDTH - 100, 20);



        EndDrawing();


        //////////////////////////// HANDLE INPUTS ////////////////////

        if (IsKeyPressed(KEY_M)) camera_toggle_mode();

        if (config_state.camera_mode == STILL) {

            if (IS_LEFT_MOUSE_DOWN(mouse) && config_state.edit_mode == EDIT) {
                manager_select_obj(&mouse_ray);
                manager_move_selected_obj(&mouse_ray);
            }
            else if (IS_LEFT_MOUSE_RELEASED(mouse) && config_state.edit_mode == CREATE) {
                Object new_object = modifier_create_object(
                    &mouse_ray, &config_state.selected_shape, &config_state.obj_placing_distance
                );

                if (new_object.type != OBJECT_NONE) {
                    manager_add_object(&shader, new_object);
                }


            }
        }

    }

    //////////////////////////// UNLOAD AND CLOSE ////////////////////

    manager_destroy_objects();
    shader_close();
    ui_close();

    UnloadShader(shader);
    CloseWindow();

    return 0;
}
