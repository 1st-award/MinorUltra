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

int getCenterPosX(char *text, int fontSize, int screenWidth) {
    return screenWidth / 2 - MeasureText(text, fontSize) / 2;
}


int main(void) {
    // My Initialization
    Converter::setMapLength(10, 10);
    //--------------------------------------------------------------------------------------
    // Player
    Player *player = new Player(70);
    int *playerRelativeArray = player->getRelativePlayerPos();
    int mineScanCount;
    char printDefuseKit[10];
    char printMineScanCount[10];
    char printScore[10];
    //--------------------------------------------------------------------------------------
    // Mine
    Mine *mine = new Mine(70);              //Mine(mineNum)
    mine->landMine(playerRelativeArray[0], playerRelativeArray[1]);
    //--------------------------------------------------------------------------------------
    // Timer
    Timer *timer = new Timer();                         // Start Timer
    timer->StartTimer(999.0f);                            // Set Timer
    char remainTime[30];
    char timeOut[] = "Time Out!!";
    //--------------------------------------------------------------------------------------
    // Others
    Color textColor = BLACK;
    int GAME_MODE = 0;   // default 0
    const int GAME_TITLE = 0;
    const int GAME_OVER = 1;
    const int GAME_WIN = 2;
    const int GAME_PLAY = 3;
    float fadeOut = 0.0f;
    bool pause = false;
    int frameCounter = 0;
    //--------------------------------------------------------------------------------------
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Minesweeper");

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
        // Global Key, Mouse Event
        if (IsKeyDown('Z')) timer->StartTimer(10.0f);
        if (CheckCollisionPointRec(GetMousePosition(), pauseBounds))
            if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
                if (pause) pause = false;
                else pause = true;
            }
        if (IsKeyPressed(KEY_Z)) GAME_MODE = GAME_WIN;  // temp key
        frameCounter += 1;
        //----------------------------------------------------------------------------------
        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();
        ClearBackground(RAYWHITE);
        if (GAME_MODE == GAME_TITLE) {
            // Game Title Display
            char titleText[] = "MineSweeper";
            char startText[] = "Press Enter to start";
            int titlePosX = getCenterPosX(titleText, 60, GetScreenWidth());
            int startPosX = getCenterPosX(startText, 30, GetScreenWidth());
            DrawText(titleText, titlePosX, screenHeight / 4, 60, GRAY);
            if ((frameCounter / 30) % 2) {
                DrawText(startText, startPosX, screenHeight / 1.5, 30, GRAY);
            }
            // Key Event
            if (IsKeyPressed(KEY_ENTER)) GAME_MODE = GAME_PLAY;
        }
        if (GAME_MODE == GAME_OVER) {
            // Game Over Display
            char ggTitleText[] = "GAME OVER";
            char ggSubTitleText[] = "You need more luck";
            int titlePosX = getCenterPosX(ggTitleText, 60, GetScreenWidth());
            int subtitlePosX = getCenterPosX(ggSubTitleText, 30, GetScreenWidth());
            BeginMode3D(camera);
            DrawGrid(10, 1.0f);
            player->drawPlayer();
            player->drawFocus();
            mine->drawMine();
            EndMode3D();
            DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Fade(RAYWHITE, fadeOut += 0.005f));
            DrawText(ggTitleText, titlePosX, screenHeight / 4, 60, GRAY);
            DrawText(ggSubTitleText, subtitlePosX, screenHeight / 2, 30, GRAY);
        }
        if (GAME_MODE == GAME_WIN) {
            // Game Win Display
            char winTitleText[] = "YOU WIN!!!";
            char scoreText[15] = "Score: ";
            sprintf_s(scoreText, "Score: %d", player->getScore());
            int winTitlePosX = getCenterPosX(winTitleText, 60, GetScreenWidth());
            int scorePosX = getCenterPosX(scoreText, 30, GetScreenWidth());
            DrawText(winTitleText, winTitlePosX, screenHeight / 4, 60, GRAY);
            DrawText(scoreText, scorePosX, screenHeight / 1.5, 30, GRAY);
        }
        if (GAME_MODE == GAME_PLAY) {
            // Game Play Display
            // Player Event
            if (IsKeyDown(KEY_SPACE)) {
                mineScanCount = player->checkMine(mine);
            } else mineScanCount = 0;
            if (IsKeyPressed((KEY_E))) player->defuseMine(mine);
            if (player->isStepOnMine(mine)) GAME_MODE = GAME_OVER;
            player->movePlayer();
            player->choiceFocus();
            //-------------------------------------------------------------------------------------
            // Draw 3D
            BeginMode3D(camera);
            // TODO 게임 타일 구현
            DrawGrid(10, 1.0f);
            // Player Draw
            player->drawFocus();
            player->drawPlayer();
            //--------------------------------------------------------------------------------------
            mine->drawMine(); // Test draw
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
                GAME_MODE = GAME_OVER;
            } else if (!pause) {
                timer->UpdateTimer();                  // Update Timer
            }
            sprintf_s(remainTime, "%.2f", timer->GetTimer());
            DrawText(remainTime, 20, 20, 10, textColor);
            //--------------------------------------------------------------------------------------
            // Score Widget
            sprintf_s(printScore, "%d", player->getScore());
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

