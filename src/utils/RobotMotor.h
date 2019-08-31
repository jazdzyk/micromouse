//
// Created by Kuba Jazdzyk on 8/31/19.
//

#ifndef MICROMOUSE_ROBOTMOTOR_H
#define MICROMOUSE_ROBOTMOTOR_H


#include "Logging.h"

template <int maxRpm>
class RobotMotor {
public:
    void run(double pwm) {
        Log::print("RobotMotor::run(pwm: " + std::to_string(pwm) + ")");
        this->pwm = pwm;
        // TODO: connect to real-world motor and run it from here
    }

    void stop() {
        Log::print("RobotMotor::stop()");
        this->pwm = 0.;
        // TODO: connect to real-world motor and stop it from here
    }

    [[nodiscard]] bool isRunning() const {
        Log::print("RobotMotor::isRunning()");
        return this->pwm == 0.;
    }

    [[nodiscard]] double getRpm() const {
        Log::print("RobotMotor::getRpm()");
        return this->pwm * maxRpm;
    }

private:
    double pwm;
};


#endif //MICROMOUSE_ROBOTMOTOR_H
