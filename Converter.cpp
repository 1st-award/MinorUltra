//
// Created by Admin on 2022-05-26.
//

#include "Converter.h"

int mapXLength;
int mapZLength;

Vector3 Converter::translateToAbsolute(int relativePosX, int relativePosZ) {
    float absolutePosX = 0.5f - mapXLength / 2.0f + relativePosX;
    float absolutePosZ = 0.5f - mapZLength / 2.0f + relativePosZ;
    Vector3 absoluteVector{absolutePosX, 0.0f, absolutePosZ};
    return absoluteVector;
}

void Converter::setMapLength(int XLength, int ZLength) {
    mapXLength = XLength;
    mapZLength = ZLength;
}

int *Converter::getMapLength() {
    int *tempArr = new int[2];
    tempArr[0] = mapXLength;
    tempArr[1] = mapZLength;
    return tempArr;
}
