//
//	Create by Admin on 2022-05-26.
//

#ifndef MINORULTRA_MINE_H
#define MINORULTRA_MINE_H
#include "raylib.h"
#include <random>
#include <ctime>
#include <vector>

class Mine
{
public:
	Mine(int, int, int);
	void setMineState(int, int, bool);
	std::vector<std::vector<bool>> getMineState();
	void landMine(int, int);
	void drawMine();
	bool checkMinePos(int, int);

private:
	int mineNum;
	int mapBlockX;
	int mapBlockZ;
	std::vector<Vector3> minePos;
	std::vector<std::vector<bool>> mineState;
};

#endif