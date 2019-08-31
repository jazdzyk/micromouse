//
// Created by Kuba Jazdzyk on 8/29/19.
//

#ifndef MICROMOUSE_SIMULATION_H
#define MICROMOUSE_SIMULATION_H


#include <src/maze/Maze.h>

class Simulation {
public:
    using RobotAlgorithms = std::pair<RobotAlgorithm, std::optional<RobotAlgorithm>>;

    Simulation(Maze *maze, RobotAlgorithms robotAlgorithms);
    ~Simulation();

    void start() const;
    void pause() const;
    void reset() const;

private:
    Robot *robot1;
    std::optional<Robot *> robot2;

    Maze *maze;

    static void delay(double seconds = 1.);
};


#endif //MICROMOUSE_SIMULATION_H
