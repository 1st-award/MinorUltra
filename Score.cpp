//
// Created by Admin on 2022-05-26.
//

#include "Score.h"


Score::Score() {
    /* 점수 계산 클래스 */
    score = 0;
}

void Score::addScore(bool defusingSuccess) {
    /* 폭탄 해체 성공 시 점수 +100 추가 함수 */
    if (defusingSuccess) {
        score += 100;
    }
}

int Score::getScore() {
    /* 점수를 반환하는 함수 */
    return score;
}