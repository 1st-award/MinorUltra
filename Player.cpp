//
// Created by Admin on 2022-05-25.
//

#include "Player.h"
#include "Converter.h"
#include "Mine.h"

Player::Player(int playerPosX, int playerPosZ, int defuseKitNumber) {
    relativePosX = playerPosX;
    relativePosZ = playerPosZ;
    relativeFocusX = 0;
    relativeFocusZ = 0;
    playerSize = 0.7f;
    DefuseKit::setDefuseKit(defuseKitNumber);
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
            if (count[i] == true) {
                result += 1;
            }
        }
        return result;
    }
}
void Player::movePlayer() {
    if (IsKeyPressed(KEY_D)) {
        relativePosX += 1;
    } else if (IsKeyPressed(KEY_A)) {
        relativePosX -= 1;
    } else if (IsKeyPressed(KEY_S)) {
        relativePosZ += 1;
    } else if (IsKeyPressed(KEY_W)) {
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
    const Vector3 &playerPos = Converter::translateToAbsolute(relativePosX, relativePosZ);
    DrawCube(playerPos, playerSize, playerSize, playerSize, RED);
    DrawCubeWires(playerPos, playerSize, playerSize, playerSize, MAROON);
}

void Player::drawFocus() {
    if(relativeFocusX >= 0 && relativeFocusZ >= 0) {
        const Vector3 &focusPos = Converter::translateToAbsolute(relativeFocusX, relativeFocusZ);
        DrawCubeWires(focusPos, playerSize, playerSize, playerSize, GREEN);
    }
}

void Player::choiceFocus() {
    if (IsKeyPressed(KEY_RIGHT)) {
        relativeFocusX += 1;
    } else if (IsKeyPressed(KEY_LEFT)) {
        relativeFocusX -= 1;
    } else if (IsKeyPressed(KEY_DOWN)) {
        relativeFocusZ += 1;
    } else if (IsKeyPressed(KEY_UP)) {
        relativeFocusZ -= 1;
    }
    Player::limitFocus();
}

void Player::limitFocus() {
    int *mapLengthArr = Converter::getMapLength();
    int maxPosX = mapLengthArr[0] - 1;
    int maxPosZ = mapLengthArr[1] - 1;
    int distancePosX = relativeFocusX - relativePosX;
    int distancePosZ = relativeFocusZ - relativePosZ;

    if(distancePosX > 1 || relativeFocusX > maxPosX)
        relativeFocusX -= 1;
    else if(distancePosX < -1 || relativeFocusX < 0)
        relativeFocusX += 1;
    else if(distancePosZ > 1 || relativeFocusZ > maxPosZ)
        relativeFocusZ -= 1;
    else if(distancePosZ < -1 || relativeFocusZ < 0)
        relativeFocusZ += 1;
}

void Player::defuseBomb(Mine* mine) {
    bool result = DefuseKit::defuseBomb(relativeFocusX, relativeFocusZ, mine);
}

bool Player::isStepOnMine(Mine *mine) {
    return !(mine->checkMinePos(relativePosX, relativePosZ));
}

int *Player::getRelativePlayerPos() {
    int *playerPosArr = new int[2];
    playerPosArr[0] = relativePosX;
    playerPosArr[1] = relativePosZ;
    return playerPosArr;
}
