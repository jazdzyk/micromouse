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
#include <cmath>

class MazeField : public Serializable {
public:
    using WallSide = Direction;
    using Walls = std::map<WallSide, MazeWall*>;

    MazeField(const Coordinate &coordinate, MazeSize mazeSize);
    MazeField(const Coordinate &coordinate, MazeField::Walls walls);
    explicit MazeField(const QJsonObject& json);
    ~MazeField() override;

    [[nodiscard]] Coordinate getCoordinate() const;

    [[nodiscard]] MazeWall *getWallAt(WallSide side) const;
    [[nodiscard]] bool hasWallAt(WallSide side) const;
    void setWallAt(MazeField::WallSide side, bool shouldBeActive) const;
    void toggleWallAt(WallSide side) const;
    void removeWall(const Coordinate &nextCoordinate);

    [[nodiscard]] MazeField *getNeighbourAssociatedWithWallAt(WallSide side) const;
    void setNeighbourAssociatedWithWallAt(WallSide side, MazeField* neighbour) const;

    [[nodiscard]] bool wasVisited() const;
    void setVisited(bool visited);

    // Serializable methods
    [[nodiscard]] QJsonObject serializeToJson() const override;
    void deserializeJson(const QJsonObject& json) override;

private:
    Walls walls;
    Coordinate coordinate;

    bool _wasVisited;

    void removeWall(WallSide side) const;
};


#endif //MICROMOUSE_MAZEFIELD_H
