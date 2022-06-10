//
// Created by Admin on 2022-05-25.
//

#include "Timer.h"

void Timer::StartTimer(float lifeTime) {
    /* 타이머 시작 설정 함수 */
    Lifetime = lifeTime;
}

void Timer::UpdateTimer() {
    /* 타이머 업데이트 함수 */
    if (Lifetime > 0) {
        Lifetime -= GetFrameTime();
    }
}

float Timer::GetTimer() {
    /* 타이머 값 리턴 함수 */
    return Lifetime;
}

bool Timer::TimeDone() {
    /* 타이머가 끝났는지 확인하는 함수 */
    return Lifetime <= 0;
}