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
#include "Mine.h"
#include "Score.h"

Color check = GREEN;
int count = 0;
void Player::DrawPlayerSide() {
    Mine mine(70, 10, 10);
    bool collision = false;
    Vector3 cubePosition = { playerPos.x, 0.0f, playerPos.z };
    if (IsKeyDown(KEY_SPACE)) {
        DrawCube(cubePosition, 3.0f, -0.1f, 3.0f, check);
    }
    for (int i = 0; i < 70; i++) {
        if (CheckCollisionBoxes(
            BoundingBox{
            Vector3 {
            cubePosition.x - 1.0f / 2,
                cubePosition.y - 1.0f / 2,
                cubePosition.z - 1.0f / 2
        },
                Vector3 {
                cubePosition.x + 1.0f / 2,
                    cubePosition.y + 1.0f / 2,
                    cubePosition.z + 1.0f / 2
            }
            },
            BoundingBox{
            Vector3 {
            mine.CopyminePos[i].x - mine.CopyminePos[i].x / 2,
                mine.CopyminePos[i].y - mine.CopyminePos[i].y / 2,
                mine.CopyminePos[i].z - mine.CopyminePos[i].z / 2
        },
                Vector3 {
                mine.CopyminePos[i].x + mine.CopyminePos[i].x / 2,
                    mine.CopyminePos[i].y + mine.CopyminePos[i].y / 2,
                    mine.CopyminePos[i].z + mine.CopyminePos[i].z / 2
            }
            })) collision = true;
        if(collision == true)count += 1;
    }
}
int main(void)
{
    // My Initialization
    Player* player = new Player(-0.5f, 0.0f, -0.5f);
    Timer* timer = new Timer();                         // Start Timer
    timer->StartTimer(5.0f);                            // Set   Timer
    char remainTime[30];
    char timeOut[] = "Time Out!!";
    Color textColor = BLACK;
    Mine* mine = new Mine(70, 10, 10);              //Mine(mineNum, mapBlockX, mapBlockY)
    mine->landMine(4, 4);
    Score* score = new Score();
    char printScore[10];
    char printCheck[50];
    //--------------------------------------------------------------------------------------
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - 3d camera free");

    // Define the camera to look into our 3d world
    Camera3D camera = { 0 };
    camera.position = Vector3{ 0.0f, 15.0f, 0.0f }; // Camera position
    camera.target = Vector3{ 0.0f, 0.0f, 0.0f };      // Camera looking at point
    camera.up = Vector3{ 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
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
        //Player move
        player->movePlayer();
        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(RAYWHITE);

        BeginMode3D(camera);

        DrawGrid(10, 1.0f);
        player->drawPlayer();
        mine->drawMine();
        player->DrawPlayerSide();

        EndMode3D();
        sprintf_s(printCheck, " %d", count);
        DrawText(printCheck, 20, 50, 30, GRAY);
        if (IsKeyUp(KEY_SPACE)) {
            count = 0;
        }
        // Time Draw
        if (timer->TimeDone()) {
            DrawText(timeOut, 20, 20, 10, textColor);
        }
        else {
            timer->UpdateTimer();                  // Update Timer
            sprintf_s(remainTime, "%.2f", timer->GetTimer());
            DrawText(remainTime, 20, 20, 10, textColor);
        }
        // End Time draw
        // Score Draw
        sprintf_s(printScore, "%d", score->getScore());
        DrawText(printScore, 750, 20, 10, textColor);
        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}