//
// Created by Kuba Jazdzyk on 8/29/19.
//

#include "Simulation.h"


Simulation::Simulation(Maze *maze, const Simulation::RobotAlgorithms &robotAlgorithms,
                       const Simulation::RobotDelegates &robotDelegates) : maze(maze) {
    Log::print("Simulation::Simulation(*maze, &robotAlgorithms, &robotDelegates)");
    this->robot1 = buildRobot(0, robotAlgorithms.first,
                              Coordinate(0, getMazeLength()), robotDelegates.first);

    if (robotAlgorithms.second) {
        auto algorithm = *robotAlgorithms.second;
        this->robot2.emplace(buildRobot(1, algorithm,
                                        Coordinate(getMazeLength(), 0), robotDelegates.second));
    }

    this->timer1 = new Timer;
    this->timer2 = new Timer;
}

Simulation::~Simulation() {
    Log::print("Simulation::~Simulation()");
    utils::destruct(robot1);
    if (robot2) {
        utils::destruct(*robot2);
    }
    utils::destruct(timer1);
    utils::destruct(timer2);
}

void Simulation::start() const {
    Log::print("Simulation::start()");
    this->timer1->setInterval([=]() {
        this->robot1->move();

        if (this->robot1->getCurrentPosition() == getMazeEndCoordinate()) {
            this->timer1->stop();
        }
    }, 50);

    if (this->robot2) {
        this->timer2->setInterval([=]() {
            auto robot2 = *this->robot2;
            robot2->move();

            if (robot2->getCurrentPosition() == getMazeEndCoordinate()) {
                this->timer2->stop();
            }
        }, 50);
    }
}

void Simulation::pause() const {
    Log::print("Simulation::pause()");
    this->timer1->pause();
    this->timer2->pause();
}

void Simulation::reset() const {
    Log::print("Simulation::reset()");
    this->timer1->stop();
    this->timer2->stop();

    this->robot1->goToStart();
    if (this->robot2) {
        auto robot2 = *this->robot2;
        robot2->goToStart();
    }
}

void Simulation::updateRobotSurrounding(int robotId, const RobotSurrounding &surrounding) const {
    Log::print("Simulation::updateRobotSurrounding(robotId: " + std::to_string(robotId) + ", &surrounding)");
    auto robot = robotId == 0 ? this->robot1 : *this->robot2;
    robot->updateSurrounding(
            surrounding.at(WallSide::LEFT),
            surrounding.at(WallSide::RIGHT),
            surrounding.at(WallSide::TOP)
    );
}

void Simulation::updateRobotCurrentPosition(int robotId, const Coordinate &coordinate) const {
    Log::print("Simulation::updateRobotCurrentPosition(robotId: " + std::to_string(robotId) + "&coordinate)");
    auto robot = robotId == 0 ? this->robot1 : *this->robot2;
    robot->updateCurrentPosition(coordinate);
}

Robot<15, 100, 12, 20> *Simulation::buildRobot(int id, RobotAlgorithm algorithm, const Coordinate &coordinate,
                                               std::optional<RobotDelegate *> delegate) const {
    Log::print("Simulation::buildRobot(id, algorithm, &coordinate, delegate?)");
    auto robot = new Robot<15, 100, 12, 20>(id, algorithm, coordinate, std::move(delegate));

    auto robotField = maze->getFieldAt(coordinate);
    robot->updateSurrounding(
            robotField->getWallAt(WallSide::LEFT),
            robotField->getWallAt(WallSide::RIGHT),
            robotField->getWallAt(WallSide::TOP)
    );

    return robot;
}

int Simulation::getMazeLength() const {
    Log::print("Simulation::getMazeLength()");
    return static_cast<int>(sqrt(static_cast<int>(this->maze->getSize())) - 1);
}

Coordinate Simulation::getMazeEndCoordinate() const {
    Log::print("Simulation::getMazeEndCoordinate()");
    auto mazeLength = getMazeLength();
    return Coordinate(static_cast<int>(mazeLength / 2), static_cast<int>(mazeLength / 2));
}

void Simulation::delay(double seconds) {

}
