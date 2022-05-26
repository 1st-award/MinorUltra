//
// Created by Admin on 2022-05-25.
//

#include "Player.h"

Player::Player(float x, float y, float z) {
    playerPos.x = x;
    playerPos.y = y;
    playerPos.z = z;
    playerSize = 0.7f;
    
    Vector3 cubePosition { playerPos.x, 0.0f, playerPos.z };
}

void Player::movePlayer() {
    if (IsKeyPressed(KEY_RIGHT)) {
            playerPos.x += 1.0f;
    }
    else if (IsKeyPressed(KEY_LEFT)) {
            playerPos.x -= 1.0f;
    }
    else if (IsKeyPressed(KEY_DOWN)) {
            playerPos.z += 1.0f;
    }
    else if (IsKeyPressed(KEY_UP)) {
            playerPos.z -= 1.0f;
    }
    return;
}
void Player::drawPlayer() {
    DrawCube(playerPos, playerSize, playerSize, playerSize, RED);
    DrawCubeWires(playerPos, playerSize, playerSize, playerSize, MAROON);
}
