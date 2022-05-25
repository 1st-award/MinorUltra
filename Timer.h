//
// Created by Admin on 2022-05-25.
//

#ifndef MINORULTRA_TIMER_H
#define MINORULTRA_TIMER_H


class Timer {
public:
    void StartTimer(float);
    void UpdateTimer();
    float GetTimer();
    bool TimeDone();

private:
    float Lifetime;
};


#endif //MINORULTRA_TIMER_H

