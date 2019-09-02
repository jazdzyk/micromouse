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

class SimulationController : public BaseController,
                             public MazeViewDelegate, public RobotDelegate, public SimulationDelegate {
    Q_OBJECT

public:
    using RobotsDistance = std::pair<int, int>;
    using SimulationTimes = std::pair<double, double>;
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

    RobotsDistance robotsDistance = {0, 0};
    SimulationTimes simulationTimes = {0., 0.};

    void setUpUi();
    QVBoxLayout* prepareButtonsLayout();
    QVBoxLayout* prepareSimulationStateLayout();

    void onStartSimulationButtonClicked();
    void onPauseSimulationButtonClicked();
    void onResetSimulationButtonClicked();
    void onReturnButtonClicked();

    void activateArrowForRobot(int robotId, Direction direction) const;
    void deactivateAllArrowsForRobot(int robotId) const;

    void updateDistanceValueForRobot(int robotId, int distance) const;
    void updateTimeValueForRobot(int robotId, double time) const;
    void updateSpeedValueForRobot(int robotId) const;

    void updateRobotsDistance(int robotId);
    [[nodiscard]] int getDistanceForRobot(int robotId) const;

    void updateSimulationTime(int robotId, int msecs);
    [[nodiscard]] double getSimulationTimeForRobot(int robotId) const;

    // MazeViewDelegate methods
    void robotDidMove(int robotId, Direction direction) override;
    void delayDidHappen(int robotId, int msecs) override;

    // RobotDelegate methods
    void robotShouldGoTo(int robotId, RobotMovement movement) override;
    void robotShouldGoToStart(int robotId) override;
    void robotDidFinish(int robotId) override;

    // SimulationDelegate methods
    void simulationIterationDidHappen(int robotId, int msecs) override;
    void simulationDidReset() override;
};


#endif //MICROMOUSE_SIMULATIONCONTROLLER_H
