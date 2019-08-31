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

class Maze : public Serializable {
public:
    using MazeFields = std::vector<std::vector<MazeField *>>;
    using IterateOverFieldsFunction = std::function<void(MazeField*)>;

    Maze(MazeSize size, SimulationMode simulationMode, std::optional<const Maze::MazeFields> fields = {});
    explicit Maze(const QJsonObject& json);
    ~Maze() override;

    [[nodiscard]] MazeSize getSize() const;
    [[nodiscard]] SimulationMode getSimulationMode() const;
    [[nodiscard]] MazeFields getFields() const;
    MazeField* getFieldAt(const Coordinate &coordinate) const;

    void iterateOverAllFields(const IterateOverFieldsFunction& function) const;

    // Serializable methods
    [[nodiscard]] QJsonObject serializeToJson() const override;
    void deserializeJson(const QJsonObject& json) override;

private:
    MazeSize size;
    SimulationMode simulationMode;

    MazeFields fields;

    [[nodiscard]] MazeFields randomlyGenerateFields() const;
};


#endif //MICROMOUSE_MAZE_H
