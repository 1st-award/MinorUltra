//
// Created by Admin on 2022-05-25.
//

#ifndef MINORULTRA_PLAYER_H
#define MINORULTRA_PLAYER_H
#include "raylib.h"

class Player {
public:
    Player(float, float, float);
    void drawPlayer();
    void movePlayer(int keyCode);

private:
    Vector3 playerPos;
    float playerSize;
};


#endif //MINORULTRA_PLAYER_H
