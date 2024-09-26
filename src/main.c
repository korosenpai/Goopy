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


    // prepare shader
    Shader shader = LoadShader(0, "shaders/ray_marcher.glsl");
    float resolution[2] = { SCREEN_WIDTH, SCREEN_HEIGHT };
    int resolutionLoc = GetShaderLocation(shader, "resolution");
    SetShaderValue(shader, resolutionLoc, resolution, SHADER_UNIFORM_VEC2);

    float ray_origin[3] = {0.0f, 0.0f, -3.0f};
    int rayOriginLoc = GetShaderLocation(shader, "ro");
    SetShaderValue(shader, rayOriginLoc, ray_origin, SHADER_UNIFORM_VEC3);

    float ray_direction[3] = {0.0f, 0.0f, -3.0f};
    int rayDirectionLoc = GetShaderLocation(shader, "rd");
    SetShaderValue(shader, rayDirectionLoc, ray_direction, SHADER_UNIFORM_VEC3);

    float time = 0;
    int timeLoc = GetShaderLocation(shader, "time");
    SetShaderValue(shader, timeLoc, &time, SHADER_UNIFORM_FLOAT);

    int mouseLoc = GetShaderLocation(shader, "mouse");
    float mouse_pos[2] = {0, 0};
    SetShaderValue(shader, mouseLoc, mouse_pos, SHADER_UNIFORM_VEC2);


    Camera3D camera = camera_create((Vector3){0.0f, 0.0f, 0.0f}, ray_origin);

    float camera_quaternion[4] = {0};
    Quaternion q = QuaternionFromMatrix(MatrixTranspose(GetCameraMatrix(camera)));
    camera_quaternion[0] = q.x;
    camera_quaternion[1] = q.y;
    camera_quaternion[2] = q.z;
    camera_quaternion[3] = q.w;
    int cameraQuaternionLoc = GetShaderLocation(shader, "camera_quaternion");
    SetShaderValue(shader, cameraQuaternionLoc, camera_quaternion, SHADER_UNIFORM_VEC4);
    
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

        camera_update(&camera);
        // printf("position: %f %f %f\n", camera.position.x, camera.position.y, camera.position.z);

        vector3_ptr_to_array(&camera.position, ray_origin);
        SetShaderValue(shader, rayOriginLoc, ray_origin, SHADER_UNIFORM_VEC3);

        SetShaderValue(shader, timeLoc, &time, SHADER_UNIFORM_FLOAT);

        vector2_to_array(GetMousePosition(), mouse_pos);
        SetShaderValue(shader, mouseLoc, mouse_pos, SHADER_UNIFORM_VEC2);

        vector3_to_array(Vector3Normalize(Vector3Subtract(camera.target, camera.position)), ray_direction);
        SetShaderValue(shader, rayDirectionLoc, ray_direction, SHADER_UNIFORM_VEC3);


        Quaternion q = QuaternionFromMatrix(MatrixTranspose(GetCameraMatrix(camera)));
        camera_quaternion[0] = q.x;
        camera_quaternion[1] = q.y;
        camera_quaternion[2] = q.z;
        camera_quaternion[3] = q.w;
        int cameraQuaternionLoc = GetShaderLocation(shader, "camera_quaternion");
        SetShaderValue(shader, cameraQuaternionLoc, camera_quaternion, SHADER_UNIFORM_VEC4);


        // collisions
        Ray mouse_ray = GetScreenToWorldRay(GetMousePosition(), camera);
        manager_select_obj(&mouse_ray);
        manager_move_selected_obj(&mouse_ray);


        BeginDrawing();
            ClearBackground(RAYWHITE);

            // raymarcher
            BeginShaderMode(shader);
                DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, BLACK);
            EndShaderMode();

            // if (!IsCursorHidden()) {
            if (1) {

                BeginMode3D(camera);
                    DrawSphere((Vector3){0.0f, 0.0f, 0.0f}, .1, BLACK); // origin point

                    manager_render_objects();

                EndMode3D();
            }

            // 2d menu
            // manager_render_selected_obj_menu(&camera);


            DrawFPS(SCREEN_WIDTH - 100, 20);

        EndDrawing();

        if (IsKeyPressed(KEY_M)) camera_toggle_mode();



    }

    manager_destroy_objects();

    UnloadShader(shader);
    CloseWindow();

    return 0;
}
