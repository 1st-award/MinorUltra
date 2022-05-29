#include "Mine.h"

mineStateStruct *mineStateArray = new mineStateStruct;

Mine::Mine(int num) {
    mineNum = num;
    mapArray = Converter::getMapLength();
    mineNumMapping.resize(mapArray[0], std::vector<int>(mapArray[1], -1));
    mineStateArray->mineAbsoluteValue.resize(mineNum, Vector3{0.0f, 0.0f, 0.0f});
    mineStateArray->mineNumState.resize(mineNum, false);
    mineState.resize(mapArray[0], std::vector<bool>(mapArray[1], false));
};

void Mine::setMineState(int posRelativeX, int posRelativeZ, bool state) {
    mineState[posRelativeX][posRelativeZ] = state;
    if (mineNumMapping[posRelativeX][posRelativeZ] != -1) {
        mineStateArray->mineNumState[mineNumMapping[posRelativeX][posRelativeZ]] = state;
    }
}

std::vector<std::vector<bool>> Mine::getMineState() {
    return mineState;
}

void Mine::landMine(int playerRelativeX, int playerRelativeZ) {
    int posRelativeX;
    int posRelativeZ;
    srand((unsigned int) time(NULL));
    for (int i = 0; i < mineNum;) {
        posRelativeX = rand() % mapArray[0];
        posRelativeZ = rand() % mapArray[1];
        if (checkMinePos(posRelativeX, posRelativeZ) == false &&
            (posRelativeX != playerRelativeX || posRelativeZ != playerRelativeZ)) {
            mineState[posRelativeX][posRelativeZ] = true;
            mineNumMapping[posRelativeX][posRelativeZ] = i;
            mineStateArray->mineNumState[i] = true;
            mineStateArray->mineAbsoluteValue[i] = Converter::translateToAbsolute(posRelativeX, posRelativeZ);
            i += 1;
        }
    }
};

bool Mine::checkMinePos(int posRelativeX, int posRelativeZ) {
    int maxPosX = mapArray[0] - 1;
    int maxPosZ = mapArray[1] - 1;

    if (posRelativeX < 0 || posRelativeX > maxPosX || posRelativeZ < 0 || posRelativeZ > maxPosZ) {
        return false;
    } else {
        return mineState[posRelativeX][posRelativeZ];
    }
};

void Mine::drawMine() {
    for (int i = 0; i < mineNum; i++) {
        if (mineStateArray->mineNumState[i] == true) {
            DrawCube(mineStateArray->mineAbsoluteValue[i], 0.7f, 0.7f, 0.7f, BLUE);
        }
    }
};