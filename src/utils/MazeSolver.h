//
// Created by Kuba Jazdzyk on 8/31/19.
//

#ifndef MICROMOUSE_MAZESOLVER_H
#define MICROMOUSE_MAZESOLVER_H


#include <map>
#include <src/maze/MazeWall.h>
#include <functional>
#include "Enums.h"

template<RobotAlgorithm algorithm, int distanceThreshold>
class MazeSolver {
public:
    using WallSide = MazeWall::WallSide;
    using DistanceMeasurement = std::map<WallSide, double>;

    MazeSolver() {
        switch (algorithm) {
            case RobotAlgorithm::LEFT_WALL_FOLLOWER:
                this->solverAlgorithm = leftWallFollower;
                break;
            case RobotAlgorithm::RIGHT_WALL_FOLLOWER:
                this->solverAlgorithm = rightWallFollower;
                break;
            case RobotAlgorithm::BRUTE_FORCE:
                this->solverAlgorithm = bruteForce;
                break;
            case RobotAlgorithm::WAVE_PROPAGATION:
                this->solverAlgorithm = wavePropagation;
                break;
        }
    }

    [[nodiscard]] RobotMovement solve(const DistanceMeasurement &measurement) const {
        return this->solverAlgorithm(measurement);
    }

private:
    std::function<RobotMovement(DistanceMeasurement &)> solverAlgorithm;

    static RobotMovement leftWallFollower(DistanceMeasurement &measurement) {
        if (measurement[WallSide::LEFT] > distanceThreshold) {
            return RobotMovement::LEFT;
        } else if (measurement[WallSide::TOP] > distanceThreshold) {
            return RobotMovement::FORWARD;
        } else if (measurement[WallSide::RIGHT] > distanceThreshold) {
            return RobotMovement::RIGHT;
        } else {
            return RobotMovement::BACK;
        }
    }

    static RobotMovement rightWallFollower(DistanceMeasurement &measurement) {
        if (measurement[WallSide::RIGHT] > distanceThreshold) {
            return RobotMovement::RIGHT;
        } else if (measurement[WallSide::TOP] > distanceThreshold) {
            return RobotMovement::FORWARD;
        } else if (measurement[WallSide::LEFT] > distanceThreshold) {
            return RobotMovement::LEFT;
        } else {
            return RobotMovement::BACK;
        }
    }

    static RobotMovement bruteForce(DistanceMeasurement &measurement) {
        // TODO: probably something does not work as it should
        if (measurement[WallSide::TOP] > distanceThreshold && measurement[WallSide::LEFT] > distanceThreshold &&
            measurement[WallSide::RIGHT] > distanceThreshold) {
            return static_cast<RobotMovement>(rand() % 3);
        } else if (measurement[WallSide::LEFT] > distanceThreshold &&
                   measurement[WallSide::RIGHT] > distanceThreshold) {
            return static_cast<RobotMovement>(rand() % 3);
        } else if (measurement[WallSide::LEFT] > distanceThreshold) {
            return RobotMovement::LEFT;
        } else if (measurement[WallSide::RIGHT] > distanceThreshold) {
            return RobotMovement::RIGHT;
        } else if (measurement[WallSide::TOP] > distanceThreshold) {
            return RobotMovement::FORWARD;
        } else {
            return RobotMovement::BACK;
        }
    }

    static RobotMovement wavePropagation(const DistanceMeasurement &measurement) {
        return RobotMovement::LEFT;
    }
};


#endif //MICROMOUSE_MAZESOLVER_H
