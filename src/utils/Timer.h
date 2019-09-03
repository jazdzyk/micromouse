//
// Created by Kuba Jazdzyk on 8/15/19.
//

#ifndef MICROMOUSE_TIMER_H
#define MICROMOUSE_TIMER_H


#include <thread>
#include "Logging.h"

class Timer {
public:
    template<typename Function>
    void setTimeout(Function function, int delay) {
        Log::print("Timer::setTimeout(function, delay: " +  std::to_string(delay) + "");
        this->isInactive = false;

        std::thread thread([=]() {
            if (this->isInactive) {
                return;
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(delay));

            if (this->isInactive) {
                return;
            }
            function();
        });

        thread.detach();
    }

    template<typename Function>
    void setInterval(Function function, int interval) {
        Log::print("Timer::setInterval(function, interval: " +  std::to_string(interval) + ")");
        this->isInactive = false;

        std::thread thread([=]() {
            while (true) {
                if (this->isInactive) {
                    return;
                }
                std::this_thread::sleep_for(std::chrono::milliseconds(interval));

                if (this->isPaused) {
                    continue;
                }
                if (this->isInactive) {
                    return;
                }
                function();
            }
        });

        thread.detach();
    }

    void stop();
    void pause();

private:
    bool isInactive = false;
    bool isPaused = false;
};


#endif //MICROMOUSE_TIMER_H
