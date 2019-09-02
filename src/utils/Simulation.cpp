//
// Created by Kuba Jazdzyk on 8/29/19.
//

#include "Simulation.h"


Simulation::Simulation(Maze *maze, const Simulation::RobotAlgorithms &robotAlgorithms,
                       const Simulation::RobotDelegates &robotDelegates) : maze(maze), algorithms(robotAlgorithms) {
    Log::print("Simulation::Simulation(*maze, &robotAlgorithms, &robotDelegates)");
    this->robot1 = buildRobot(0, robotAlgorithms.first,
                              Coordinate(getMazeLength(), 0), robotDelegates.first);

    if (robotAlgorithms.second) {
        auto algorithm = *robotAlgorithms.second;
        this->robot2.emplace(buildRobot(1, algorithm,
                                        Coordinate(0, getMazeLength()), robotDelegates.second));
    }

    this->timer1 = new QTimer;
    this->timer2 = new QTimer;
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
    QObject::connect(this->timer1, &QTimer::timeout, [this] {
        this->simulate(this->robot1, this->timer1);
    });
    this->timer1->start(50);
}

void Simulation::pause() const {
    Log::print("Simulation::pause()");
    if (this->timer1->isActive()) {
        this->timer1->stop();
    }
    if (this->timer2->isActive()) {
        this->timer2->stop();
    }
}

void Simulation::reset() {
    Log::print("Simulation::reset()");
    this->timer1->stop();
    this->timer2->stop();

    this->robot1 = resetRobot(this->robot1);
    if (this->robot2) {
        this->robot2.emplace(resetRobot(*this->robot2));
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

void Simulation::simulate(Robot<15, 100, 12, 20> *robot, QTimer *timer) const {
    Log::print("Simulation::simulate(*robot, *timer)");
    robot->move();

    if (robot->getCurrentPosition() == getMazeEndCoordinate()) {
        timer->stop();
    }
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

Robot<15, 100, 12, 20> *Simulation::resetRobot(Robot<15, 100, 12, 20> *robot) {
    Log::print("Simulation::resetRobot(*robot)");
    robot->goToStart();

    auto id = robot->getId();
    auto newRobot = buildRobot(id, id == 0 ? this->algorithms.first : *this->algorithms.second,
                               id == 0 ? Coordinate(getMazeLength(), 0) : Coordinate(0, getMazeLength()),
                               robot->getDelegate());
    utils::destruct(robot);

    return newRobot;
}

int Simulation::getMazeLength() const {
    Log::print("Simulation::getMazeLength()");
    return static_cast<int>(sqrt(static_cast<int>(this->maze->getSize())) - 1);
}

Coordinate Simulation::getMazeEndCoordinate() const {
    Log::print("Simulation::getMazeEndCoordinate()");
    auto mazeLength = getMazeLength();
    return Coordinate(static_cast<int>(mazeLength / 2) + 1, static_cast<int>(mazeLength / 2) + 1);
}

void Simulation::delay(double seconds) {

}
