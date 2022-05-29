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

typedef struct widgetByDifficult {
    Vector2 screenSize;
    Vector2 remainMineTexture;
    Vector2 remainMineWidget;
    Vector2 timeTexture;
    Vector2 timeWidget;
    Vector2 scoreTexture;
    Vector2 scoreWidget;
    Vector2 defuseCountTexture;
    Vector2 defuseCountWidget;
    Vector2 mineScanTexture;
    Vector2 mineScanWidget;
    Vector2 pauseTexture;
    Vector2 pauseWidget;
} widgetByDifficult;

typedef struct widgetParameterStruct{
    char *remainMine;
    char *timeOut;
    char *remainTime;
    char *printScore;
    char *printDefuseKit;
    char *printMineScanCount;
} widgetParameterStruct;

typedef struct textureStruct{
    Texture remainMineTexture;
    Texture timeTexture;
    Texture scoreTexture;
    Texture defuseKitTexture;
    Texture mineScanTexture;
    Texture pauseTexture;
} textureStruct;

void drawWidget(widgetByDifficult widgetPerDifficult, widgetParameterStruct widgetParameter,textureStruct textureArray, Timer *timer, bool pause, int frameCounter, Color textColor){
    SetWindowSize(widgetPerDifficult.screenSize.x, widgetPerDifficult.screenSize.y);
    // Widget
    // Mine Widget
    DrawTexture(textureArray.remainMineTexture, widgetPerDifficult.remainMineTexture.x, widgetPerDifficult.remainMineTexture.y, WHITE);
    DrawText(widgetParameter.remainMine, widgetPerDifficult.remainMineWidget.x, widgetPerDifficult.remainMineWidget.y, 20, GRAY);
    //--------------------------------------------------------------------------------------
    // Time Widget
    DrawTexture(textureArray.timeTexture, widgetPerDifficult.timeTexture.x, widgetPerDifficult.timeTexture.y, WHITE);
    if (!pause) {
        timer->UpdateTimer();                  // Update Timer
    }
    if (timer->TimeDone())
        DrawText(widgetParameter.timeOut, widgetPerDifficult.timeWidget.x, widgetPerDifficult.timeWidget.y, 20, textColor);
    else {
        DrawText(widgetParameter.remainTime, widgetPerDifficult.timeWidget.x, widgetPerDifficult.timeWidget.y, 20, textColor);
    }
    //--------------------------------------------------------------------------------------
    // Score Widget
    DrawTexture(textureArray.scoreTexture, widgetPerDifficult.scoreTexture.x, widgetPerDifficult.scoreTexture.y, WHITE);
    DrawText(widgetParameter.printScore, widgetPerDifficult.scoreWidget.x, widgetPerDifficult.scoreWidget.y, 20, textColor);
    //--------------------------------------------------------------------------------------
    // DefuseCount Widget
    DrawTexture(textureArray.defuseKitTexture, widgetPerDifficult.defuseCountTexture.x, widgetPerDifficult.defuseCountTexture.y, WHITE);
    DrawText(widgetParameter.printDefuseKit, widgetPerDifficult.defuseCountWidget.x, widgetPerDifficult.defuseCountWidget.y, 20, textColor);
    //--------------------------------------------------------------------------------------
    // MineScanCount Widget
    // TODO 마인 스캔 위젯 (우석)
    DrawTexture(textureArray.mineScanTexture, widgetPerDifficult.mineScanTexture.x, widgetPerDifficult.mineScanTexture.y, WHITE);
    DrawText(widgetParameter.printMineScanCount, widgetPerDifficult.mineScanWidget.x, widgetPerDifficult.mineScanWidget.y, 30, GRAY);
    //--------------------------------------------------------------------------------------
    // Pause Widget
    DrawTexture(textureArray.pauseTexture, widgetPerDifficult.pauseTexture.x, widgetPerDifficult.pauseTexture.y, WHITE);
    if (pause && ((frameCounter / 30) % 2)) DrawText("PAUSED", widgetPerDifficult.pauseWidget.x, widgetPerDifficult.pauseWidget.y, 30, GRAY);
    //--------------------------------------------------------------------------------------
}

int main(void) {
    // My Initialization
    // Struct widgetByDifficult setting
    widgetByDifficult widgetPerDifficult[4];
    widgetPerDifficult[0] = {Vector2{450, 550},
                             Vector2{0,10}, Vector2{35, 20},
                             Vector2{210,0}, Vector2{195, 35},
                             Vector2{400,0}, Vector2{400, 35},
                             Vector2{65,10}, Vector2{100, 20},
                             Vector2{210,510}, Vector2{245,510},
                             Vector2{0, 510}, Vector2{165, 250}};
    widgetParameterStruct widgetParameter;
    textureStruct textureArray;
    //--------------------------------------------------------------------------------------
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
    char remainMine[10];
    //--------------------------------------------------------------------------------------
    // Timer
    Timer *timer = new Timer();                         // Start Timer
    timer->StartTimer(999.0f);                            // Set Timer
    char remainTime[30];
    char timeOut[] = "Time Out!!";
    //--------------------------------------------------------------------------------------
    // Others
    Color textColor = BLACK;
    unsigned int GAME_MODE = 0;   // default 0
    unsigned int GAME_DIFF = 0;
    const int GAME_TITLE = 0;
    const int GAME_SELECT = 1;
    const int GAME_OVER = 2;
    const int GAME_WIN = 3;
    const int GAME_PLAY = 4;
    float fadeOut = 0.0f;
    bool pause = false;
    bool SoundExplode = false;
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
    Texture2D remainMineTexture = LoadTexture("../resources/mine.png");
    Texture2D timeTexture = LoadTexture("../resources/time.png");
    Texture2D scoreTexture = LoadTexture("../resources/score.png");
    Texture2D defuseKitTexture = LoadTexture("../resources/defusekit.png");
    Texture2D mineScanTexture = LoadTexture("../resources/minescan.png");
    Texture2D pauseTexture = LoadTexture("../resources/pause.png");
    textureArray.remainMineTexture = remainMineTexture;
    textureArray.timeTexture = timeTexture;
    textureArray.scoreTexture = scoreTexture;
    textureArray.defuseKitTexture = defuseKitTexture;
    textureArray.mineScanTexture = mineScanTexture;
    textureArray.pauseTexture = pauseTexture;
    Rectangle pauseBounds = {widgetPerDifficult[0].pauseTexture.x, widgetPerDifficult[0].pauseTexture.y, (float) pauseTexture.width, (float) pauseTexture.height};
    //--------------------------------------------------------------------------------------
    // Load Audio
    // https://soundspunos.com/audio/421-sounds-from-video-games-8-bit.html
    InitAudioDevice();      // Initialize audio device
    SetMasterVolume(0.3);
    Sound pressKeySound = LoadSound("../resources/presskey.mp3");
    Sound moveSound = LoadSound("../resources/move.mp3");         // Load WAV audio file
    Sound explodeSound = LoadSound("../resources/explosion.mp3");
    Sound foundMineSound = LoadSound("../resources/foundmine.mp3");
    Sound enterSound = LoadSound("../resources/enter.mp3");
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
        if (IsKeyPressed(KEY_F1)) GAME_MODE = GAME_TITLE;  // temp key
        if (IsKeyPressed(KEY_F2)) GAME_MODE = GAME_SELECT;  // temp key
        if (IsKeyPressed(KEY_F3)) GAME_MODE = GAME_PLAY;  // temp key
        if (IsKeyPressed(KEY_F4)) GAME_MODE = GAME_WIN;  // temp key
        if (IsKeyPressed(KEY_F5)) GAME_MODE = GAME_OVER;  // temp key
        frameCounter += 1;
        //----------------------------------------------------------------------------------
        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();
        if (GAME_MODE != GAME_OVER) ClearBackground(RAYWHITE);
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
            if (IsKeyReleased(KEY_ENTER)) {
                PlaySound(enterSound);
                GAME_MODE = GAME_SELECT;
            }
        }
        if (GAME_MODE == GAME_SELECT) {
            float rectLineWidth = screenWidth * 0.6f;
            float rectLineHeight = screenHeight * 0.6f;
            float rectLinePosX = screenWidth / 2 - rectLineWidth / 2;
            float rectLinePosY = screenHeight / 2 - rectLineHeight / 2;
            char* difficult[] = {"EASY", "NORMAL", "HARD", "INSANE"};
            int diffPosX;
            int diffPosY = screenWidth / 6;
            Rectangle rect{ rectLinePosX, rectLinePosY, rectLineWidth, rectLineHeight};
            DrawRectangleLinesEx(rect, 6, BLACK);

            if (IsKeyPressed(KEY_LEFT)) {
                PlaySoundMulti(pressKeySound);
                GAME_DIFF -= 1;
            }
            if (IsKeyPressed(KEY_RIGHT)) {
                PlaySoundMulti(pressKeySound);
                GAME_DIFF += 1;
            }
            if (IsKeyDown(KEY_ENTER)){
                PlaySound(enterSound);
                GAME_MODE = GAME_PLAY;
            }
            diffPosX = getCenterPosX(difficult[GAME_DIFF%4], 40, GetScreenWidth());
            DrawText(difficult[GAME_DIFF%4], diffPosX, diffPosY, 40, BLACK);
        }
        if (GAME_MODE == GAME_OVER) {
            // Game Over Display
            char ggTitleText[] = "GAME OVER";
            char ggSubTitleText[] = "You need more luck";
            char score[15];
            sprintf_s(score, "Score: %d", player->getScore());
            int titlePosX = getCenterPosX(ggTitleText, 60, GetScreenWidth());
            int subtitlePosX = getCenterPosX(ggSubTitleText, 30, GetScreenWidth());
            int scorePosX = getCenterPosX(score, 30, GetScreenWidth());
            DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Fade(RAYWHITE, fadeOut += 0.001f));
            DrawText(ggTitleText, titlePosX, screenHeight / 4, 60, GRAY);
            DrawText(ggSubTitleText, subtitlePosX, screenHeight / 2.5, 30, GRAY);
            DrawText(score, scorePosX, screenHeight / 1.5, 30, GRAY);
            if (!SoundExplode) {
                PlaySoundMulti(explodeSound);
                SoundExplode = true;
            }
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
            if (player->isStepOnMine(mine) || ((mine->getMineNumber()) > 0 && (player->getDefuseKit() < 1)) || timer->TimeDone()) GAME_MODE = GAME_OVER;
            if (!mine->getMineNumber()) GAME_MODE = GAME_WIN;
            if (IsKeyDown(KEY_SPACE)) {
                mineScanCount = player->checkMine(mine);
            } else mineScanCount = 0;
            if (IsKeyPressed((KEY_E))) player->defuseMine(mine, foundMineSound);
            player->movePlayer(moveSound);
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
            sprintf_s(remainMine, "%d", mine->getMineNumber());
            widgetParameter.remainMine = remainMine;
            //--------------------------------------------------------------------------------------
            // Time Widget
            sprintf_s(remainTime, "%.2f", timer->GetTimer());
            widgetParameter.remainTime = remainTime;
            widgetParameter.timeOut = timeOut;
            //--------------------------------------------------------------------------------------
            // Score Widget
            sprintf_s(printScore, "%d", player->getScore());
            widgetParameter.printScore = printScore;
            //--------------------------------------------------------------------------------------
            // DefuseCount Widget
            sprintf_s(printDefuseKit, "%d", player->getDefuseKit());
            widgetParameter.printDefuseKit = printDefuseKit;
            //--------------------------------------------------------------------------------------
            // 주위 마인
            sprintf_s(printMineScanCount, "%d", mineScanCount);
            widgetParameter.printMineScanCount = printMineScanCount;
            //--------------------------------------------------------------------------------------
            // Draw Widget
            drawWidget(widgetPerDifficult[0], widgetParameter, textureArray, timer, pause, frameCounter, textColor);
            //--------------------------------------------------------------------------------------
            if (timer->TimeDone()) {
                GAME_MODE = GAME_OVER;
            }
            //--------------------------------------------------------------------------------------
        }
        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    // Texture
    UnloadTexture(pauseTexture);
    // Sound
    UnloadSound(moveSound);
    UnloadSound(explodeSound);
    UnloadSound(foundMineSound);
    UnloadSound(enterSound);
    UnloadSound(pressKeySound);
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}

