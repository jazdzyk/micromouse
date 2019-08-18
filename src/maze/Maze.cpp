//
// Created by Kuba Jazdzyk on 8/15/19.
//

#include "Maze.h"

Maze::Maze(MazeSize size, SimulationMode simulationMode, std::optional<const Maze::MazeFields> fields)
        : size(size), simulationMode(simulationMode) {
    Log::print("Maze::Maze(size, simulationMode, fields?)");
    this->fields = fields ? *fields : randomlyGenerateFields();
}

Maze::Maze(const QJsonObject &json) {
    Log::print("Maze::Maze(const QJsonObject &json)");
    deserializeJson(json);
}

Maze::~Maze() {
    Log::print("Maze::~Maze()");
    iterateOverAllFields([](auto field) {
        utils::destruct(field);
    });
}

MazeSize Maze::getSize() const {
    Log::print("Maze::getSize()");
    return this->size;
}

SimulationMode Maze::getSimulationMode() const {
    Log::print("Maze::getSimulationMode()");
    return this->simulationMode;
}

Maze::MazeFields Maze::getFields() const {
    Log::print("Maze::getFields()");
    return this->fields;
}

MazeField *Maze::getFieldAt(Coordinate &coordinate) const {
    Log::print("Maze::getFieldAt(Coordinate &coordinate)");
    return this->fields[coordinate.vertical][coordinate.horizontal];
}

void Maze::iterateOverAllFields(const Maze::IterateOverFieldsFunction& function) const  {
    for (const auto& row : this->fields) {
        for (auto field : row) {
            function(field);
        }
    }
}

QJsonObject Maze::serializeToJson() const {
    Log::print("Maze::serializeToJson()");
    QJsonObject json;

    json.insert(JsonKeys::MAZE_SIZE, static_cast<int>(this->size));
    json.insert(JsonKeys::SIMULATION_MODE, static_cast<int>(this->simulationMode));

    QJsonArray jsonFields;
    iterateOverAllFields([jsonFields](MazeField* field) mutable {
        jsonFields.append(field->serializeToJson());
    });
    json.insert(JsonKeys::FIELDS, jsonFields);

    return json;
}

void Maze::deserializeJson(const QJsonObject &json) {
    Log::print("Maze::deserializeJson(&json)");
    this->size = static_cast<MazeSize>(json[JsonKeys::MAZE_SIZE].toInt());
    this->simulationMode = static_cast<SimulationMode>(json[JsonKeys::SIMULATION_MODE].toInt());

    auto jsonFields = json[JsonKeys::FIELDS].toArray();
    auto counter = 0, rowCount = -1, maxInRowCount = static_cast<int>(sqrt(static_cast<int>(this->size)));
    for (auto field : jsonFields) {
        if (counter++ % maxInRowCount == 0) {
            this->fields.push_back(std::vector<MazeField *>());
            rowCount++;
        }
        this->fields[rowCount].push_back(new MazeField(field.toObject()));
    }
}

Maze::MazeFields Maze::randomlyGenerateFields() const {
    Log::print("Maze::randomlyGenerateFields()");
    // TODO: implement RandomMazeGenerator class
//    return RandomMazeGenerator(this->size).generate();
}
