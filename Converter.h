//
// Created by Admin on 2022-05-26.
//

#ifndef MINORULTRA_CONVERTER_H
#define MINORULTRA_CONVERTER_H

#include "raylib.h"

class Converter {
public:
    Converter(int, int);

    Vector3 translateToAbsolute(int, int);

private:
    int mapXLength;
    int mapZLength;
};


#endif //MINORULTRA_CONVERTER_H
