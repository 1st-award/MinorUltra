//
// Created by Admin on 2022-05-25.
//

#ifndef MINORULTRA_PLAYER_H
#define MINORULTRA_PLAYER_H
#include "raylib.h"
#include "Mine.h"
#include "Score.h"
#include "DefuseKit.h"

class Player: public DefuseKit, Score {
public:
    Player(int);
    void drawPlayer();
    void movePlayer();
    void drawFocus();
    void choiceFocus();
    void defuseMine(Mine*);
    bool isStepOnMine(Mine*);
    int checkMine(Mine*);
    int getScore();
    int* getRelativePlayerPos();

private:
    Vector3 playerPos;
    float playerSize;
    int relativePosX;
    int relativePosZ;
    int relativeFocusX;
    int relativeFocusZ;
    void limitMove();
    void limitFocus();
    void setRandomSpawn();
};

#endif //MINORULTRA_PLAYER_H