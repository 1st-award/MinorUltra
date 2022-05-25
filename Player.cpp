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

void Player::movePlayer() {
    if (IsKeyPressed(KEY_RIGHT)) {
        for (int i = 0; i < 100; i++) {
            playerPos.x += 0.01f;
        }
    }
    else if (IsKeyPressed(KEY_LEFT)) {
        for (int i = 0; i < 100; i++) {
            playerPos.x -= 0.01f;
        }
    }
    else if (IsKeyPressed(KEY_DOWN)) {
        for (int i = 0; i < 100; i++) {
            playerPos.z += 0.01f;
        }
    }
    else if (IsKeyPressed(KEY_UP)) {
        for (int i = 0; i < 100; i++) {
            playerPos.z -= 0.01f;
        }
    }
    return;
}
void Player::drawPlayer() {
    DrawCube(playerPos, playerSize, playerSize, playerSize, RED);
    DrawCubeWires(playerPos, playerSize, playerSize, playerSize, MAROON);
}
