#include "Mine.h"

Mine::Mine(int num) {
    mineNum = num;
    mapLengthArr = Converter::getMapLength();
    mineAbsoluteValue.resize(mineNum, Vector3{ 0.0f, 0.0f, 0.0f });
    mineState.resize(mapLengthArr[0], std::vector<bool>(mapLengthArr[1], true));
};

void Mine::setMineState(int posRelativeX, int posRelativeZ, bool state){
    mineState[posRelativeX][posRelativeZ] = state;
}

std::vector<std::vector<bool>> Mine::getMineState() {
    return mineState;
}

void Mine::landMine(Player* player) {
    int* relativePlayerPos = player->getRelativePlayerPos();
    int posRelativeX;
    int posRelativeZ;
    srand((unsigned int)time(NULL));
    for (int i = 0; i < mineNum; ) {
        posRelativeX = rand() % mapLengthArr[0];
        posRelativeZ = rand() % mapLengthArr[1];
        if (checkMinePos(posRelativeX, posRelativeZ) == true && (posRelativeX != relativePlayerPos[0] || posRelativeZ != relativePlayerPos[1])) {
            mineState[posRelativeX][posRelativeZ] = false;
            mineAbsoluteValue[i] = Converter::translateToAbsolute(posRelativeX, posRelativeZ);
            i += 1;
        }
    }
};

bool Mine::checkMinePos(int posRelativeX, int posRelativeZ) {
    if (mineState[posRelativeX][posRelativeZ] == true) {
        return true;
    }
    else { return false; }
};

void Mine::drawMine() {
    for (int i = 0; i < mineNum; i++) {
        DrawCube(mineAbsoluteValue[i], 0.7f, 0.7f, 0.7f, BLUE);
    }
};