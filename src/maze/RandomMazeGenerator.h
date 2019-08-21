//
// Created by Kuba Jazdzyk on 8/18/19.
//

#ifndef MICROMOUSE_RANDOMMAZEGENERATOR_H
#define MICROMOUSE_RANDOMMAZEGENERATOR_H


#include <vector>
#include <stack>
#include "MazeField.h"

class RandomMazeGenerator {
public:
    using MazeBoard = std::vector<std::vector<MazeField *>>;

    explicit RandomMazeGenerator(MazeSize mazeSize);

    MazeBoard generate();

private:
    using Fields = std::vector<MazeField *>;
    using Neighbours = std::map<Direction, MazeField *>;
    using FieldsHistory = std::stack<MazeField *>;

    MazeSize mazeSize;

    Fields fields;
    MazeField *currentField;

    void createFields();
    [[nodiscard]] int calculateFieldPosition(const Coordinate& coordinate) const;
    Neighbours getNeighboursFor(Coordinate& coordinate) const;
    [[nodiscard]] Neighbours getAvailableNeighbours() const;
    [[nodiscard]] MazeField* findNextField() const;

    [[nodiscard]] MazeBoard createOutputFieldsForm() const;
    MazeField::Walls prepareMazeFieldWalls(Coordinate& coordinate) const;

    [[nodiscard]] int calculateMazeSideLength() const;
};


#endif //MICROMOUSE_RANDOMMAZEGENERATOR_H
