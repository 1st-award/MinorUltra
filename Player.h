//
// Created by Admin on 2022-05-25.
//

#ifndef MINORULTRA_PLAYER_H
#define MINORULTRA_PLAYER_H
#include "raylib.h"
#include "Mine.h"

class Player {
public:
    Player(int, int);
    void drawPlayer();
    void movePlayer();
    void drawFocus();
    void choiceFocus();
    bool isStepOnMine(Mine*);
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
};


#endif //MINORULTRA_PLAYER_H
