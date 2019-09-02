//
// Created by Kuba Jazdzyk on 8/26/19.
//

#ifndef MICROMOUSE_MAZEVIEWDELEGATE_H
#define MICROMOUSE_MAZEVIEWDELEGATE_H


#include <src/utils/Enums.h>

class MazeViewDelegate {
public:
    virtual void robotDidMove(int robotId, Direction direction) = 0;
    virtual void delayDidHappen(int robotId, int msecs) = 0;
    virtual ~MazeViewDelegate() = default;
};


#endif //MICROMOUSE_MAZEVIEWDELEGATE_H
