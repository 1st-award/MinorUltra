#include "Mine.h"

Mine::Mine(int num, float x, float z) {
	mineNum = num;
	mapSizeX = x;
	mapSizeZ = z;
	for (int i = 0; i < 100; i++) {
		minePos[i] = Vector3{ 0.0f, 0.0f , 0.0f };
	}
};

void Mine::landMine() {
	float posX;
	float posZ;
	srand((unsigned int)time(NULL));
	for (int i = 0; i < mineNum; i++) {
		posX = -0.5f + mapSizeX / 2 - rand() % (int)mapSizeX;
		posZ = -0.5f + mapSizeZ / 2 - rand() % (int)mapSizeZ;
		minePos[i] = Vector3{posX , 0.0f, posZ};
	}
};

void Mine::drawMine() {
	for (int i = 0; i < mineNum; i++) {
		DrawCube(minePos[i], 0.7f, 0.7f, 0.7f, BLUE);
	}
};