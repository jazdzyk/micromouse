//
// Created by Kuba Jazdzyk on 8/17/19.
//

#ifndef MICROMOUSE_MAZECONTROLLERDELEGATE_H
#define MICROMOUSE_MAZECONTROLLERDELEGATE_H


#include <src/controllers/BaseController.h>

class MazeControllerDelegate {
public:
    virtual void mazeControllerDidAcceptMaze(BaseController *controller, SimulationSettings& simulationSettings) = 0;
    virtual ~MazeControllerDelegate() = default;
};


#endif //MICROMOUSE_MAZECONTROLLERDELEGATE_H
