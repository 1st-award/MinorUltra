//
// Created by Admin on 2022-05-25.
//

#include "Player.h"

Player::Player(float x, float y, float z) {
    playerPos.x = x;
    playerPos.y = y;
    playerPos.z = z;
    playerSize = 0.7f;
}

void Player::movePlayer(int keyCode) {
    return;
}

void Player::drawPlayer() {
    DrawCube(playerPos, playerSize, playerSize, playerSize, RED);
    DrawCubeWires(playerPos, playerSize, playerSize, playerSize, MAROON);
}
