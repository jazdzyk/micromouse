//
// Created by Kuba Jazdzyk on 8/17/19.
//

#ifndef MICROMOUSE_MAZEVIEW_H
#define MICROMOUSE_MAZEVIEW_H


#include <QtWidgets/QGridLayout>
#include <src/protocols/delegates/MazeFieldViewDelegate.h>
#include <src/maze/Maze.h>
#include "src/protocols/delegates/MazeViewDelegate.h"
#include "MazeFieldView.h"

class MazeView : public QGridLayout, public MazeFieldViewDelegate {
public:
    using WallSide = MazeField::WallSide;
    using WallSurrounding = std::map<WallSide, MazeWall *>;
    using IterateOverFieldsFunction = std::function<void(MazeFieldView*)>;

    MazeView(MazeSize mazeSize, SimulationMode simulationMode, std::optional<MazeViewDelegate *> delegate = {});
    explicit MazeView(Maze *maze, bool withRobot = true, std::optional<MazeViewDelegate *> delegate = {});
    ~MazeView() override;

    void setEnabled(bool enabled) const;
    [[nodiscard]] Maze* getMaze() const;

    WallSurrounding moveRobotTo(int robotId, RobotMovement movement);
    WallSurrounding moveRobotToStart(int robotId);
    [[nodiscard]] Coordinate getCurrentRobotCoordinate() const;

    void showMazeExit() const;
    void showMazeEntry() const;

    void setDelegate(MazeViewDelegate* delegate);

    void iterateOverAllFields(const IterateOverFieldsFunction& function) const;

private:
    using FieldsRow = std::vector<MazeFieldView *>;
    using MazeBoard = std::vector<FieldsRow>;
    using MazeFields = Maze::MazeFields;

    MazeSize mazeSize;              // ???
    SimulationMode simulationMode;  // ???
    MazeBoard mazeBoard;
    Maze* maze;

    MazeFieldView *currentRobotField;

    std::optional<MazeViewDelegate *> delegate;

    void createEmptyUi();
    void createPredefinedUi(const MazeFields& mazeFields, bool withRobot);
    void createBoard(std::optional<const MazeFields *> mazeFields = {});

    void moveRobot(const Coordinate& coordinate, int rotation);
    void showRobots(bool withRobot1, bool withRobot2);

    [[nodiscard]] int getMazeLength() const;

    // MazeFieldViewDelegate method
    void mazeFieldWallDidSet(const MazeFieldViewInfo &info) override;

};


#endif //MICROMOUSE_MAZEVIEW_H
