//
// Created by Kuba Jazdzyk on 8/18/19.
//

#ifndef MICROMOUSE_RANDOMMAZEGENERATOR_H
#define MICROMOUSE_RANDOMMAZEGENERATOR_H


#include <vector>
#include <stack>
#include "MazeField.h"

/**
 * The RandomMazeGenerator class task is to randomly generate maze to be possible to solve by Micromouse robot.
 */
class RandomMazeGenerator {
public:
    using MazeBoard = std::vector<std::vector<MazeField *>>;

    /**
     * RandomMazeGenerator class constructor.
     *
     * @param mazeSize a size of a maze to be generated
     */
    explicit RandomMazeGenerator(MazeSize mazeSize);

    /**
     * A public method which generates a vector of vectors of maze fields which create a maze.
     *
     * @return a vector of vectors of maze fields
     */
    MazeBoard generate();

private:
    using Fields = std::vector<MazeField *>;
    using Neighbours = std::map<Direction, MazeField *>;
    using FieldsHistory = std::stack<MazeField *>;

    MazeSize mazeSize;

    Fields fields;
    MazeField *currentField;

    /**
     * A private method which creates maze fields.
     */
    void createFields();

    /**
     * A private method which calculates the position of a maze field with a given coordinate in a vector.
     *
     * @param coordinate a coordinate of a maze field
     * @return a position of a maze field in a vector
     */
    [[nodiscard]] int calculateFieldPosition(const Coordinate &coordinate) const;

    /**
     * A private method which returns neighbour fields for a field with a given coordinate.
     *
     * @param coordinate a coordinate of a maze field
     * @return a map of neighbour fields specified by their directions
     */
    Neighbours getNeighboursFor(Coordinate &coordinate) const;

    /**
     * A private method which returns available neighbour fields.
     *
     * @return a map of neighbou fields specified by their directions
     */
    [[nodiscard]] Neighbours getAvailableNeighbours() const;

    /**
     * A private method which searches for next maze field to process.
     *
     * @return a next maze field
     */
    [[nodiscard]] MazeField *findNextField() const;

    /**
     * A private method which modifies 1-dimensional vector into the final output format
     * which is a vector of vectors of maze fields.
     *
     * @return a vector of vector of maze fields
     */
    [[nodiscard]] MazeBoard createOutputFieldsForm() const;

    /**
     * A private method which prepares maze field's walls at the given coordinate.
     *
     * @param coordinate a coordinate of a maze field
     * @return
     */
    MazeField::Walls prepareMazeFieldWalls(Coordinate &coordinate) const;

    /**
     *
     * @return a map of walls specified by its sides on a field
     */
    [[nodiscard]] int calculateMazeSideLength() const;
};


#endif //MICROMOUSE_RANDOMMAZEGENERATOR_H
