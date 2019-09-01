//
// Created by Kuba Jazdzyk on 8/18/19.
//

#include "RandomMazeGenerator.h"

RandomMazeGenerator::RandomMazeGenerator(MazeSize mazeSize) : mazeSize(mazeSize) {
    Log::print("RandomMazeGenerator::RandomMazeGenerator(mazeSize)");
    createFields();
    this->currentField = this->fields[rand() % this->fields.size()];
}

RandomMazeGenerator::MazeBoard RandomMazeGenerator::generate() {
    Log::print("RandomMazeGenerator::generate()");
    FieldsHistory fieldsHistory;

    while (true) {
        this->currentField->setVisited(true);
        auto *next = findNextField();

        if (next != nullptr) {
            fieldsHistory.push(this->currentField);
            this->currentField->removeWall(next->getCoordinate());
            this->currentField = next;
        } else if (!fieldsHistory.empty()) {
            this->currentField = fieldsHistory.top();
            fieldsHistory.pop();
        } else if (fieldsHistory.empty()) {
            break;
        }
    }

    return createOutputFieldsForm();
}

void RandomMazeGenerator::createFields() {
    Log::print("RandomMazeGenerator::createFields()");
    auto mazeSideLength = calculateMazeSideLength();
    for (auto row = 0; row < mazeSideLength; ++row) {
        for (auto column = 0; column < mazeSideLength; ++column) {
            auto coordinate = Coordinate(row, column);
            this->fields.push_back(new MazeField(coordinate, prepareMazeFieldWalls(coordinate)));
            std::cout << "//|(" + std::to_string(column) + ", " + std::to_string(row) + ") = (" +
                         std::to_string(this->fields[calculateFieldPosition(coordinate)]->getCoordinate().column) + ", " +
                         std::to_string(this->fields[calculateFieldPosition(coordinate)]->getCoordinate().row) + ")|\n";
        }
    }

    using WallSide = MazeField::WallSide;
    for (auto row = 0; row < mazeSideLength; ++row) {
        for (auto column = 0; column < mazeSideLength; ++column) {
            auto coordinate = Coordinate(row, column);
            auto neighbours = getNeighboursFor(coordinate);
            auto fieldPosition = calculateFieldPosition(coordinate);

            this->fields[fieldPosition]->setNeighbourAssociatedWithWallAt(WallSide::LEFT,
                                                                          neighbours.at(Direction::LEFT));
            this->fields[fieldPosition]->setNeighbourAssociatedWithWallAt(WallSide::RIGHT,
                                                                          neighbours.at(Direction::RIGHT));
            this->fields[fieldPosition]->setNeighbourAssociatedWithWallAt(WallSide::TOP,
                                                                          neighbours.at(Direction::TOP));
            this->fields[fieldPosition]->setNeighbourAssociatedWithWallAt(WallSide::BOTTOM,
                                                                          neighbours.at(Direction::BOTTOM));
            std::cout << "*|(" + std::to_string(column) + ", " + std::to_string(row) + ") = (" +
                         std::to_string(this->fields[calculateFieldPosition(coordinate)]->getCoordinate().column) + ", " +
                         std::to_string(this->fields[calculateFieldPosition(coordinate)]->getCoordinate().row) + ")|\n";
        }
    }
}

int RandomMazeGenerator::calculateFieldPosition(const Coordinate &coordinate) const {
    Log::print("RandomMazeGenerator::calculateFieldPosition(&coordinate)");
    auto mazeSizeLength = calculateMazeSideLength() - 1;
    if (coordinate.column < 0 || coordinate.column > mazeSizeLength ||
        coordinate.row < 0 || coordinate.row > mazeSizeLength) {
        return -1;
    }

    return coordinate.column + coordinate.row * (mazeSizeLength + 1);
}

RandomMazeGenerator::Neighbours RandomMazeGenerator::getNeighboursFor(Coordinate &coordinate) const {
    Log::print("RandomMazeGenerator::getNeighboursFor(&coordinate)");
    std::map<Direction, int> neighboursIndices = {
            {Direction::TOP,    calculateFieldPosition(Coordinate(coordinate.row - 1, coordinate.column))},
            {Direction::RIGHT,  calculateFieldPosition(Coordinate(coordinate.row, coordinate.column + 1))},
            {Direction::BOTTOM, calculateFieldPosition(Coordinate(coordinate.row + 1, coordinate.column))},
            {Direction::LEFT,   calculateFieldPosition(Coordinate(coordinate.row, coordinate.column - 1))},
    };

    Neighbours neighbours;
    for (auto element : neighboursIndices) {
        neighbours.insert({element.first, element.second != -1 ? this->fields[element.second] : nullptr});
    }

    return neighbours;
}

RandomMazeGenerator::Neighbours RandomMazeGenerator::getAvailableNeighbours() const {
    Log::print("RandomMazeGenerator::getAvailableNeighbours()");
    auto coordinate = this->currentField->getCoordinate();
    std::map<Direction, int> neighboursIndices = {
            {Direction::TOP,    calculateFieldPosition(Coordinate(coordinate.row - 1, coordinate.column))},
            {Direction::RIGHT,  calculateFieldPosition(Coordinate(coordinate.row, coordinate.column + 1))},
            {Direction::BOTTOM, calculateFieldPosition(Coordinate(coordinate.row + 1, coordinate.column))},
            {Direction::LEFT,   calculateFieldPosition(Coordinate(coordinate.row, coordinate.column - 1))},
    };

    Neighbours neighbours;
    for (auto element : neighboursIndices) {
        if (element.second != -1 && !this->fields[element.second]->wasVisited()) {
            neighbours.insert({element.first, this->fields[element.second]});
        }
    }

    return neighbours;
}

MazeField *RandomMazeGenerator::findNextField() const {
    Log::print("RandomMazeGenerator::findNextField()");
    auto availableNeighbours = getAvailableNeighbours();

    std::vector<Direction> availableDirections;
    for (auto element : availableNeighbours) {
        availableDirections.push_back(element.first);
    }

    if (availableNeighbours.empty()) {
        return nullptr;
    }

    return availableNeighbours.at(availableDirections[rand() % availableNeighbours.size()]);
}

RandomMazeGenerator::MazeBoard RandomMazeGenerator::createOutputFieldsForm() const {
    Log::print("RandomMazeGenerator::createOutputFieldsForm()");
    MazeBoard outputFields;
    auto mazeSideLength = calculateMazeSideLength();
    for (auto x = 0; x < mazeSideLength; ++x) {
        auto beginning = this->fields.begin();
        outputFields.push_back(Fields(beginning + x * mazeSideLength, beginning + (1 + x) * mazeSideLength));
    }

    return outputFields;
}

MazeField::Walls RandomMazeGenerator::prepareMazeFieldWalls(Coordinate& coordinate) const {
    Log::print("RandomMazeGenerator::prepareMazeFieldWalls(&coordinate)");
    using WallSide = MazeField::WallSide;

    MazeField::Walls walls;
    for (auto i = 0; i < 4; ++i) {
        walls.insert({static_cast<WallSide >(i),
                      MazeWall::createDefault(static_cast<WallSide>(i), coordinate, this->mazeSize, true)});
    }

    return walls;
}

int RandomMazeGenerator::calculateMazeSideLength() const {
    Log::print("RandomMazeGenerator::calculateMazeSideLength()");
    return static_cast<int>(sqrt(static_cast<int>(this->mazeSize)));
}
