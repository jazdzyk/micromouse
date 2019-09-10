//
// Created by Kuba Jazdzyk on 8/21/19.
//
#pragma once

#ifndef MICROMOUSE_MAZEFIELDVIEW_H
#define MICROMOUSE_MAZEFIELDVIEW_H


#include <QtWidgets/QLabel>
#include <src/utils/Coordinate.h>
#include <src/utils/Enums.h>
#include <src/protocols/delegates/MazeFieldViewDelegate.h>
#include <QApplication>
#include <QDesktopWidget>
#include <QMouseEvent>

class MazeFieldView : public QLabel {
    Q_OBJECT

public:
    using WallSide = MazeField::WallSide;

    MazeFieldView(const Coordinate &coordinate, MazeSize mazeSize, std::optional<MazeFieldViewDelegate *> delegate = {},
                  MazeFieldType mazeFieldType = ::PLAIN);
    MazeFieldView(MazeField *mazeField, MazeSize mazeSize, std::optional<MazeFieldViewDelegate *> delegate = {});
    ~MazeFieldView() override;

    void setEnabled(bool enabled);
    void setBorder(WallSide side, bool border);
    void setFieldType(MazeFieldType type);

    void setColor();

    [[nodiscard]] MazeField* getMazeField() const;
    [[nodiscard]] Coordinate getCoordinate() const;

    void showRobot(bool robot, int rotation = 0);
    void resetCurrentRobotRotationWith(int angle);
    [[nodiscard]] int getCurrentRobotRotationAngle() const;

private:
    std::optional<MazeFieldViewDelegate *> delegate;

    MazeSize mazeSize;
    MazeFieldType fieldType;

    bool isEnabled;

    MazeField* mazeField;

    int currentRobotRotation;

    void updateBorders();
    [[nodiscard]] bool isEdgeSide(WallSide side) const;

    [[nodiscard]] int calculateMazeSideLength() const;

    void paintFieldIfNeeded();

    void mousePressEvent(QMouseEvent *event) override;
};


#endif //MICROMOUSE_MAZEFIELDVIEW_H
