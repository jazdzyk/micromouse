//
// Created by Kuba Jazdzyk on 8/31/19.
//

#ifndef MICROMOUSE_ROBOTDELEGATE_H
#define MICROMOUSE_ROBOTDELEGATE_H


#include "src/utils/Enums.h"

/**
 * RobotDelegate is a protocol delegating methods from Robot template class.
 */
class RobotDelegate {
public:
    /**
     * A method which delegates work when a robot should go in a specific direction.
     *
     * @param robotId an id of a robot
     * @param movement a direction which a robot should move to
     */
    virtual void robotShouldGoTo(int robotId, RobotMovement movement) = 0;

    /**
     * A method which delegates work when a robot should go to a start position.
     *
     * @param robotId an id of a robot
     */
    virtual void robotShouldGoToStart(int robotId) = 0;

    /**
     * A method which delegates work when a robot did finish a maze.
     *
     * @param robotId an id of a robot
     */
    virtual void robotDidFinish(int robotId) = 0;

    /**
     * RobotDelegate class destructor.
     */
    virtual ~RobotDelegate() = default;
};


#endif //MICROMOUSE_ROBOTDELEGATE_H
