//
// Created by Kuba Jazdzyk on 8/31/19.
//

#ifndef MICROMOUSE_ROBOT_H
#define MICROMOUSE_ROBOT_H


#include <optional>
#include <src/maze/MazeWall.h>
#include <src/protocols/delegates/RobotDelegate.h>
#include "Enums.h"
#include "Coordinate.h"

template<int WheelRadius, int MotorMaxRpm, int MazeFieldSize, int ToWallFactor>
class Robot {
public:
    using WallSide = MazeWall::WallSide;
    using Surrounding = std::map<WallSide, MazeWall *>;
    using SensorsValues = std::map<WallSide, double>;

    Robot(RobotAlgorithm algorithm, const Coordinate &startPosition, int id,
          std::optional<RobotDelegate *> delegate = {}) : mazeSolver(new MazeSolver<MazeFieldSize>(algorithm)),
                                                          currentPosition(startPosition),
                                                          delegate(std::move(delegate)) {
        this->leftSensor = new DistanceSensor<12, 20>(RobotMovement::LEFT);
        this->rightSensor = new DistanceSensor<12, 20>(RobotMovement::RIGHT);
        this->frontSensor = new DistanceSensor<12, 20>(RobotMovement::FORWARD);

        this->leftMotor = new RobotMotor<MotorMaxRpm>;
        this->rightMotor = new RobotMotor<MotorMaxRpm>;
    }

    ~Robot();

    void move() const;
    void goToStart() const;
    void finish() const;

    void updateSurrounding(Surrounding surrounding) const;

    Coordinate getCurrentPosition() const;
    void updateCurrentPosition(const Coordinate& newPosition) const;

    double getCurrentSpeed() const;

private:
    std::optional<RobotDelegate *> delegate;

    MazeSolver<MazeFieldSize> *mazeSolver;

    RobotMotor<MotorMaxRpm> *leftMotor;
    RobotMotor<MotorMaxRpm> *rightMotor;

    DistanceSensor<MazeFieldSize, ToWallFactor> *leftSensor;
    DistanceSensor<MazeFieldSize, ToWallFactor> *frontSensor;
    DistanceSensor<MazeFieldSize, ToWallFactor> *rightSensor;

    Coordinate currentPosition;
    Surrounding currentSurrounding;

    void go(RobotMovement movement) const;

    void setMotorsSpeed(double leftMotorPwm, double rightMotorPwm) const;
    SensorsValues readSensorsValues() const;
};


#endif //MICROMOUSE_ROBOT_H
