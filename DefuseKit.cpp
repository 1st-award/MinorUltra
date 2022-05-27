//
// Created by Admin on 2022-05-27.
//

#include "DefuseKit.h"
#include "Mine.h"

DefuseKit::DefuseKit() {}

void DefuseKit::setDefuseKit(int defuseKit) {
    defuseKitNumber = defuseKit;
}

int DefuseKit::getDefuseKit() {
    return defuseKitNumber;
}

bool DefuseKit::defuseBomb(int relativePosX, int relativePosZ, Mine *mine) {
    defuseKitNumber -= 1;
    if (mine->checkMinePos(relativePosX, relativePosZ)) {
        mine->setMineState(relativePosX, relativePosZ, false);
        return true;
    }
    else return false;
}
