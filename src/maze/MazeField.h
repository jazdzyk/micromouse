//
// Created by Kuba Jazdzyk on 8/17/19.
//

#pragma once

#ifndef MICROMOUSE_MAZEFIELD_H
#define MICROMOUSE_MAZEFIELD_H


#include <map>
#include <src/utils/Enums.h>
#include "MazeWall.h"
#include <src/utils/utils.h>
#include <src/utils/JsonKeys.h>

class MazeField : public Serializable {
public:
    using WallSide = Direction;
    using Walls = std::map<WallSide, MazeWall*>;

    MazeField(Coordinate& coordinate, MazeSize mazeSize);
    MazeField(Coordinate &coordinate, MazeField::Walls walls);
    MazeField(const QJsonObject& json);
    ~MazeField();

    Coordinate getCoordinate() const;

    MazeWall *getWallAt(WallSide side) const;
    bool hasWallAt(WallSide side) const;
    void setWallAt(MazeField::WallSide side, bool shouldBeActive) const;
    void toggleWallAt(WallSide side) const;
    void removeWall(Coordinate& nextCoordinate);

    MazeField *getNeighbourAssociatedWithWallAt(WallSide side) const;
    void setNeighbourAssociatedWithWallAt(WallSide side, MazeField* neighbour) const;

    // Serializable methods
    QJsonObject serializeToJson() const;
    void deserializeJson(const QJsonObject& json);

private:
    Walls walls;
    Coordinate coordinate;

    void removeWall(WallSide side) const;
};


#endif //MICROMOUSE_MAZEFIELD_H
