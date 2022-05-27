#include "Mine.h"

Mine::Mine(int num, int mx, int mz) {
    mineNum = num;
    mapBlockX = mx;
    mapBlockZ = mz;
    mineAbsoluteValue.resize(mineNum, Vector3{ 0.0f, 0.0f, 0.0f });
    mineState.resize(mapBlockX, std::vector<bool>(mapBlockZ, true));
};

void Mine::setMineState(int posRelativeX, int posRelativeZ, bool state) {
    mineState[posRelativeX][posRelativeZ] = state;
}

std::vector<std::vector<bool>> Mine::getMineState() {
    return mineState;
}

void Mine::landMine(int playerBlockX, int playerBlockZ) {
    int posRelativeX;
    int posRelativeZ;
    srand((unsigned int)time(NULL));
    for (int i = 0; i < mineNum; ) {
        posRelativeX = rand() % mapBlockX;
        posRelativeZ = rand() % mapBlockZ;
        if (checkMinePos(posRelativeX, posRelativeZ) == true && (posRelativeX != playerBlockX || posRelativeZ != playerBlockZ)) {
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