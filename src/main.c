#include <raylib.h>
#include <raymath.h>
#include <stdbool.h>
#include <stdio.h>

#include "collisions.h"
#include "constants.h"
#include "objects.h"


int main(void) {

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Goopy - 3d modeller");
    SetTargetFPS(60);

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
    Vector3 prev_mouse_pos = {0};

    // https://www.raylib.com/examples/models/loader.html?name=models_mesh_picking hit object

    Sphere sphere = (Sphere) {
        .position = origin,
        .radius = 2.0f,
        .color = BLACK,
    };

    Cube x_axis = (Cube) {
        .position = Vector3Add(origin, (Vector3){0.5, 0, 0}),
        .width = 1,
        .height = 0.1,
        .length = 0.1,
        .color = RED
    };
    Cube y_axis = (Cube) {
        .position = Vector3Add(origin, (Vector3){0, 0.5, 0}),
        .width = 0.1,
        .height = 1,
        .length = 0.1,
        .color = GREEN
    };

    // Main game loop
    while (!WindowShouldClose()) { // esc to exit

        UpdateCamera(&camera, camera_mode);


        // collisions
        Ray ray = GetScreenToWorldRay(GetMousePosition(), camera);
        RayCollision sphere_hit_info = GetRayCollisionSphere(ray, sphere.position, sphere.radius) ;

        RayCollision x_axis_hit = get_ray_collision_cube(&ray, &x_axis);
        RayCollision y_axis_hit = get_ray_collision_cube(&ray, &x_axis);


        if (x_axis_hit.hit && IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            x_axis.position.x += x_axis_hit.point.x - prev_mouse_pos.x;
            y_axis.position.x += x_axis_hit.point.x - prev_mouse_pos.x;
            sphere.position.x += x_axis_hit.point.x - prev_mouse_pos.x;
        }
        if (x_axis_hit.hit) {
            prev_mouse_pos = x_axis_hit.point;
        }

        BeginDrawing();
            ClearBackground(RAYWHITE);

            // BeginShaderMode(shader);
            //     DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, BLACK);
            // EndShaderMode();

            BeginMode3D(camera);
                DrawSphere(origin, .1, MAGENTA);
                DrawSphereWires(sphere.position, sphere.radius, 16, 16, sphere.color );

                if (is_cursor_enabled && sphere_hit_info.hit) {
                    DrawSphereWires(sphere.position, sphere.radius, 16, 16, GOLD);
                }

                // y axis
                // when selected. highlight with gold (draw lines) (when moving rectangle)
                DrawCube(
                    y_axis.position, y_axis.width, y_axis.height, y_axis.length, y_axis.color
                );
                if (is_cursor_enabled && x_axis_hit.hit) {
                    DrawCube(
                        y_axis.position, y_axis.width, y_axis.height, y_axis.length, y_axis.color
                    );
                }

                // x axis
                DrawCube(
                    x_axis.position, x_axis.width, x_axis.height, x_axis.length, x_axis.color
                );
                if (is_cursor_enabled && x_axis_hit.hit) {
                    DrawCube(
                        x_axis.position, x_axis.width, x_axis.height, x_axis.length, GOLD
                    );
                }

                // z axis
                // NOTE: z axis grows going out of screen, opposite of shader
                // find way to make shader go with this
                DrawCube(
                    Vector3Add(origin, (Vector3){0, 0, 0.5}),
                    0.1, 0.1, 1, BLUE 
                );
            EndMode3D();

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
