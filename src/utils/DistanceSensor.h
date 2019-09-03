//
// Created by Kuba Jazdzyk on 8/31/19.
//

#ifndef MICROMOUSE_DISTANCESENSOR_H
#define MICROMOUSE_DISTANCESENSOR_H


#include <functional>
#include "SensorProtocol.h"

template <int mazeFieldSize = 15, int toWallFactor = 15>
class DistanceSensor : public SensorProtocol {
public:
    using WallSide = MazeWall::WallSide;

    DistanceSensor(WallSide location, bool broken = false) {
        Log::print("DistanceSensor::DistanceSensor(location, broken)");
    }

    [[nodiscard]] double measure() const override {
        Log::print("DistanceSensor::double measure()");
        // TODO: connect real-world sensor and return its measurement value here
        return 0;
    }

    [[nodiscard]] double measureDistance(MazeWall *closestWall) const {
        Log::print("DistanceSensor::measureDistance(*closestWall)");
        if (closestWall->isActive()) {
            return (toWallFactor / 100.0) * mazeFieldSize;
        } else {
            std::function<bool(MazeWall*, MazeWall*&)> isWallLocated = [](MazeWall *wall, MazeWall *&newWall) {
                if (!wall->getNeighbour()) {
                    return false;
                }

                auto neighbourWall = wall->getNeighbourWallAt(wall->getSide());
                if (neighbourWall) {
                    newWall = *neighbourWall;
                    return newWall->isActive();
                }
                return false;
            };

            MazeWall *currentlyCheckedWall = new MazeWall(*closestWall);
            MazeWall *_checkWall;

            int howMany = 1;
            while (!isWallLocated(currentlyCheckedWall, _checkWall) && howMany != mazeFieldSize) {
                howMany++;
                currentlyCheckedWall = _checkWall;
            }

            return (howMany + toWallFactor / 100.0) * mazeFieldSize;
        }
    }
};


#endif //MICROMOUSE_DISTANCESENSOR_H
