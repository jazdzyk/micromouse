//
// Created by Kuba Jazdzyk on 8/31/19.
//

#ifndef MICROMOUSE_ROBOT_H
#define MICROMOUSE_ROBOT_H


#include <optional>
#include <utility>
#include <src/maze/MazeWall.h>
#include <src/protocols/delegates/RobotDelegate.h>
#include "Enums.h"
#include "Coordinate.h"
#include "MazeSolver.h"
#include "DistanceSensor.h"
#include "RobotMotor.h"

template<int wheelRadius, int motorMaxRpm, int mazeFieldSize, int toWallFactor>
class Robot {
public:
    using WallSide = MazeWall::WallSide;
    using Surrounding = std::map<WallSide, MazeWall *>;
    using SensorsValues = std::map<WallSide, double>;

    Robot(int id, RobotAlgorithm algorithm, Coordinate startPosition,
          std::optional<RobotDelegate *> delegate = {}) : mazeSolver(new MazeSolver<mazeFieldSize>(algorithm)),
                                                          currentPosition(std::move(startPosition)),
                                                          delegate(std::move(delegate)), id(id) {
        Log::print("Robot::Robot(id: " + std::to_string(id) + ", algorithm, &startPosition, delegate?)");
        this->leftSensor = new DistanceSensor<12, 20>(WallSide::LEFT);
        this->rightSensor = new DistanceSensor<12, 20>(WallSide::RIGHT);
        this->frontSensor = new DistanceSensor<12, 20>(WallSide::TOP);

        this->leftMotor = new RobotMotor<motorMaxRpm>;
        this->rightMotor = new RobotMotor<motorMaxRpm>;
    }

    ~Robot() {
        Log::print("Robot::~Robot()");
        utils::destruct(this->mazeSolver);
        utils::destruct(this->leftMotor);
        utils::destruct(this->rightMotor);
        utils::destruct(this->leftSensor);
        utils::destruct(this->frontSensor);
    }

    void move() const {
        Log::print("Robot::move()");
        go(this->mazeSolver->solve(readSensorsValues()));
    }

    void goToStart() const {
        Log::print("Robot::goToStart()");
        if (this->delegate) {
            auto delegate = *this->delegate;
            delegate->robotShouldGoToStart(this->id);
        }
    }

    void finish() const {
        Log::print("Robot::finish()");
        if (this->delegate) {
            auto delegate = *this->delegate;
            delegate->robotDidFinish(this->id);
        }
    }

    void updateSurrounding(MazeWall *left, MazeWall *right, MazeWall *front) const {
        Log::print("Robot::updateSurrounding(surrounding)");
        this->currentSurrounding = {
                {WallSide::LEFT, left},
                {WallSide::RIGHT, right},
                {WallSide::TOP, front},
        };
    }

    [[nodiscard]] Coordinate getCurrentPosition() const {
        Log::print("Robot::getCurrentPosition()");
        return this->currentPosition;
    }

    void updateCurrentPosition(const Coordinate &newPosition) const {
        Log::print("Robot::updateCurrentPosition(&newPosition)");
        this->currentPosition = newPosition;
    }

    [[nodiscard]] double getCurrentSpeed() const {
        Log::print("Robot::getCurrentSpeed()");
        // TODO: implement in real-world application
        return wheelRadius * 0.;
    }

private:
    int id;
    std::optional<RobotDelegate *> delegate;

    MazeSolver<mazeFieldSize> *mazeSolver;

    RobotMotor<motorMaxRpm> *leftMotor;
    RobotMotor<motorMaxRpm> *rightMotor;

    DistanceSensor<mazeFieldSize, toWallFactor> *leftSensor;
    DistanceSensor<mazeFieldSize, toWallFactor> *frontSensor;
    DistanceSensor<mazeFieldSize, toWallFactor> *rightSensor;

    Coordinate currentPosition;
    Surrounding currentSurrounding;

    void go(RobotMovement movement) const {
        Log::print("Robot::go(movement)");
        if (this->delegate) {
            auto delegate = *this->delegate;
            delegate->robotShouldGoTo(this->id, movement);
        }
    }

    void setMotorsSpeed(double leftMotorPwm, double rightMotorPwm) const {
        Log::print("Robot::setMotorsSpeed(leftMotorPwm: " + std::to_string(leftMotorPwm) + ", rightMotorPwm: " +
                   std::to_string(rightMotorPwm) + ")");
        this->leftMotor->run(leftMotorPwm);
        this->rightMotor->run(rightMotorPwm);
    }

    [[nodiscard]] SensorsValues readSensorsValues() const {
        Log::print("Robot::readSensorsValues()");
        return {
                {WallSide::LEFT, this->leftSensor->measureDistance(this->currentSurrounding[WallSide::LEFT])},
                {WallSide::RIGHT, this->leftSensor->measureDistance(this->currentSurrounding[WallSide::RIGHT])},
                {WallSide::TOP, this->leftSensor->measureDistance(this->currentSurrounding[WallSide::TOP])},
        };
    }
};


#endif //MICROMOUSE_ROBOT_H
