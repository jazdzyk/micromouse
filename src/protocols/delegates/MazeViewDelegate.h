//
// Created by Kuba Jazdzyk on 8/26/19.
//

#ifndef MICROMOUSE_MAZEVIEWDELEGATE_H
#define MICROMOUSE_MAZEVIEWDELEGATE_H


#include <src/utils/Enums.h>

/**
 * MazeViewDelegate is a protocol delegating methods from MazeView class.
 */
class MazeViewDelegate {
public:
    /**
     * A method which delegates work when a robot did move.
     *
     * @param robotId an id of a robot
     * @param direction a direction which robot moved to
     */
    virtual void robotDidMove(int robotId, Direction direction) = 0;

    /**
     * A method which delegates work when a delay did happen.
     *
     * @param robotId an id of a robot
     * @param msecs elapsed time
     */
    virtual void delayDidHappen(int robotId, int msecs) = 0;

    /**
     * MazeViewDelegate class destructor.
     */
    virtual ~MazeViewDelegate() = default;
};


#endif //MICROMOUSE_MAZEVIEWDELEGATE_H
