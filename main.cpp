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

int main(void) {
    // My Initialization
    Converter::setMapLength(10, 10);
    //--------------------------------------------------------------------------------------
    // Player
    Player *player = new Player(70);
    int *playerRelativeArray = player->getRelativePlayerPos();
    int mineScanCount = 0;
    char printDefuseKit[10];
    char printMineScanCount[10];
    //--------------------------------------------------------------------------------------
    // Mine
    Mine *mine = new Mine(70);              //Mine(mineNum)
    mine->landMine(playerRelativeArray[0], playerRelativeArray[1]);
    //--------------------------------------------------------------------------------------
    // Timer
    Timer *timer = new Timer();                         // Start Timer
    timer->StartTimer(5.0f);                            // Set   Timer
    char remainTime[30];
    char timeOut[] = "Time Out!!";
    //--------------------------------------------------------------------------------------
    // Score
    Score *score = new Score();
    Color textColor = BLACK;
    char printScore[10];
    //--------------------------------------------------------------------------------------
    // Others
    int GAME_MODE = 3;
    const int GAME_TITLE = 0;
    const int GAME_OVER = 1;
    const int GAME_WIN = 2;
    const int GAME_PLAY = 3;
    bool pause = false;
    int frameCounter = 0;
    //--------------------------------------------------------------------------------------
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - 3d camera free");

    // Define the camera to look into our 3d world
    Camera3D camera = {0};
    camera.position = Vector3{0.0f, 15.0f, 0.0f}; // Camera position
    camera.target = Vector3{0.0f, 0.0f, 0.0f};      // Camera looking at point
    camera.up = Vector3{0.0f, 1.0f, 0.0f};          // Camera up vector (rotation towards target)
    camera.fovy = 45.0f;                                // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;                   // Camera mode type
    SetCameraMode(camera, CAMERA_FREE); // Set a free camera mode
    //--------------------------------------------------------------------------------------
    // Frame
    SetTargetFPS(60);                   // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------
    // Load Texture
    Texture2D pauseTexture = LoadTexture("../ resource/pause.png");
    Rectangle pauseBounds = {750, 150, (float) pauseTexture.width, (float) pauseTexture.height};
    //--------------------------------------------------------------------------------------
    // Main game loop
    while (!WindowShouldClose())        // Detect window close button or ESC key
    {
        // Update
        UpdateCamera(&camera);
        if (timer->GetTimer() < 5)
            textColor = RED;
        else
            textColor = BLACK;
        //----------------------------------------------------------------------------------
        // Key, Mouse Event
        if (IsKeyDown('Z')) timer->StartTimer(10.0f);
        if (IsKeyPressed((KEY_E))) player->defuseBomb(mine);
        if (CheckCollisionPointRec(GetMousePosition(), pauseBounds))
            if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
                if (pause) pause = false;
                else pause = true;
            }
        mineScanCount = player->checkMine(mine);
        frameCounter += 1;
        //----------------------------------------------------------------------------------
        //Player move
        player->movePlayer();
        player->choiceFocus();
        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();
        ClearBackground(RAYWHITE);
        if (GAME_MODE == GAME_TITLE) {
            // Game Title Display
            // TODO 게임 타이틀 구현

        }
        if (GAME_MODE == GAME_OVER) {
            // TODO 게임 오버 구현

        }
        if (GAME_MODE == GAME_WIN) {
            // TODO 게임 승리 구현

        }
        if (GAME_MODE == GAME_PLAY) {
            // Game Play Display
            // Draw 3D
            BeginMode3D(camera);
            // TODO 게임 타일 구현

            DrawGrid(10, 1.0f);
            player->drawFocus();
            player->drawPlayer();
            // mine->drawMine(); // Test draw
            EndMode3D();
            //--------------------------------------------------------------------------------------
            // Widget
            // Mine Widget
            sprintf_s(printMineScanCount, "%d", mineScanCount);
            DrawText(printMineScanCount, 20, 40, 30, GRAY);
            //--------------------------------------------------------------------------------------
            // Time Widget
            if (timer->TimeDone()) {
                DrawText(timeOut, 20, 20, 10, textColor);
            } else {
                timer->UpdateTimer();                  // Update Timer
                sprintf_s(remainTime, "%.2f", timer->GetTimer());
                DrawText(remainTime, 20, 20, 10, textColor);
            }
            //--------------------------------------------------------------------------------------
            // Score Widget
            sprintf_s(printScore, "%d", score->getScore());
            DrawText(printScore, 750, 20, 10, textColor);
            //--------------------------------------------------------------------------------------
            // DefuseCount Widget
            sprintf_s(printDefuseKit, "%d", player->getDefuseKit());
            DrawText(printDefuseKit, 750, 50, 10, textColor);
            //--------------------------------------------------------------------------------------
            // MineScanCount Widget
            // TODO 마인 스캔 위젯 (우석)

            //--------------------------------------------------------------------------------------
            // Pause Widget
            DrawTexture(pauseTexture, 750, 150, WHITE);
            if (pause && ((frameCounter / 30) % 2)) DrawText("PAUSED", 350, 200, 30, GRAY);
            //--------------------------------------------------------------------------------------
            //--------------------------------------------------------------------------------------
        }
        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadTexture(pauseTexture);
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}