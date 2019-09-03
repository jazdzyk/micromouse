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

/**
 * The MazeWall class implements Serializable protocol.
 * It represents a single wall which is a part of the MazeField.
 */
class MazeWall : public Serializable {
public:
    using WallSide = Direction;
    using NeighbourField = std::optional<MazeField *>;

    /**
     * MazeWall class constructor.
     *
     * @param active an appropriate boolean flag related to the activeness state
     * @param blocked an appropriate boolean information whether the wall is blocked
     * @param side a side of the wall on a field
     * @param neighbourField a neighbour field to the wall
     */
    MazeWall(bool active, bool blocked, WallSide side, NeighbourField neighbourField = std::nullopt);

    /**
     * MazeWall class constructor.
     *
     * @param json a JSON object containing serialized MazeWall data
     */
    explicit MazeWall(const QJsonObject &json);

    /**
     * A public getter of an activeness state of the wall.
     *
     * @return an appropriate boolean flag
     */
    [[nodiscard]] bool isActive() const;

    /**
     * A public getter of information whether the wall is currently blocked.
     *
     * @return an appropriate boolean flag
     */
    [[nodiscard]] bool isBlocked() const;

    /**
     * A public setter of an activeness state of the wall.
     *
     * @param active an appropriate boolean flag
     */
    void setActive(bool active);

    /**
     * A public setter of information whether the wall is currently blocked.
     *
     * @param blocked an appropriate boolean flag
     */
    void setBlocked(bool blocked);

    /**
     * A public method which enables toggling an activeness state of the wall.
     */
    void toggleActive();

    /**
     * A public getter of a side of the wall on a maze field.
     *
     * @return a side of the wall
     */
    [[nodiscard]] WallSide getSide() const;

    /**
     * A public setter of a side of the wall on a maze field.
     *
     * @param side a side of the wall
     */
    void setSide(WallSide side);

    /**
     * A public getter of a neighbour field to the wall.
     *
     * @return a neighbour field
     */
    [[nodiscard]] const NeighbourField &getNeighbour() const;

    /**
     * A public method which returns a neighbour field's wall at a specified side of a maze field.
     *
     * @param side a side of the desired wall
     * @return a wall of a neighbour field
     */
    [[nodiscard]] std::optional<MazeWall *> getNeighbourWallAt(WallSide side) const;

    /**
     * A public setter of a neighbour field to the wall.
     *
     * @param neighbour a neighbour field
     */
    void setNeighbour(const NeighbourField &neighbour);

    /**
     * A public method which enables to 'remove' a wall,
     * which means that the wall and its neighbour's counterpart are set inactive.
     */
    void removeWall();

    /**
     * A public static method which creates a default MazeWall object.
     *
     * @param side a side of the wall on a field
     * @param coordinate a coordinate of a field which the wall is part of
     * @param mazeSize a size of a maze which wall's field is part of
     * @param shouldBeActive an appropriate boolean flag related to the activeness state
     * @return a new MazeWall object
     */
    static MazeWall *createDefault(MazeWall::WallSide side, const Coordinate &coordinate,
                                   MazeSize mazeSize, bool shouldBeActive = false);

    // Serializable methods
    /**
     * A public method which enables JSON serialization.
     *
     * @return a serialized json object
     */
    [[nodiscard]] QJsonObject serializeToJson() const override;

    /**
     * A public method which enables JSON deserialization.
     *
     * @param json a serialized json object
     */
    void deserializeJson(const QJsonObject &json) override;

private:
    bool active;
    bool blocked;

    WallSide side;
    NeighbourField neighbour;

    /**
     * A private method which returns the opposite side direction to this wall.
     *
     * @return an opposite side direction
     */
    [[nodiscard]] WallSide getOppositeSide() const;
};


#endif //MICROMOUSE_MAZEWALL_H
