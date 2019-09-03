//
// Created by Kuba Jazdzyk on 8/15/19.
//

#include "Timer.h"

void Timer::stop() {
    Log::print("Timer::stop()");
    this->isInactive = true;
}

void Timer::pause() {
    Log::print("Timer::pause()");
    this->isPaused = true;
}
