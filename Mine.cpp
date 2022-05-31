#include "Mine.h"

mineStateStruct *mineStateArray = new mineStateStruct;

Mine::Mine(int num) {
    mineNum = num;
    mapArray = Converter::getMapLength();
    mineNumMapping.resize(mapArray[0], std::vector<int>(mapArray[1], -1));
    mineStateArray->mineNumState.resize(mineNum, false);
    mineStateArray->mineRelativeValue.resize(mineNum, Vector2{0.0f, 0.0f});
    mineStateArray->mineAbsoluteValue.resize(mineNum, Vector3{0.0f, 0.0f, 0.0f});
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
            mineStateArray->mineRelativeValue[i] = Vector2{(float)posRelativeX, (float)posRelativeZ};
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

void Mine::drawMine(Texture2D mine, int mapSize, float povy) {
    for (int i = 0; i < mineNum; i++) {
        if (mineStateArray->mineNumState[i] == true) {
            DrawTextureEx(mine, Vector2{440.0f / mapSize * mineStateArray->mineRelativeValue[i].x + 5,
                                        440.0f / mapSize * mineStateArray->mineRelativeValue[i].y + 55},
                          0, 60.0f/povy, RAYWHITE);
        }
    }
};

void Mine::drawDefusedArea() {
    for (int i = 0; i < mineNum; i++) {
        if (mineStateArray->mineNumState[i] == false) {
            DrawCube(mineStateArray->mineAbsoluteValue[i], 1.0f, 0, 1.0f, GREEN);
            DrawCubeWires(mineStateArray->mineAbsoluteValue[i], 1.0f, 0, 1.0f, GRAY);
        }
    }
};

int Mine::getMineNumber() {
    int mineCount = 0;
    for(int i = 0; i < mineNum; ++i) {
        if(mineStateArray->mineNumState[i] == true) {
            mineCount += 1;
        }
    }
    return mineCount;
}