//
// Created by Kuba Jazdzyk on 8/17/19.
//

#ifndef MICROMOUSE_MAZECONTROLLERDELEGATE_H
#define MICROMOUSE_MAZECONTROLLERDELEGATE_H


#include <src/controllers/BaseController.h>

/**
 * MazeControllerDelegate is a protocol delegating methods from MazeController class.
 */
class MazeControllerDelegate {
public:
    /**
     * A method which delegates work when MazeController did accept a maze.
     *
     * @param controller an instance of the MazeController
     * @param simulationSettings a set of settings used to perform Micromouse simulation
     */
    virtual void mazeControllerDidAcceptMaze(BaseController *controller, SimulationSettings &simulationSettings) = 0;

    /**
     * MazeControllerDelegate class destructor.
     */
    virtual ~MazeControllerDelegate() = default;
};


#endif //MICROMOUSE_MAZECONTROLLERDELEGATE_H
