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

/**
 * The SimulationController class inherits from BaseController
 * and implements MazeViewDelegate, RobotDelegate and SimulationDelegate protocols.
 * It is a controller class for a window related to simulation activities.
 *
 * It enables:
 *  - starting a simulation,
 *  - pausing a simulation,
 *  - resetting a simulation,
 *  - watching live results of the simulation on display panels.
 */
class SimulationController : public BaseController,
                             public MazeViewDelegate, public RobotDelegate, public SimulationDelegate {
    Q_OBJECT

public:
    using RobotsDistance = std::pair<int, int>;
    using SimulationTimes = std::pair<double, double>;

    /**
     * SimulationController class constructor.
     *
     * @param simulationSettings a set of settings used to perform Micromouse simulation
     * @param returnDelegate an optional delegate due to the purpose of returning to the previous controller
     * @param parent a parent class to the SimulationController
     */
    explicit SimulationController(SimulationSettings &simulationSettings,
                                  std::optional<ReturnToPreviousControllerDelegate *> returnDelegate,
                                  QWidget *parent = nullptr);

    /**
     * SimulationController class destructor.
     */
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

    /**
     * A private method which enables a configuration of controller's UI.
     */
    void setUpUi();

    /**
     * A private method which prepares layout with buttons for displaying in a UI.
     *
     * @return a layout with buttons
     */
    QVBoxLayout *prepareButtonsLayout();

    /**
     * A private method which prepares layout with simulation results' display panels for displaying in a UI.
     *
     * @return a layout with buttons
     */
    QVBoxLayout *prepareSimulationStateLayout();

    /**
     * A private method which is a callback for StartSimulationButton.
     */
    void onStartSimulationButtonClicked();

    /**
     * A private method which is a callback for PauseSimulationButton.
     */
    void onPauseSimulationButtonClicked();

    /**
     * A private method which is a callback for ResetSimulationButton.
     */
    void onResetSimulationButtonClicked();

    /**
     * A private method which is a callback for ReturnButton.
     */
    void onReturnButtonClicked();

    /**
     * A private method which activates a given arrow in an appropriate simulation results' display panel.
     *
     * @param robotId an id of a Micromouse robot related to the appropriate display panel
     * @param direction a direction of the arrow to be activated
     */
    void activateArrowForRobot(int robotId, Direction direction) const;

    /**
     * A private method which deactivates all arrows in an appropriate simulation results' display panel.
     *
     * @param robotId an id of a Micromouse robot related to the appropriate display panel
     */
    void deactivateAllArrowsForRobot(int robotId) const;

    /**
     * A private method which updates an appropriate simulation results' display panel with a new distance value.
     *
     * @param robotId an id of a Micromouse robot related to the appropriate display panel
     * @param distance a new distance value
     */
    void updateDistanceValueForRobot(int robotId, int distance) const;

    /**
     * A private method which updates an appropriate simulation results' display panel with a new time value.
     *
     * @param robotId an id of a Micromouse robot related to the appropriate display panel
     * @param time a new time value
     */
    void updateTimeValueForRobot(int robotId, double time) const;

    /**
     * A private method which updates an appropriate simulation results' display panel with a new speed value.
     *
     * @param robotId an id of a Micromouse robot related to the appropriate display panel
     */
    void updateSpeedValueForRobot(int robotId) const;

    /**
     * A private method to update an appropriate private distance field.
     *
     * @param robotId an id of a Micromouse robot related to the appropriate distance field
     */
    void updateRobotsDistance(int robotId);

    /**
     * A private getter of an appropriate distance field.
     *
     * @param robotId an id of a Micromouse robot related to the appropriate distance field
     * @return an appropriate distance field
     */
    [[nodiscard]] int getDistanceForRobot(int robotId) const;

    /**
     * A private method to update an appropriate private time field.
     *
     * @param robotId an id of a Micromouse robot related to the appropriate time field
     * @param msecs a new time value
     */
    void updateSimulationTime(int robotId, int msecs);

    /**
     * A private getter of an appropriate time field.
     *
     * @param robotId an id of a Micromouse robot related to the appropriate time field
     * @return an appropriate time field
     */
    [[nodiscard]] double getSimulationTimeForRobot(int robotId) const;

    // MazeViewDelegate methods
    /**
     * A private method which delegates work when a robot did move.
     *
     * @param robotId an id of a robot
     * @param direction a direction which robot moved to
     */
    void robotDidMove(int robotId, Direction direction) override;

    /**
     * A private method which delegates work when a delay did happen.
     *
     * @param robotId an id of a robot
     * @param msecs elapsed time
     */
    void delayDidHappen(int robotId, int msecs) override;

    // RobotDelegate methods
    /**
     * A private method which delegates work when a robot should go in a specific direction.
     *
     * @param robotId an id of a robot
     * @param movement a direction which a robot should move to
     */
    void robotShouldGoTo(int robotId, RobotMovement movement) override;

    /**
     * A private method which delegates work when a robot should go to a start position.
     *
     * @param robotId an id of a robot
     */
    void robotShouldGoToStart(int robotId) override;

    /**
     * A private method which delegates work when a robot did finish a maze.
     *
     * @param robotId an id of a robot
     */
    void robotDidFinish(int robotId) override;

    // SimulationDelegate methods
    /**
     * A private method which delegates work when a simulation's iteration did happen.
     *
     * @param robotId an id of a robot
     * @param msecs elapsed time
     */
    void simulationIterationDidHappen(int robotId, int msecs) override;

    /**
     * A private method which delegates work when a simulation was reset.
     */
    void simulationDidReset() override;
};


#endif //MICROMOUSE_SIMULATIONCONTROLLER_H
