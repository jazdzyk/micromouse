//
// Created by Kuba Jazdzyk on 8/15/19.
//

#ifndef MICROMOUSE_ENUMS_H
#define MICROMOUSE_ENUMS_H

enum SimulationMode {
    ONE_ROBOT = 1,
    TWO_ROBOT = 2,
};

enum MazeSize {
    _256_FIELDS = 256,
    _576_FIELDS = 576,
    _1024_FIELDS = 1024,
};

enum RobotAlgorithm {
    LEFT_WALL_FOLLOWER,
    RIGHT_WALL_FOLLOWER,
    BRUTE_FORCE,
    WAVE_PROPAGATION,
};

enum class RobotMovement {
    FORWARD,
    BACK,
    LEFT,
    RIGHT,
};

enum class Direction {
    TOP,
    BOTTOM,
    LEFT,
    RIGHT,
};

enum MazeFieldType {
    ROBOT1_START,
    ROBOT2_START,
    END,
    PLAIN
};

#endif //MICROMOUSE_ENUMS_H
