//
// Created by Kuba Jazdzyk on 8/17/19.
//

#include "SimulationController.h"

using namespace Localizable;

SimulationController::SimulationController(SimulationSettings &simulationSettings,
                                           std::optional<ReturnToPreviousControllerDelegate *> returnDelegate,
                                           QWidget *parent)
        : BaseController(simulationSettings, parent), returnDelegate(std::move(returnDelegate)) {
    Log::print("SimulationController::SimulationController(&simulationSettings, returnDelegate?, *parent)");
    this->simulation = new Simulation(*simulationSettings.maze, simulationSettings.robotAlgorithms,
                                      Simulation::RobotDelegates(std::make_optional(this), std::make_optional(this)),
                                      this);
    setUpUi();
}

SimulationController::~SimulationController() {
    Log::print("SimulationController::~SimulationController()");
    utils::destruct(this->startSimulationButton);
    utils::destruct(this->pauseSimulationButton);
    utils::destruct(this->resetSimulationButton);
    utils::destruct(this->leftSimulationStateView);
    utils::destruct(this->mazeView);
}

void SimulationController::setUpUi() {
    Log::print("SimulationController::setUpUi()");
    addToParentLayout(prepareButtonsLayout(), 1);

    this->mazeView = new MazeView(*this->simulationSettings.maze);
    this->mazeView->setEnabled(false);
    this->mazeView->showMazeEntry();
    this->mazeView->showMazeExit();
    this->mazeView->setDelegate(this);

    addToParentLayout(this->mazeView, 6);
    addToParentLayout(prepareSimulationStateLayout(), 2);
}

QVBoxLayout *SimulationController::prepareButtonsLayout() {
    Log::print("SimulationController::prepareButtonsLayout()");
    this->startSimulationButton = new RoundedPushButton(
            this->locale[PL::START_SIMULATION_BUTTON_SIMULATION_CONTROLLER_TITLE], 15);
    this->startSimulationButton->setAction([this]() {
        this->onStartSimulationButtonClicked();
    });

    this->pauseSimulationButton = new RoundedPushButton(
            this->locale[PL::PAUSE_SIMULATION_BUTTON_TITLE], 15);
    this->pauseSimulationButton->setAction([this]() {
        this->onPauseSimulationButtonClicked();
    });

    this->resetSimulationButton = new RoundedPushButton(
            this->locale[PL::RESET_SIMULATION_BUTTON_TITLE], 15);
    this->resetSimulationButton->setAction([this]() {
        this->onResetSimulationButtonClicked();
    });

    auto quitButtonLayout = new QHBoxLayout;
    quitButtonLayout->addWidget(this->quitButton);
    quitButtonLayout->addWidget(this->returnButton);
    connect(this->returnButton, &QPushButton::clicked, [=]() {
        this->onReturnButtonClicked();
    });
    quitButtonLayout->addStretch(1);

    auto buttonsLayout = new QVBoxLayout;
    addWidgetsToLayout({this->startSimulationButton, this->pauseSimulationButton, this->resetSimulationButton},
                       buttonsLayout);
    buttonsLayout->addStretch(1);
    buttonsLayout->addLayout(quitButtonLayout);

    return buttonsLayout;
}

QVBoxLayout *SimulationController::prepareSimulationStateLayout() {
    Log::print("SimulationController::prepareSimulationStateLayout()");
    this->leftSimulationStateView = new SimulationStateView;
    this->leftSimulationStateView->setName(this->locale[PL::RESULT_ROBOT1_LABEL]);

    auto layout = new QVBoxLayout;
    layout->addWidget(this->leftSimulationStateView);

    if (this->simulationSettings.simulationMode == SimulationMode::TWO_ROBOTS) {
        this->rightSimulationStateView = new SimulationStateView;
        this->rightSimulationStateView->setName(this->locale[PL::RESULT_ROBOT2_LABEL]);
        layout->addWidget(this->rightSimulationStateView);
    }

    layout->addStretch(1);

    return layout;
}

void SimulationController::onStartSimulationButtonClicked() {
    Log::print("SimulationController::onStartSimulationButtonClicked()");
    this->simulation->start();
}

void SimulationController::onPauseSimulationButtonClicked() {
    Log::print("SimulationController::onPauseSimulationButtonClicked()");
    this->simulation->pause();
}

void SimulationController::onResetSimulationButtonClicked() {
    Log::print("SimulationController::onResetSimulationButtonClicked()");
    this->simulation->reset();
    this->mazeView->resetFieldsColor();
}

void SimulationController::onReturnButtonClicked() {
    Log::print("SimulationController::onReturnButtonClicked()");
    this->simulation->reset();
    if (this->returnDelegate) {
        auto delegate = *this->returnDelegate;
        delegate->controllerWillReturn(this);
    }
}

void SimulationController::activateArrowForRobot(int robotId, Direction direction) const {
    Log::print("SimulationController::activateArrowForRobot(robotId: " + std::to_string(robotId) + ", direction)");
    switch (robotId) {
        case 0:
            this->leftSimulationStateView->activateArrow(direction);
            break;
        case 1:
            this->rightSimulationStateView->activateArrow(direction);
            break;
        default:
            break;
    }
}

void SimulationController::deactivateAllArrowsForRobot(int robotId) const {
    Log::print("SimulationController::deactivateAllArrowsForRobot(robotId: " + std::to_string(robotId) + ")");
    switch (robotId) {
        case 0:
            this->leftSimulationStateView->deactivateAllArrows();
            break;
        case 1:
            this->rightSimulationStateView->deactivateAllArrows();
            break;
        default:
            break;
    }
}

void SimulationController::updateDistanceValueForRobot(int robotId, int distance) const {
    Log::print("SimulationController::updateDistanceValueForRobot(robotId: " + std::to_string(robotId) +
               ", distance: " + std::to_string(distance) + ")");
    switch (robotId) {
        case 0:
            this->leftSimulationStateView->setDistanceValue(distance);
            break;
        case 1:
            this->rightSimulationStateView->setDistanceValue(distance);
            break;
        default:
            break;
    }
}

void SimulationController::updateTimeValueForRobot(int robotId, double time) const {
    Log::print("SimulationController::updateTimeValueForRobot(robotId: " + std::to_string(robotId) +
               ", time: " + std::to_string(time) + ")");
    switch (robotId) {
        case 0:
            this->leftSimulationStateView->setTimeValue(time);
            break;
        case 1:
            this->rightSimulationStateView->setTimeValue(time);
            break;
        default:
            break;
    }
}

void SimulationController::updateSpeedValueForRobot(int robotId) const {
    Log::print("SimulationController::updateSpeedValueForRobot(robotId: " + std::to_string(robotId) + ")");
    switch (robotId) {
        case 0:
            this->leftSimulationStateView->setSpeedValue(
                    getDistanceForRobot(robotId) / getSimulationTimeForRobot(robotId));
            break;
        case 1:
            this->rightSimulationStateView->setSpeedValue(
                    getDistanceForRobot(robotId) / getSimulationTimeForRobot(robotId));
            break;
        default:
            break;
    }
}

void SimulationController::updateRobotsDistance(int robotId) {
    Log::print("SimulationController::updateRobotsDistance(robotId: " + std::to_string(robotId) + ")");
    switch (robotId) {
        case 0:
            this->robotsDistance.first++;
            break;
        case 1:
            this->robotsDistance.second++;
            break;
        default:
            break;
    }
}

int SimulationController::getDistanceForRobot(int robotId) const {
    Log::print("SimulationController::getDistanceForRobot(robotId: " + std::to_string(robotId) + ")");
    switch (robotId) {
        case 0:
            return this->robotsDistance.first;
        case 1:
            return this->robotsDistance.second;
        default:
            return 0;
    }
}

void SimulationController::updateSimulationTime(int robotId, int msecs) {
    Log::print("SimulationController::updateSimulationTime(robotId: " + std::to_string(robotId) +
               ", msecs: " + std::to_string(msecs) + ")");
    switch (robotId) {
        case 0:
            this->simulationTimes.first += (static_cast<double>(msecs) / 1000);
            break;
        case 1:
            this->simulationTimes.second += (static_cast<double>(msecs) / 1000);
            break;
        default:
            break;
    }
}

double SimulationController::getSimulationTimeForRobot(int robotId) const {
    Log::print("SimulationController::getSimulationTimeForRobot(robotId: " + std::to_string(robotId) + ")");
    switch (robotId) {
        case 0:
            return this->simulationTimes.first;
        case 1:
            return this->simulationTimes.second;
        default:
            return 0.;
    }
}

void SimulationController::robotDidMove(int robotId, Direction direction) {
    Log::print("SimulationController::robotDidMove(robotId: " + std::to_string(robotId) + ", direction)");
    activateArrowForRobot(robotId, direction);
}

void SimulationController::delayDidHappen(int robotId, int msecs) {
    Log::print("SimulationController::delayDidHappen(robotId: " + std::to_string(robotId) +
               ", msecs: " + std::to_string(msecs) + ")");
    updateSimulationTime(robotId, msecs);
    updateTimeValueForRobot(robotId, getSimulationTimeForRobot(robotId));
    updateSpeedValueForRobot(robotId);
}

void SimulationController::robotShouldGoTo(int robotId, RobotMovement movement) {
    Log::print("SimulationController::robotShouldGoTo(robotId: " + std::to_string(robotId) + ", movement)");
    this->simulation->updateRobotSurrounding(robotId, this->mazeView->moveRobotTo(robotId, movement));
    this->simulation->updateRobotCurrentPosition(robotId, this->mazeView->getCurrentRobotCoordinate(robotId));

    updateRobotsDistance(robotId);
    updateDistanceValueForRobot(robotId, getDistanceForRobot(robotId));
}

void SimulationController::robotShouldGoToStart(int robotId) {
    Log::print("SimulationController::robotShouldGoToStart(robotId: " + std::to_string(robotId) + ")");
    this->simulation->updateRobotSurrounding(robotId, this->mazeView->moveRobotToStart(robotId));
    this->simulation->updateRobotCurrentPosition(robotId, this->mazeView->getCurrentRobotCoordinate(robotId));

    this->robotsDistance = {0, 0};
    updateDistanceValueForRobot(robotId, getDistanceForRobot(robotId));
    deactivateAllArrowsForRobot(robotId);
}

void SimulationController::robotDidFinish(int robotId) {
    Log::print("SimulationController::robotDidFinish(robotId: " + std::to_string(robotId) + ")");
    deactivateAllArrowsForRobot(robotId);
}

void SimulationController::simulationIterationDidHappen(int robotId, int msecs) {
    Log::print("SimulationController::simulationIterationDidHappen(robotId: " + std::to_string(robotId) +
               ", msecs: " + std::to_string(msecs) + ")");
    updateSimulationTime(robotId, msecs);
    updateTimeValueForRobot(robotId, getSimulationTimeForRobot(robotId));
    updateSpeedValueForRobot(robotId);
}

void SimulationController::simulationDidReset() {
    Log::print("SimulationController::simulationDidReset()");
    this->leftSimulationStateView->setTimeValue(0);
    this->leftSimulationStateView->setSpeedValue(0);
    if (this->simulationSettings.simulationMode == ::TWO_ROBOTS) {
        this->rightSimulationStateView->setTimeValue(0);
        this->rightSimulationStateView->setSpeedValue(0);
    }
}
