//
// Created by Kuba Jazdzyk on 8/15/19.
//

#ifndef MICROMOUSE_MAZE_H
#define MICROMOUSE_MAZE_H


#include <src/utils/Enums.h>
#include <vector>
#include <functional>
#include "MazeField.h"
#include "RandomMazeGenerator.h"
#include <cmath>
#include <QtCore/QJsonArray>

/**
 * The Maze class implements Serializable protocol.
 * It represents a maze which a Micromouse robot has to solve.
 */
class Maze : public Serializable {
public:
    using MazeFields = std::vector<std::vector<MazeField *>>;
    using IterateOverFieldsFunction = std::function<void(MazeField *)>;

    /**
     * Maze class constructor.
     *
     * @param size a size of a maze
     * @param simulationMode a simulation mode
     * @param fields a vector of vectors of maze fields
     */
    Maze(MazeSize size, SimulationMode simulationMode, std::optional<const Maze::MazeFields> fields = {});

    /**
     * Maze class constructor.
     *
     * @param json a JSON object containing serialized Maze data
     */
    explicit Maze(const QJsonObject &json);

    /**
     * Maze class destructor.
     */
    ~Maze() override;

    /**
     * A public getter of a size of a maze.
     *
     * @return a size of a maze
     */
    [[nodiscard]] MazeSize getSize() const;

    /**
     * A public getter of a simulation mode.
     *
     * @return a simulation mode
     */
    [[nodiscard]] SimulationMode getSimulationMode() const;

    /**
     * A public getter of a vector of vectors of maze fields.
     *
     * @return a vector of vectors of maze fields
     */
    [[nodiscard]] MazeFields getFields() const;

    /**
     * A public method which returns a maze field at a given coordinate.
     *
     * @param coordinate a coordinate of a desired field
     * @return a maze field
     */
    [[nodiscard]] MazeField *getFieldAt(const Coordinate &coordinate) const;

    /**
     * A public method which enables iterating over all fields in the maze.
     *
     * @param function a function to be call for every maze field
     */
    void iterateOverAllFields(const IterateOverFieldsFunction &function) const;

    /**
     * A public method which enables assigning neighbours to all fields in the maze.
     */
    void assignNeighboursToFields() const;

    // Serializable methods
    /**
     * A public method which enables JSON serialization.
     *
     * @return a serialized JSON object
     */
    [[nodiscard]] QJsonObject serializeToJson() const override;

    /**
     * A public method which enables JSON deserialization.
     *
     * @param json a serialized json object
     */
    void deserializeJson(const QJsonObject &json) override;

private:
    MazeSize size;
    SimulationMode simulationMode;

    MazeFields fields;

    /**
     * A private method which enables random generation of fields.
     * The purpose is to give a user randomly generated maze for a Micromouse robot to solve
     * in case she/he didn't want to create their own maze.
     *
     * @return a vector of vectors of maze fields
     */
    [[nodiscard]] MazeFields randomlyGenerateFields() const;
};


#endif //MICROMOUSE_MAZE_H
