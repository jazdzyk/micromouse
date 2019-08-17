//
// Created by Kuba Jazdzyk on 8/17/19.
//

#ifndef MICROMOUSE_MAZECONTROLLER_H
#define MICROMOUSE_MAZECONTROLLER_H


#include <src/utils/SimulationSettings.h>
#include <src/protocols/delegates/ReturnToPreviousControllerDelegate.h>
#include <optional>

class MazeController : public BaseController {
public:
    explicit MazeController(SimulationSettings& simulationSettings, std::optional<ReturnToPreviousControllerDelegate*> returnDelegate, QWidget *parent = nullptr) {};

};


#endif //MICROMOUSE_MAZECONTROLLER_H
