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

class MazeWall;

/**
 * The MazeField class implements Serializable protocol.
 * It represents a single maze field which is a part of the entire Maze.
 */
class MazeField : public Serializable {
public:
    using WallSide = Direction;
    using Walls = std::map<WallSide, MazeWall *>;

    /**
     * Maze class constructor.
     *
     * @param coordinate a coordinate of the field
     * @param mazeSize a size of a maze which the field is part of
     */
    MazeField(const Coordinate &coordinate, MazeSize mazeSize);

    /**
     * Maze class constructor.
     *
     * @param coordinate a coordinate of the field
     * @param walls a map of MazeWall objects specified by directions
     */
    MazeField(const Coordinate &coordinate, MazeField::Walls walls);

    /**
     * Maze class constructor.
     *
     * @param json a JSON object containing serialized MazeField data
     */
    explicit MazeField(const QJsonObject &json);

    /**
     * Maze class destructor.
     */
    ~MazeField() override;

    /**
     * A public getter of a coordinate of the field.
     *
     * @return a coordinate of the field
     */
    [[nodiscard]] Coordinate getCoordinate() const;

    /**
     * A public method which returns a wall at a specified side of the field.
     *
     * @param side a side of the desired wall
     * @return a wall
     */
    [[nodiscard]] MazeWall *getWallAt(WallSide side) const;

    /**
     * A public method which gives information whether the field has an active wall at a specified side.
     *
     * @param side a side of the questioned wall
     * @return an appropriate boolean flag
     */
    [[nodiscard]] bool hasWallAt(WallSide side) const;

    /**
     * A public method which enables setting an activeness state of a wall at a specified side of the field.
     *
     * @param side a side of the desired wall
     * @param shouldBeActive an appropriate boolean flag
     */
    void setWallAt(MazeField::WallSide side, bool shouldBeActive) const;

    /**
     * A public method which enables toggling an activeness state of a wall at a specified side of the field.
     *
     * @param side a side of the desired wall
     */
    void toggleWallAt(WallSide side) const;

    /**
     * A public method which enables to 'remove' a wall in a direction to a given coordinate,
     * which means that the desired wall and its neighbour's counterpart are set inactive.
     *
     * @param nextCoordinate a coordinate of a field in a desired direction
     */
    void removeWall(const Coordinate &nextCoordinate);

    /**
     * A public method which returns a neighbour field, if exists,
     * in a direction of a wall at a specified side of the field.
     *
     * @param side a side of the desired wall
     * @return a neighbour maze field
     */
    [[nodiscard]] std::optional<MazeField *> getNeighbourAssociatedWithWallAt(WallSide side) const;

    /**
     * A public method which enables setting a neighbour field
     * in a direction of a wall at a specified side of the field.
     *
     * @param side a side of the desired wall
     * @param neighbour a neighbour maze field
     */
    void setNeighbourAssociatedWithWallAt(WallSide side, MazeField *neighbour) const;

    /**
     * A public method which gives information whether the field was visited.
     *
     * @return an appropriate boolean flag
     */
    [[nodiscard]] bool wasVisited() const;

    /**
     * A public method which enables setting information whether the field was visited.
     *
     * @param visited an appropriate boolean flag
     */
    void setVisited(bool visited);

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
    Walls walls;
    Coordinate coordinate;

    bool _wasVisited;

    /**
     * A private method which 'removes' a wall in a specified side of the field.
     * It means that the wall and its neighbour's counterpart are set inactive.
     *
     * @param side a side of the desired wall
     */
    void removeWall(WallSide side) const;
};


#endif //MICROMOUSE_MAZEFIELD_H
