//
// Created by Kuba Jazdzyk on 8/17/19.
//

#include <QtCore/QEventLoop>
#include "MazeView.h"

MazeView::MazeView(MazeSize mazeSize, SimulationMode simulationMode, std::optional<MazeViewDelegate *> delegate)
        : QGridLayout(), mazeSize(mazeSize), simulationMode(simulationMode), delegate(std::move(delegate)) {
    Log::print("MazeView::MazeView(mazeSize, simulationMode, delegate?)");
    createEmptyUi();
}

MazeView::MazeView(Maze *maze, bool withRobot, std::optional<MazeViewDelegate *> delegate)
        : QGridLayout(), delegate(std::move(delegate)) {
    Log::print("MazeView::MazeView(*maze, withRobot, delegate?)");
    //
    this->mazeSize = maze->getSize();
    this->simulationMode = maze->getSimulationMode();
    //
    createPredefinedUi(maze->getFields(), withRobot);
}

MazeView::~MazeView() {
    Log::print("MazeView::~MazeView()");
}

void MazeView::setEnabled(bool enabled) const {
    Log::print("MazeView::setEnabled(enabled)");
    iterateOverAllFields([enabled](auto field) {
        field->setEnabled(enabled);
    });
}

Maze *MazeView::getMaze() const {
    Log::print("MazeView::getMaze()");
    return this->maze;
}

MazeView::WallSurrounding MazeView::moveRobotTo(int robotId, RobotMovement movement) {
    Log::print("MazeView::moveRobotTo(robotId: " + std::to_string(robotId) + ", movement)");
    auto rotationAngle = 0;

    auto getMovementDirection = [this](RobotMovement movement) {
        auto currentRobotRotation = this->currentRobotField->getCurrentRobotRotationAngle() % 360;

        auto getMovement = [](RobotMovement desiredMovement, const std::vector<WallSide> &choices) {
            switch (desiredMovement) {
                case RobotMovement::FORWARD:
                    return choices[0];
                case RobotMovement::BACK:
                    return choices[1];
                case RobotMovement::LEFT:
                    return choices[2];
                case RobotMovement::RIGHT:
                    return choices[3];
            }
        };

        switch (currentRobotRotation) {
            case -270:
                return getMovement(movement, {WallSide::TOP, WallSide::BOTTOM, WallSide::RIGHT, WallSide::LEFT});
            case -180:
                return getMovement(movement, {WallSide::RIGHT, WallSide::LEFT, WallSide::BOTTOM, WallSide::TOP});
            case -90:
                return getMovement(movement, {WallSide::BOTTOM, WallSide::TOP, WallSide::LEFT, WallSide::RIGHT});
            case 0:
                return getMovement(movement, {WallSide::LEFT, WallSide::RIGHT, WallSide::TOP, WallSide::BOTTOM});
            case 90:
                return getMovement(movement, {WallSide::TOP, WallSide::BOTTOM, WallSide::RIGHT, WallSide::LEFT});
            case 180:
                return getMovement(movement, {WallSide::RIGHT, WallSide::LEFT, WallSide::BOTTOM, WallSide::TOP});
            case 270:
                return getMovement(movement, {WallSide::BOTTOM, WallSide::TOP, WallSide::LEFT, WallSide::RIGHT});
            default:
                return WallSide::TOP;
        }
    };

    // ???
    auto delay = [](double secs = 1) {
        auto dieTime = QTime::currentTime().addMSecs(secs * 1000);
        while (QTime::currentTime() < dieTime) {
            QApplication::processEvents(QEventLoop::AllEvents, 100);
        }
    };

    auto wallSide = getMovementDirection(movement);
    switch (movement) {
        case RobotMovement::LEFT:
            rotationAngle = -90;
            break;
        case RobotMovement::RIGHT:
            rotationAngle = 90;
            break;
        case RobotMovement::BACK:
            rotationAngle = 180;
            break;
        default:
            break;
    }

    auto updateUi = [this](int robotId, RobotMovement movement) {
        switch (movement) {
            case RobotMovement::BACK:
            case RobotMovement::RIGHT:
                if (this->delegate) {
                    auto delegate = *this->delegate;
                    delegate->robotDidMove(robotId, Direction::RIGHT);
                }
                break;
            case RobotMovement::LEFT:
                if (this->delegate) {
                    auto delegate = *this->delegate;
                    delegate->robotDidMove(robotId, Direction::LEFT);
                }
                break;
            default:
                break;
        }
    };

    this->currentRobotField->showRobot(true, rotationAngle);
    updateUi(0, movement);
    delay(0.2);
    if (this->delegate) {
        auto delegate = *this->delegate;
        delegate->robotDidMove(0, Direction::TOP);
    }
    auto newCoordinate = this->currentRobotField->getMazeField()
            ->getNeighbourAssociatedWithWallAt(wallSide)->getCoordinate();
    auto currentRotation = this->currentRobotField->getCurrentRobotRotationAngle();
    moveRobot(newCoordinate, currentRotation);

    return {
            {WallSide::LEFT,  this->currentRobotField->getMazeField()->getWallAt(
                    getMovementDirection(RobotMovement::LEFT))},
            {WallSide::RIGHT, this->currentRobotField->getMazeField()->getWallAt(
                    getMovementDirection(RobotMovement::RIGHT))},
            {WallSide::TOP,   this->currentRobotField->getMazeField()->getWallAt(
                    getMovementDirection(RobotMovement::FORWARD))}
    };
}

MazeView::WallSurrounding MazeView::moveRobotToStart(int robotId) {
    Log::print("MazeView::moveRobotToStart(robotId: " + std::to_string(robotId) + ")");
    auto isFirstRobot = robotId == 0;
    auto rotationAngle = isFirstRobot ? 0 : 180;
    auto mazeLength = getMazeLength();
    auto startCoordinate = isFirstRobot ? Coordinate(0, mazeLength) : Coordinate(mazeLength, 0);

    moveRobot(startCoordinate, rotationAngle);

    return {
            {WallSide::LEFT,  this->currentRobotField->getMazeField()->getWallAt(
                    isFirstRobot ? WallSide::LEFT : WallSide::RIGHT)},
            {WallSide::RIGHT, this->currentRobotField->getMazeField()->getWallAt(
                    isFirstRobot ? WallSide::RIGHT : WallSide::LEFT)},
            {WallSide::TOP,   this->currentRobotField->getMazeField()->getWallAt(
                    isFirstRobot ? WallSide::TOP : WallSide::BOTTOM)}
    };
}

Coordinate MazeView::getCurrentRobotCoordinate() const {
    Log::print("MazeView::getCurrentRobotCoordinate()");
    return this->currentRobotField->getCoordinate();
}

void MazeView::showMazeExit() const {
    Log::print("MazeView::showMazeExit()");
    auto mazeLength = getMazeLength() + 1;
    this->mazeBoard[mazeLength / 2][mazeLength / 2]->setFieldType(MazeFieldType::END);
}

void MazeView::showMazeEntry() const {
    Log::print("MazeView::showMazeEntry()");
    auto mazeLength = getMazeLength();
    this->mazeBoard[0][mazeLength]->setFieldType(MazeFieldType::ROBOT1_START);
    if (this->simulationMode == SimulationMode::TWO_ROBOTS) {
        this->mazeBoard[mazeLength][0]->setFieldType(MazeFieldType::ROBOT2_START);
    }
}

void MazeView::setDelegate(MazeViewDelegate *delegate) {
    Log::print("MazeView::setDelegate(*delegate)");
    this->delegate.emplace(delegate);
}

void MazeView::iterateOverAllFields(const IterateOverFieldsFunction &function) const {
    Log::print("MazeView::iterateOverAllFields(&function)");
    for (const auto &row : this->mazeBoard) {
        for (auto field : row) {
            function(field);
        }
    }
}

void MazeView::createEmptyUi() {
    Log::print("MazeView::createEmptyUi()");
    createBoard();
    showMazeExit();
    showMazeEntry();
    showRobots(false, false);
}

void MazeView::createPredefinedUi(const MazeView::MazeFields &mazeFields, bool withRobot) {
    Log::print("MazeView::createPredefinedUi(const MazeView::MazeFields &mazeFields, bool withRobot)");
    createBoard(mazeFields);
    showRobots(withRobot, withRobot);
}

void MazeView::createBoard(std::optional<const MazeFields *> mazeFields) {
    Log::print("MazeView::createBoard(mazeFields?)");
    auto mazeLength = getMazeLength() + 1;
    for (auto x = 0; x < mazeLength; ++x) {
        FieldsRow _temp;
        for (auto y = 0; y < mazeLength; ++y) {
            MazeFieldView *fieldView;
            if (mazeFields) {
                fieldView = new MazeFieldView((*mazeFields)->at(y)[x], this->mazeSize, this);
            } else {
                fieldView = new MazeFieldView(Coordinate(x, y), this->mazeSize, this);
            }
            addWidget(fieldView, y, x, 1, 1);
            _temp.push_back(fieldView);
        }
        this->mazeBoard.push_back(_temp);
    }
    setSpacing(0);
}

void MazeView::moveRobot(const Coordinate &coordinate, int rotation) {
    Log::print("MazeView::moveRobot(&coordinate, rotation: " + std::to_string(rotation) + ")");
    this->currentRobotField->showRobot(false);
    this->currentRobotField = this->mazeBoard[coordinate.vertical][coordinate.horizontal];
    this->currentRobotField->resetCurrentRobotRotationWith(rotation);
    this->currentRobotField->showRobot(true);
}

void MazeView::showRobots(bool withRobot1, bool withRobot2) {
    Log::print("MazeView::showRobots(withRobot1, withRobot2)");
    auto mazeLength = getMazeLength();
    currentRobotField = mazeBoard[0][mazeLength];
    currentRobotField->showRobot(withRobot1);

    if (simulationMode == TWO_ROBOTS) {
        mazeBoard[mazeLength][0]->showRobot(withRobot2, 180);
    }
}

int MazeView::getMazeLength() const {
    Log::print("MazeView::getMazeLength()");
    return static_cast<int>(sqrt(static_cast<int>(this->mazeSize))) - 1;
}

void MazeView::mazeFieldWallDidSet(const MazeFieldViewDelegate::MazeFieldViewInfo &info) {
    Log::print("MazeView::mazeFieldWallDidSet(&info)");
    for (const auto &_info : info) {
        switch (_info.wallSide) {
            case WallSide::LEFT:
                if (_info.coordinate.horizontal != 0) {
                    this->mazeBoard[_info.coordinate.horizontal - 1][_info.coordinate.vertical]->setBorder(
                            WallSide::RIGHT, _info.shouldBeSet);
                }
                break;
            case WallSide::RIGHT:
                if (_info.coordinate.horizontal != (this->mazeSize - 1)) {
                    this->mazeBoard[_info.coordinate.horizontal + 1][_info.coordinate.vertical]->setBorder(
                            WallSide::LEFT, _info.shouldBeSet);
                }
                break;
            case WallSide::TOP:
                if (_info.coordinate.vertical != 0) {
                    this->mazeBoard[_info.coordinate.horizontal][_info.coordinate.vertical - 1]->setBorder(
                            WallSide::BOTTOM, _info.shouldBeSet);
                }
                break;
            case WallSide::BOTTOM:
                if (_info.coordinate.vertical != this->mazeSize - 1) {
                    this->mazeBoard[_info.coordinate.horizontal][_info.coordinate.vertical + 1]->setBorder(
                            WallSide::TOP, _info.shouldBeSet);
                }
                break;
        }
    }
}
