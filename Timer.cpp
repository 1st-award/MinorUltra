//
// Created by Admin on 2022-05-25.
//

#include "Timer.h"
#include "raylib.h"

void Timer::StartTimer(float lifeTime) {
    Lifetime = lifeTime;
}

void Timer::UpdateTimer() {
    if (Lifetime > 0) {
        Lifetime -= GetFrameTime();
    }
}

float Timer::GetTimer() {
    return Lifetime;
}

bool Timer::TimeDone() {
    return Lifetime <= 0;
}