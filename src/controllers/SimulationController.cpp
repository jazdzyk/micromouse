//
// Created by Kuba Jazdzyk on 8/17/19.
//

#include "SimulationController.h"

using namespace Localizable;

SimulationController::SimulationController(SimulationSettings &simulationSettings,
                                           std::optional<ReturnToPreviousControllerDelegate *> returnDelegate,
                                           QWidget *parent)
        : BaseController(simulationSettings, parent), returnDelegate(std::move(returnDelegate)),
          simulation(new Simulation()) {
    Log::print("SimulationController::SimulationController(&simulationSettings, returnDelegate?, *parent)");
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
    addToParentLayout(preapreButtonsLayout(), 1);

    this->mazeView = new MazeView(*this->simulationSettings.maze);
    this->mazeView->setEnabled(false);
    this->mazeView->showMazeEntry();
    this->mazeView->showMazeExit();
    this->mazeView->setDelegate(this);

    addToParentLayout(this->mazeView, 6);
    addToParentLayout(prepareSimulationStateLayout(), 2);
}

QVBoxLayout *SimulationController::preapreButtonsLayout() {
    Log::print("SimulationController::preapreButtonsLayout()");
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

    this->rightSimulationStateView = new SimulationStateView;
    this->rightSimulationStateView->setName(this->locale[PL::RESULT_ROBOT2_LABEL]);

    auto layout = new QVBoxLayout;
    layout->addWidget(this->leftSimulationStateView);
    layout->addWidget(this->rightSimulationStateView);
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
}

void SimulationController::onReturnButtonClicked() {
    Log::print("SimulationController::onReturnButtonClicked()");
    if (this->returnDelegate) {
        auto delegate = *this->returnDelegate;
        delegate->controllerWillReturn(this);
    }
}

void SimulationController::robotDidMove(int robotId, Direction direction) {
    Log::print("SimulationController::robotDidMove(robotId: " + std::to_string(robotId) + ", direction)");
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
