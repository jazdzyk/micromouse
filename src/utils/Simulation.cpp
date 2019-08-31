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
}

Simulation::~Simulation() {
    Log::print("Simulation::~Simulation()");
    utils::destruct(robot1);
    if (robot2) {
        utils::destruct(*robot2);
    }
}

void Simulation::start() const {
    Log::print("Simulation::start()");

}

void Simulation::pause() const {
    Log::print("Simulation::pause()");

}

void Simulation::reset() const {
    Log::print("Simulation::reset()");

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
    Log::print("Simulation::getMazeLength(*maze)");
    return static_cast<int>(sqrt(static_cast<int>(this->maze->getSize())) - 1);
}

void Simulation::delay(double seconds) {

}
