//
// Created by Admin on 2022-05-26.
//

#ifndef MINORULTRA_CONVERTER_H
#define MINORULTRA_CONVERTER_H

#include "raylib.h"


class Converter {
public:
    static Vector3 translateToAbsolute(int, int);

    static void setMapLength(int, int);

    static int* getMapLength();
};


#endif //MINORULTRA_CONVERTER_H
