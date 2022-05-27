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
int Player::checkMine(Mine* mine) {
    int result = 0;
    bool count[8]{};
    if (IsKeyDown(KEY_SPACE)) {
        count[0] = mine->checkMinePos(relativePosX - 1, relativePosZ - 1);
        count[1] = mine->checkMinePos(relativePosX, relativePosZ - 1);
        count[2] = mine->checkMinePos(relativePosX + 1, relativePosZ - 1);
        count[3] = mine->checkMinePos(relativePosX - 1, relativePosZ);
        count[4] = mine->checkMinePos(relativePosX + 1, relativePosZ);
        count[5] = mine->checkMinePos(relativePosX - 1, relativePosZ + 1);
        count[6] = mine->checkMinePos(relativePosX, relativePosZ + 1);
        count[7] = mine->checkMinePos(relativePosX + 1, relativePosZ + 1);
        for (int i = 0; i < 8; i++) {
            if (count[i] == false) {
                result += 1;
            }
        }
        return result;
    }
}
void Player::movePlayer() {
    if (IsKeyPressed(KEY_RIGHT)) {
        relativePosX += 1;
    }
    else if (IsKeyPressed(KEY_LEFT)) {
        relativePosX -= 1;
    }
    else if (IsKeyPressed(KEY_DOWN)) {
        relativePosZ += 1;
    }
    else if (IsKeyPressed(KEY_UP)) {
        relativePosZ -= 1;
    }
    Player::limitMove();
}

void Player::limitMove() {
    int* mapLengthArr = Converter::getMapLength();
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
    const Vector3& playerPos = Converter::translateToAbsolute(relativePosX, relativePosZ);
    DrawCube(playerPos, playerSize, playerSize, playerSize, RED);
    DrawCubeWires(playerPos, playerSize, playerSize, playerSize, MAROON);
}

int* Player::getRelativePlayerPos() {
    int* playerPosArr = new int[2];
    playerPosArr[0] = relativePosX;
    playerPosArr[1] = relativePosZ;
    return playerPosArr;
}