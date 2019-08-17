//
// Created by Kuba Jazdzyk on 8/15/19.
//

#include <src/utils/Timer.h>
#include "StartController.h"

StartController::StartController(QWidget *parent) : BaseController(parent) {
    Log::print("StartController::StartController(*parent)");
    setUpUi();
    showFullScreen();
}

StartController::~StartController() {
    Log::print("StartController::~StartController()");
}

void StartController::setUpUi() {
    Log::print("StartController::setUpUi()");
    using namespace Localizable;
    this->startSimulationButton = new RoundedPushButton(
            this->locale[PL::START_SIMULATION_BUTTON_START_CONTROLLER_TITLE], 18);
    this->startSimulationButton->setAction([this]() {
        this->onStartSimulationButtonClicked();
    });

    this->simulationModeBox = new RadioButtonGroupBox(
            this->locale[PL::SIMULATION_MODE_BOX_TITLE],
            {this->locale[PL::ONE_ROBOT_RADIO_BUTTON_TITLE], this->locale[PL::TWO_ROBOTS_RADIO_BUTTON_TITLE]},
            [this](int id) {
                this->onSimulationModeChanged(id);
            });

    this->mazeSizeBox = new RadioButtonGroupBox(
            this->locale[PL::MAZE_SIZE_MODE_BOX_TITLE],
            {
                    this->locale[PL::MAZE_SIZE_256_RADIO_BUTTON_TITLE],
                    this->locale[PL::MAZE_SIZE_576_RADIO_BUTTON_TITLE],
                    this->locale[PL::MAZE_SIZE_1024_RADIO_BUTTON_TITLE]
            },
            [this](int id) {
                this->onMazeSizeChanged(id);
            });

    this->algorithmModeBox = new DropDownGroupBox(
            this->locale[PL::ALGORITHM_MODE_BOX_TITLE],
            {this->locale[PL::ALGORITHM_MODE_ROBOT1_LABEL], this->locale[PL::ALGORITHM_MODE_ROBOT2_LABEL]},
            {
                    this->locale[PL::LEFT_WALL_FOLLOWER_ALGORITHM_DROP_DOWN_TEXT],
                    this->locale[PL::RIGHT_WALL_FOLLOWER_ALGORITHM_DROP_DOWN_TEXT],
                    this->locale[PL::BRUTE_FORCE_ALGORITHM_DROP_DOWN_TEXT],
                    this->locale[PL::WAVE_PROPAGATION_ALGORITHM_DROP_DOWN_TEXT]
            },
            [this](int dropDownId, int optionId) {
                this->onAlgorithmModeChanged(dropDownId, optionId);
            });

    this->ownMazeBox = new CheckButtonGroupBox(
            this->locale[PL::OWN_MAZE_MODE_BOX_TITLE],
            {this->locale[PL::OWN_MAZE_BUTTON_TITLE]},
            [this](int id) {
                this->onCreateOwnMazeButtonClicked(id);
            });

    auto *objectsLayout = new QVBoxLayout;
    objectsLayout->addStretch(1);
    addWidgetsToLayout({
                               this->startSimulationButton,
                               this->simulationModeBox,
                               this->mazeSizeBox,
                               this->algorithmModeBox,
                               this->ownMazeBox
                       }, objectsLayout);
    objectsLayout->addStretch(1);

    auto *quitButtonLayout = new QHBoxLayout;
    quitButtonLayout->addWidget(this->quitButton);
    quitButtonLayout->addStretch(1);

    auto *leftLayout = new QVBoxLayout;
    leftLayout->addStretch(1);
    leftLayout->addLayout(quitButtonLayout);

    auto *outerObjectsLayout = new QHBoxLayout;
    outerObjectsLayout->addLayout(leftLayout, 3);
    outerObjectsLayout->addLayout(objectsLayout, 1);
    outerObjectsLayout->addStretch(3);

    addToParentLayout(outerObjectsLayout);
}

void StartController::onStartSimulationButtonClicked() {
    Log::print("StartController::onStartSimulationButtonClicked()");
    if (!this->ownMazeBox->isChosen(0)) {
        this->simulationSettings.maze.emplace(Maze(this->simulationSettings.mazeSize,
                                                 this->simulationSettings.simulationMode));
    }
    moveToNextController<SimulationController>();
}

void StartController::onSimulationModeChanged(int id) {
    Log::print("StartController::onSimulationModeChanged(id: " + std::to_string(id) + ")");
    this->algorithmModeBox->setDropDownVisible(1, id == 1);
    if (id == 0) {
        this->simulationSettings.robotAlgorithms.second.reset();
    } else {
        this->simulationSettings.robotAlgorithms.second.emplace(::LEFT_WALL_FOLLOWER);
    }

    this->simulationSettings.simulationMode = static_cast<SimulationMode>(id + 1);
}

void StartController::onMazeSizeChanged(int id) {
    Log::print("StartController::onMazeSizeChanged(id: " + std::to_string(id) + ")");
    switch (id) {
        case 1:
            this->simulationSettings.mazeSize = ::_576_FIELDS;
            break;
        case 2:
            this->simulationSettings.mazeSize = ::_1024_FIELDS;
            break;
        default:
            this->simulationSettings.mazeSize = ::_256_FIELDS;
    }
}

void StartController::onAlgorithmModeChanged(int dropDownId, int optionId) {
    Log::print("StartController::onAlgorithmModeChanged(dropDownId: " + std::to_string(dropDownId) + ", optionId: " +
               std::to_string(optionId) + ")");
    if (dropDownId == 0) {
        this->simulationSettings.robotAlgorithms.first = static_cast<RobotAlgorithm>(optionId);
    } else {
        this->simulationSettings.robotAlgorithms.second.emplace(static_cast<RobotAlgorithm>(optionId));
    }
}

void StartController::onCreateOwnMazeButtonClicked(int id) {
    Log::print("StartController::onCreateOwnMazeButtonClicked(id: " + std::to_string(id) + ")");
    moveToNextController<MazeController>();
}

void StartController::controllerWillReturn(BaseController *controller) {
    Log::print("StartController::controllerWillReturn(*controller)");
    controller->hide();
    showFullScreen();
}
