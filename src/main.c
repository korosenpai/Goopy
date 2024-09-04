#include "raylib.h"

int main(void) {
    const int SCREEN_WIDTH = 1600;
    const int SCREEN_HEIGHT = 900;

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Goopy - 3d modeller");
    SetTargetFPS(60);

    // prepare shader
    Shader shader = LoadShader(0, "shaders/fragmentShader.glsl");
    int resolutionLoc = GetShaderLocation(shader, "resolution");


    float resolution[2] = { SCREEN_WIDTH, SCREEN_HEIGHT };

    SetShaderValue(shader, resolutionLoc, resolution, SHADER_UNIFORM_VEC2);

    // Define the camera to look into our 3d world
    Camera3D camera = { 0 };
    camera.position = (Vector3){ 0.0f, 10.0f, 10.0f };
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
    camera.fovy = 45.0f;
    camera.projection = CAMERA_PERSPECTIVE;


    // Main game loop
    while (!WindowShouldClose()) { // esc to exit

        BeginDrawing();
            ClearBackground(RAYWHITE);

            BeginShaderMode(shader);
                DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, BLACK);
            EndShaderMode();

            BeginMode3D(camera);
                DrawSphereWires((Vector3){10.0f, 0.0f, 0.0f}, 2.0f, 16, 16, BLACK);
            EndMode3D();

        EndDrawing();
    }

    UnloadShader(shader);
    CloseWindow();

    return 0;
}
