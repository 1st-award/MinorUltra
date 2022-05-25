#include "Mine.h"

Mine::Mine(int num, int mx, int mz) {
	mineNum = num;
	mapBlockX = mx;
	mapBlockZ = mz;
	for (int i = 0; i < 100; i++) {
		minePos[i] = Vector3{ 0.0f, 0.0f , 0.0f };
	}
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			check[i][j] = true;
		}
	}
};

void Mine::landMine() {
	int posX;
	int posZ;
	srand((unsigned int)time(NULL));
	for (int i = 0; i < mineNum; ) {
		posX = rand() % mapBlockX;
		posZ = rand() % mapBlockZ;
		if (checkMinePos(posX, posZ) == true) {
			minePos[i] = Vector3{ 0.5f - mapBlockX / 2 + posX , 0.0f, 0.5f - mapBlockZ / 2 + posZ };
			i += 1;
		}
	}
};

bool Mine::checkMinePos(int posX,int posZ) {
	check[4][4] = false;
	if (check[posX][posZ] == true) {
		check[posX][posZ] = false;

		return true;
	}
	else { return false; }
};

void Mine::drawMine() {
	for (int i = 0; i < mineNum; i++) {
		DrawCube(minePos[i], 0.7f, 0.7f, 0.7f, BLUE);
	}
};