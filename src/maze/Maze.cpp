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

    auto *jsonFields = new QJsonArray();
    iterateOverAllFields([jsonFields](MazeField* field) {
        jsonFields->append(field->serializeToJson());
    });
    json.insert(JsonKeys::FIELDS, *jsonFields);

    return json;
}

void Maze::deserializeJson(const QJsonObject &json) {
    Log::print("Maze::deserializeJson(&json)");
    this->size = static_cast<MazeSize>(json[JsonKeys::MAZE_SIZE].toInt());
    this->simulationMode = static_cast<SimulationMode>(json[JsonKeys::SIMULATION_MODE].toInt());

    auto jsonFields = json[JsonKeys::FIELDS].toArray();
    auto maxInRowCount = static_cast<int>(sqrt(static_cast<int>(this->size)));
    this->fields = std::vector<std::vector<MazeField *>>(maxInRowCount, std::vector<MazeField *>(maxInRowCount));
    for (auto field : jsonFields) {
        auto currentField = new MazeField(field.toObject());
        auto currentCoordinate = currentField->getCoordinate();
        this->fields[currentCoordinate.horizontal][currentCoordinate.vertical] = currentField;
    }
}

Maze::MazeFields Maze::randomlyGenerateFields() const {
    Log::print("Maze::randomlyGenerateFields()");
    return RandomMazeGenerator(this->size).generate();
}
