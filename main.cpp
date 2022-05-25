/*******************************************************************************************
*
*   raylib [core] example - Initialize 3d camera free
*
*   This example has been created using raylib 1.3 (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
*   Copyright (c) 2015 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include <iostream>
#include "raylib.h"
#include "Player.h"
#include "Timer.h"

int main(void)
{
    // My Initialization
    Player* player = new Player(-0.5f, 0.0f, -0.5f);
    Timer* timer = new Timer();                         // Start Timer
    timer->StartTimer(5.0f);                            // Set   Timer
    char* remainTime;
    char timeOut[] = "Time Out!!";
    Color textColor = BLACK;

    //--------------------------------------------------------------------------------------
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - 3d camera free");

    // Define the camera to look into our 3d world
    Camera3D camera = { 0 };
    camera.position = (Vector3){ 10.0f, 10.0f, 10.0f }; // Camera position
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };      // Camera looking at point
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
    camera.fovy = 45.0f;                                // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;                   // Camera mode type

    Vector3 cubePosition = { 0.0f, 0.0f, 0.0f };

    SetCameraMode(camera, CAMERA_FREE); // Set a free camera mode

    SetTargetFPS(60);                   // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())        // Detect window close button or ESC key
    {
        // Update
        UpdateCamera(&camera);
        if(timer->GetTimer() < 5)
            textColor = RED;
        else
            textColor = BLACK;

        //----------------------------------------------------------------------------------
        if (IsKeyDown('Z')) timer->StartTimer(10.0f);

        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(RAYWHITE);

        BeginMode3D(camera);

        DrawGrid(10, 1.0f);
        player->drawPlayer();

        EndMode3D();
        if (timer->TimeDone()) {
            DrawText(timeOut, 20, 20, 10, textColor);
        }
        else {
            timer->UpdateTimer();                  // Update Timer
            sprintf(remainTime, "%.2f", timer->GetTimer());
            DrawText(remainTime, 20, 20, 10, textColor);
        }
        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}