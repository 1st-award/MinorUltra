//
// Created by Admin on 2022-05-26.
//

#include "Converter.h"
#include "raylib.h"

Converter::Converter(int mapXLength, int mapZLength) {
    this->mapXLength = mapXLength;
    this->mapZLength = mapZLength;
}

Vector3 Converter::translateToAbsolute(int relativePosX, int relativePosZ) {
    float absolutePosX = 0.5f - mapXLength / 2.0f + relativePosX;
    float absolutePosZ = 0.5f - mapZLength / 2.0f + relativePosZ;
    Vector3 absoluteVector{(float) relativePosX, 0.0f, (float) relativePosZ};
    return absoluteVector;
}