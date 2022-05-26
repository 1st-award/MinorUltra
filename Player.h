//
// Created by Admin on 2022-05-25.
//

#ifndef MINORULTRA_PLAYER_H
#define MINORULTRA_PLAYER_H
#include "raylib.h"

class Player {
public:
    Player(int, int);
    void drawPlayer();
    void movePlayer();

private:
    Vector3 playerPos;
    float playerSize;
    int relativePosX;
    int relativePosZ;
    void limitMove();
};


#endif //MINORULTRA_PLAYER_H
