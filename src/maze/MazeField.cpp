//
// Created by Kuba Jazdzyk on 8/17/19.
//

#include "MazeField.h"

#include <utility>

MazeField::MazeField(const Coordinate &coordinate, MazeSize mazeSize) : coordinate(coordinate) {
    Log::print("MazeField::MazeField(&coordinate, mazeSize)");
    for (auto side : {WallSide::LEFT, WallSide::RIGHT, WallSide::TOP, WallSide::BOTTOM}) {
        this->walls.insert({side, MazeWall::createDefault(side, coordinate, mazeSize)});
    }
}

MazeField::MazeField(const Coordinate &coordinate, MazeField::Walls walls) : coordinate(coordinate), walls(std::move(walls)) {
    Log::print("MazeField::MazeField(&walls, &coordinate)");
}

MazeField::MazeField(const QJsonObject &json) {
    Log::print("MazeField::MazeField(&json)");
    deserializeJson(json);
}

MazeField::~MazeField() {
    Log::print("MazeField::~MazeField()");
    for (auto wall : this->walls) {
        utils::destruct(wall.second);
    }
}

Coordinate MazeField::getCoordinate() const {
    Log::print("MazeField::getCoordinate()");
    return this->coordinate;
}

MazeWall *MazeField::getWallAt(MazeField::WallSide side) const {
    Log::print("MazeField::getWallAt(side)");
    return this->walls.at(side);
}

bool MazeField::hasWallAt(MazeField::WallSide side) const {
    Log::print("MazeField::hasWallAt(side)");
    return this->walls.at(side)->isActive();
}

void MazeField::setWallAt(MazeField::WallSide side, bool shouldBeActive) const {
    Log::print("MazeField::setWallAt(side)");
    this->walls.at(side)->setActive(shouldBeActive);
}

void MazeField::toggleWallAt(MazeField::WallSide side) const {
    Log::print("MazeField::toggleWallAt(side)");
    this->walls.at(side)->toggleActive();
}

void MazeField::removeWall(const Coordinate &nextCoordinate) {
    Log::print("MazeField::removeWall(&nextCoordinate)");
    auto diffCoord = this->coordinate - nextCoordinate;

    WallSide wallSide;
    if (diffCoord.horizontal == 1) {
        wallSide = WallSide::TOP;
    } else if (diffCoord.horizontal == -1) {
        wallSide = WallSide::BOTTOM;
    } else if (diffCoord.vertical == 1) {
        wallSide = WallSide::LEFT;
    } else if (diffCoord.vertical == -1) {
        wallSide = WallSide::RIGHT;
    } else {
        return;
    }

    removeWall(wallSide);
}

std::optional<MazeField *> MazeField::getNeighbourAssociatedWithWallAt(MazeField::WallSide side) const {
    Log::print("MazeField::getNeighbourAssociatedWithWallAt(side)");
    return this->walls.at(side)->getNeighbour();
}

void MazeField::setNeighbourAssociatedWithWallAt(MazeField::WallSide side, MazeField *neighbour) const {
    Log::print("MazeField::setNeighbourAssociatedWithWallAt(side, *neighbour)");
    this->walls.at(side)->setNeighbour(neighbour);
}

bool MazeField::wasVisited() const {
    return this->_wasVisited;
}

void MazeField::setVisited(bool visited) {
    this->_wasVisited = visited;
}

QJsonObject MazeField::serializeToJson() const {
    Log::print("MazeField::serializeToJson()");
    QJsonObject wallJson;
    wallJson.insert(JsonKeys::LEFT, this->walls.at(WallSide::LEFT)->serializeToJson());
    wallJson.insert(JsonKeys::RIGHT, this->walls.at(WallSide::RIGHT)->serializeToJson());
    wallJson.insert(JsonKeys::TOP, this->walls.at(WallSide::TOP)->serializeToJson());
    wallJson.insert(JsonKeys::BOTTOM, this->walls.at(WallSide::BOTTOM)->serializeToJson());

    QJsonObject json;
    json.insert(JsonKeys::WALLS, wallJson);
    json.insert(JsonKeys::COORD, this->coordinate.serializeToJson());

    return json;
}

void MazeField::deserializeJson(const QJsonObject &json) {
    Log::print("MazeField::deserializeJson(&json)");
    auto wallJson = json[JsonKeys::WALLS].toObject();
    this->walls.insert({WallSide::LEFT, new MazeWall(wallJson[JsonKeys::LEFT].toObject())});
    this->walls.insert({WallSide::RIGHT, new MazeWall(wallJson[JsonKeys::RIGHT].toObject())});
    this->walls.insert({WallSide::TOP, new MazeWall(wallJson[JsonKeys::TOP].toObject())});
    this->walls.insert({WallSide::BOTTOM, new MazeWall(wallJson[JsonKeys::BOTTOM].toObject())});

    Coordinate coordinate;
    coordinate.deserializeJson(json[JsonKeys::COORD].toObject());
    this->coordinate = coordinate;
}

void MazeField::removeWall(MazeField::WallSide side) const {
    Log::print("MazeField::removeWall(side)");
    this->walls.at(side)->removeWall();
}
