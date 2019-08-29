//
// Created by Kuba Jazdzyk on 8/17/19.
//

#pragma once

#ifndef MICROMOUSE_SIMULATIONCONTROLLER_H
#define MICROMOUSE_SIMULATIONCONTROLLER_H


#include <src/utils/SimulationSettings.h>
#include <src/protocols/delegates/ReturnToPreviousControllerDelegate.h>
#include <optional>
#include <src/elements/RoundedPushButton.h>
#include <src/views/MazeView.h>
#include <src/views/SimulationStateView.h>
#include <src/utils/Simulation.h>

class SimulationController : public BaseController, public MazeViewDelegate {
    Q_OBJECT

public:
    explicit SimulationController(SimulationSettings& simulationSettings,
            std::optional<ReturnToPreviousControllerDelegate*> returnDelegate, QWidget *parent = nullptr);
    ~SimulationController() override;

private:
    std::optional<ReturnToPreviousControllerDelegate*> returnDelegate;

    RoundedPushButton *startSimulationButton;
    RoundedPushButton *pauseSimulationButton;
    RoundedPushButton *resetSimulationButton;

    SimulationStateView *leftSimulationStateView;
    SimulationStateView *rightSimulationStateView;

    MazeView *mazeView;

    Simulation *simulation;

    void setUpUi();
    QVBoxLayout* preapreButtonsLayout();
    QVBoxLayout* prepareSimulationStateLayout();

    void onStartSimulationButtonClicked();
    void onPauseSimulationButtonClicked();
    void onResetSimulationButtonClicked();
    void onReturnButtonClicked();

    // MazeViewDelegate method
    void robotDidMove(int robotId, Direction direction) override;
};


#endif //MICROMOUSE_SIMULATIONCONTROLLER_H
