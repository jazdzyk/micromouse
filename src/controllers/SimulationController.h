//
// Created by Kuba Jazdzyk on 8/17/19.
//

#pragma once

#ifndef MICROMOUSE_SIMULATIONCONTROLLER_H
#define MICROMOUSE_SIMULATIONCONTROLLER_H


#include <src/utils/SimulationSettings.h>
#include <src/protocols/delegates/ReturnToPreviousControllerDelegate.h>
#include <optional>

class SimulationController : public BaseController {
public:
    explicit SimulationController(SimulationSettings& simulationSettings, std::optional<ReturnToPreviousControllerDelegate*> returnDelegate, QWidget *parent = nullptr) {};
};


#endif //MICROMOUSE_SIMULATIONCONTROLLER_H
