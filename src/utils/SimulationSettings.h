//
// Created by Kuba Jazdzyk on 8/15/19.
//

#ifndef MICROMOUSE_SIMULATIONSETTINGS_H
#define MICROMOUSE_SIMULATIONSETTINGS_H

#include <optional>
#include <utility>
#include <src/utils/maze/Maze.h>
#include "Enums.h"

struct SimulationSettings {
    using RobotAlgorithms = std::pair<RobotAlgorithm, std::optional<RobotAlgorithm>>;

    SimulationMode simulationMode;
    MazeSize mazeSize;
    RobotAlgorithms robotAlgorithms;
    std::optional<Maze> maze;

    SimulationSettings() :
        simulationMode(::ONE_ROBOT),
        mazeSize(::_256_FIELDS),
        robotAlgorithms(::LEFT_WALL_FOLLOWER, std::nullopt),
        maze(std::nullopt) {}

    ~SimulationSettings() = default;
};

#endif //MICROMOUSE_SIMULATIONSETTINGS_H
