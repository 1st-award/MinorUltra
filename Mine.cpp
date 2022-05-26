#include "Mine.h"

Mine::Mine(int num, int mx, int mz) {
	mineNum = num;
	mapBlockX = mx;
	mapBlockZ = mz;
	minePos.resize(mineNum, Vector3{ 0.0f, 0.0f, 0.0f });
	mineState.resize(mapBlockX, std::vector<bool>(mapBlockZ, true));
};

void Mine::setMineState(int posX,int posZ, bool state){
	mineState[posX][posZ] = state;
}

std::vector<std::vector<bool>> Mine::getMineState() {
	return mineState;
}

void Mine::landMine(int playerBlockX, int playerBlockZ) {
	int posX;
	int posZ;
	srand((unsigned int)time(NULL));
	for (int i = 0; i < mineNum; ) {
		posX = rand() % mapBlockX;
		posZ = rand() % mapBlockZ;
		if (checkMinePos(posX, posZ) == true && (posX != playerBlockX || posZ != playerBlockZ)) {
			mineState[posX][posZ] = false;
			minePos[i].x = 0.5f - mapBlockX / (float)2 + posX;
			minePos[i].y = 0.0f;
			minePos[i].z = 0.5f - mapBlockZ / (float)2 + posZ;
			i += 1;
		}
	}
};

bool Mine::checkMinePos(int posX, int posZ) {
	if (mineState[posX][posZ] == true) {
		return true;
	}
	else { return false; }
};

void Mine::drawMine() {
	for (int i = 0; i < mineNum; i++) {
		DrawCube(minePos[i], 0.7f, 0.7f, 0.7f, BLUE);
	}
};