//
// Created by Kuba Jazdzyk on 8/17/19.
//
#pragma once

#ifndef MICROMOUSE_MAZEWALL_H
#define MICROMOUSE_MAZEWALL_H


#include <src/protocols/Serializable.h>
#include <src/utils/Enums.h>
#include <optional>
#include <src/utils/Logging.h>
#include <src/utils/Coordinate.h>
#include <utility>
#include "MazeField.h"

class MazeField;

class MazeWall : public Serializable {
public:
    using WallSide = Direction;
    using NeighbourField = std::optional<MazeField *>;

    MazeWall(bool active, bool blocked, WallSide side, NeighbourField neighbourField = std::nullopt);
    explicit MazeWall(const QJsonObject& json);

    bool isActive() const;
    bool isBlocked() const;
    void setActive(bool active);
    void setBlocked(bool blocked);
    void toggleActive();

    [[nodiscard]] WallSide getSide() const;
    void setSide(WallSide side);

    [[nodiscard]] const NeighbourField &getNeighbour() const;
    [[nodiscard]] std::optional<MazeWall *> getNeighbourWallAt(WallSide side) const;
    void setNeighbour(const NeighbourField &neighbour);

    void removeWall();

    static MazeWall *createDefault(MazeWall::WallSide side, const Coordinate &coordinate,
                                   MazeSize mazeSize, bool shouldBeActive = false);

    // Serializable methods
    [[nodiscard]] QJsonObject serializeToJson() const override;
    void deserializeJson(const QJsonObject &json) override;

private:
    bool active;
    bool blocked;
    WallSide side;
    NeighbourField neighbour;

    [[nodiscard]] WallSide getOppositeSide() const;
};


#endif //MICROMOUSE_MAZEWALL_H
