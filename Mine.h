//
//	Create by Admin on 2022-05-26.
//

#ifndef MINORULTRA_MINE_H
#define MINORULTRA_MINE_H
#include "raylib.h"
#include <random>
#include <ctime>

class Mine
{
public:
	Mine(int, int, int);
	void landMine();
	void drawMine();
	bool checkMinePos(int, int);

private:
	int mineNum;
	int mapBlockX;
	int mapBlockZ;
	Vector3 minePos[200];
	bool check[10][10];
};

#endif