//
// Created by Kuba Jazdzyk on 8/29/19.
//

#ifndef MICROMOUSE_SIMULATION_H
#define MICROMOUSE_SIMULATION_H


#include <src/maze/Maze.h>
#include "Robot.h"
#include <utility>

class Simulation {
public:
    using WallSide = MazeWall::WallSide;
    using RobotAlgorithms = std::pair<RobotAlgorithm, std::optional<RobotAlgorithm>>;
    using RobotDelegates = std::pair<std::optional<RobotDelegate *>, std::optional<RobotDelegate *>>;

    Simulation(Maze *maze, const RobotAlgorithms& robotAlgorithms, const RobotDelegates& robotDelegates);
    ~Simulation();

    void start() const;
    void pause() const;
    void reset() const;

private:
    Robot<15, 100, 12, 20> *robot1;
    std::optional<Robot<15, 100, 12, 20> *> robot2;

    Maze *maze;

    Robot<15, 100, 12, 20> *buildRobot(int id, RobotAlgorithm algorithm, const Coordinate& coordinate,
                                       std::optional<RobotDelegate *> delegate) const;
    [[nodiscard]] int getMazeLength() const;

    static void delay(double seconds = 1.);
};


#endif //MICROMOUSE_SIMULATION_H
