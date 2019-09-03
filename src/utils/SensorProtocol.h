//
// Created by Kuba Jazdzyk on 8/31/19.
//

#ifndef MICROMOUSE_SENSORPROTOCOL_H
#define MICROMOUSE_SENSORPROTOCOL_H


#include <src/maze/MazeWall.h>

class SensorProtocol {
public:
    virtual ~SensorProtocol() = default;

    virtual double measure() const = 0;

    [[nodiscard]] bool isBroken() const {
        Log::print("SensorProtocol::bool isBroken()");
        return this->broken;
    }

    void setBroken(bool broken) {
        Log::print("SensorProtocol::setBroken(broken)");
        this->broken = broken;
    }

protected:
    bool broken;
};


#endif //MICROMOUSE_SENSORPROTOCOL_H
