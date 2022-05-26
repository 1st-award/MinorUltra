//
// Created by Admin on 2022-05-26.
//

#include "Score.h"


Score::Score() {
    score = 0;
}

void Score::addScore(bool defusingSuccess) {
    if (defusingSuccess) {
        score += 100;
    }
}

int Score::getScore() {
    return score;
}