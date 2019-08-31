//
// Created by Kuba Jazdzyk on 8/31/19.
//

#ifndef MICROMOUSE_ROBOTDELEGATE_H
#define MICROMOUSE_ROBOTDELEGATE_H


#include "src/utils/Enums.h"

class RobotDelegate {
public:
    virtual void robotShouldGoTo(int robotId, RobotMovement movement) = 0;
    virtual void robotShouldGoToStart(int robotId) = 0;

    virtual void robotDidFinish(int robotId) = 0;

    virtual ~RobotDelegate() = default;
};


#endif //MICROMOUSE_ROBOTDELEGATE_H
