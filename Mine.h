//
//	Create by Admin on 2022-05-27.
//

#ifndef MINORULTRA_MINE_H
#define MINORULTRA_MINE_H

#include "Converter.h"
#include "raylib.h"
#include <ctime>
#include <random>
#include <time.h>
#include <vector>

typedef struct mineStateStruct {
    std::vector<bool> mineNumState;
    std::vector<Vector3> mineAbsoluteValue;
} mineStateStruct;

class Mine {
public:
    Mine(int);

    void setMineState(int, int, bool);

    std::vector<std::vector<bool>> getMineState();

    void landMine(int, int);

    void drawMine();

    bool checkMinePos(int, int);

    int getMineNumber();

private:
    int mineNum;
    int *mapArray;
    std::vector<std::vector<int>> mineNumMapping;
    std::vector<std::vector<bool>> mineState;
};

#endif