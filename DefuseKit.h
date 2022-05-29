//
// Created by Admin on 2022-05-27.
//

#ifndef MINORULTRA_DEFUSEKIT_H
#define MINORULTRA_DEFUSEKIT_H


#include "Mine.h"

class DefuseKit {
public:
    int getDefuseKit();

protected:
    DefuseKit();

    void setDefuseKit(int);

    bool defuseBomb(int, int, Mine *);

private:
    int defuseKitNumber;
};


#endif //MINORULTRA_DEFUSEKIT_H
