//
// Created by Kuba Jazdzyk on 8/15/19.
//

#ifndef MICROMOUSE_TIMER_H
#define MICROMOUSE_TIMER_H


#include <thread>

class Timer {
public:
    template<typename Function>
    void setTimeout(Function function, int delay) {
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
        this->isInactive = false;

        std::thread thread([=]() {
            while (true) {
                if (this->isInactive) {
                    return;
                }
                std::this_thread::sleep_for(std::chrono::milliseconds(interval));

                if (this->isInactive) {
                    return;
                }
                function();
            }
        });

        thread.detach();
    }

    void stop();

private:
    bool isInactive = false;
};


#endif //MICROMOUSE_TIMER_H
