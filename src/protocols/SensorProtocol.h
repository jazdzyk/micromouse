//
// Created by Kuba Jazdzyk on 8/31/19.
//

#ifndef MICROMOUSE_SENSORPROTOCOL_H
#define MICROMOUSE_SENSORPROTOCOL_H


#include <src/maze/MazeWall.h>

/**
 * SensorProtocol is a general protocol for different types of sensors' representations.
 */
class SensorProtocol {
public:
    /**
     * SensorProtocol class destructor.
     */
    virtual ~SensorProtocol() = default;

    /**
     * A public method which enables measurement.
     *
     * @return a measured value
     */
    virtual double measure() const = 0;

    /**
     * A public getter which gives information whether a sensor is currently broken.
     *
     * @return an appropriate boolean flag
     */
    [[nodiscard]] bool isBroken() const {
        Log::print("SensorProtocol::bool isBroken()");
        return this->broken;
    }

    /**
     * A public setter which sets information whether a sensor is broken.
     *
     * @param broken an appropriate boolean flag
     */
    void setBroken(bool broken) {
        Log::print("SensorProtocol::setBroken(broken)");
        this->broken = broken;
    }

protected:
    bool broken;
};


#endif //MICROMOUSE_SENSORPROTOCOL_H
