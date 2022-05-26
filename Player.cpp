//
// Created by Admin on 2022-05-25.
//

#include "Player.h"
#include "Converter.h"

Player::Player(int playerPosX, int playerPosZ) {
    relativePosX = playerPosX;
    relativePosZ = playerPosZ;
    playerSize = 0.7f;
}

void Player::movePlayer() {
    if (IsKeyPressed(KEY_RIGHT)) {
        relativePosX += 1;
    } else if (IsKeyPressed(KEY_LEFT)) {
        relativePosX -= 1;
    } else if (IsKeyPressed(KEY_DOWN)) {
        relativePosZ += 1;
    } else if (IsKeyPressed(KEY_UP)) {
        relativePosZ -= 1;
    }
    Player::limitMove();
}

void Player::limitMove() {
    int *mapLengthArr = Converter::getMapLength();
    int maxPosX = mapLengthArr[0] - 1;
    int maxPosZ = mapLengthArr[1] - 1;

    if (relativePosX < 0)
        relativePosX = 0;
    if (relativePosX > maxPosX)
        relativePosX = maxPosX;
    if (relativePosZ < 0)
        relativePosZ = 0;
    if (relativePosZ > maxPosZ)
        relativePosZ = maxPosZ;
}

void Player::drawPlayer() {
    playerPos = Converter::translateToAbsolute(relativePosX, relativePosZ);
    DrawCube(playerPos, playerSize, playerSize, playerSize, RED);
    DrawCubeWires(playerPos, playerSize, playerSize, playerSize, MAROON);
}
