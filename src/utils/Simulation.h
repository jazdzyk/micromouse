//
// Created by Kuba Jazdzyk on 8/29/19.
//

#ifndef MICROMOUSE_SIMULATION_H
#define MICROMOUSE_SIMULATION_H


#include <src/maze/Maze.h>
#include "Robot.h"
#include <QTimer>
#include <QObject>
#include <utility>
#include <src/views/MazeView.h>
#include <src/protocols/delegates/SimulationDelegate.h>

class Simulation {
public:
    using WallSide = MazeWall::WallSide;
    using RobotAlgorithms = std::pair<RobotAlgorithm, std::optional<RobotAlgorithm>>;
    using RobotDelegates = std::pair<std::optional<RobotDelegate *>, std::optional<RobotDelegate *>>;
    using RobotSurrounding = MazeView::WallSurrounding ;

    Simulation(Maze *maze, const RobotAlgorithms &robotAlgorithms, const RobotDelegates &robotDelegates,
               std::optional<SimulationDelegate *> simulationDelegate = {});
    ~Simulation();

    void start() const;
    void pause() const;
    void reset();

    void updateRobotSurrounding(int robotId, const RobotSurrounding& surrounding) const;
    void updateRobotCurrentPosition(int robotId, const Coordinate& coordinate) const;

private:
    const int ITERATION_TIME = 50;

    std::optional<SimulationDelegate *> delegate;

    Robot<15, 100, 12, 20> *robot1;
    std::optional<Robot<15, 100, 12, 20> *> robot2;

    Maze *maze;
    RobotAlgorithms algorithms;

    QTimer *timer1;
    QTimer *timer2;

    void simulate(Robot<15, 100, 12, 20>* robot, QTimer *timer) const;

    [[nodiscard]] Robot<15, 100, 12, 20> *buildRobot(int id, RobotAlgorithm algorithm, const Coordinate &coordinate,
                                                     std::optional<RobotDelegate *> delegate) const;
    Robot<15, 100, 12, 20>* resetRobot(Robot<15, 100, 12, 20> *robot);

    void initializeTimers();
    void resetTimers();

    [[nodiscard]] int getMazeLength() const;
    [[nodiscard]] Coordinate getMazeEndCoordinate() const;

    static void delay(double seconds = 1.);
};


#endif //MICROMOUSE_SIMULATION_H
