//
// Created by Kuba Jazdzyk on 8/17/19.
//

#include <src/utils/JsonKeys.h>
#include "MazeWall.h"


MazeWall::MazeWall(bool active, bool blocked, WallSide side, NeighbourField neighbourField)
        : active(active), blocked(blocked), side(side), neighbour(std::move(neighbourField)) {
    Log::print("MazeWall::MazeWall(side, mazeField?)");
}

MazeWall::MazeWall(const QJsonObject &json) {
    Log::print("MazeWall::MazeWall(&json)");
    deserializeJson(json);
}

bool MazeWall::isActive() const {
    Log::print("MazeWall::isActive()");
    return this->active;
}

bool MazeWall::isBlocked() const {
    Log::print("MazeWall::isBlocked()");
    return this->blocked;
}

void MazeWall::setActive(bool active) {
    Log::print("MazeWall::setActive(active)");
    this->active = active;
}

void MazeWall::setBlocked(bool blocked) {
    Log::print("MazeWall::setBlocked(blocked)");
    if (!this->blocked) {
        this->blocked = blocked;
    }
}

void MazeWall::toggleActive() {
    Log::print("MazeWall::toggleActive()");
    setActive(!this->active);
}

MazeWall::WallSide MazeWall::getSide() const {
    Log::print("MazeWall::getSide()");
    return this->side;
}

std::optional<MazeWall *> MazeWall::getNeighbourWallAt(MazeWall::WallSide side) const {
    Log::print("MazeWall::getNeighbourWallAt(side)");
    if (this->neighbour) {
        auto field = *this->neighbour;
        return field->getWallAt(side);
    }
    return {};
}

void MazeWall::setSide(MazeWall::WallSide side) {
    Log::print("MazeWall::setSide(side)");
    this->side = side;
}

const MazeWall::NeighbourField &MazeWall::getNeighbour() const {
    Log::print("MazeWall::NeighbourField &MazeWall::getNeighbour()");
    return this->neighbour;
}

void MazeWall::setNeighbour(const MazeWall::NeighbourField &neighbour) {
    Log::print("MazeWall::setNeighbour(&neighbour)");
    if (!this->blocked) {
        this->neighbour = neighbour;
    }
}

void MazeWall::removeWall() {
    Log::print("MazeWall::removeWall()");
    if (!this->blocked) {
        this->active = false;
        if (this->neighbour) {
            auto field = *this->neighbour;
            field->setWallAt(getOppositeSide(), false);
        }
    }
}

MazeWall *MazeWall::createDefault(MazeWall::WallSide side, const Coordinate &coordinate, MazeSize mazeSize,
                                  bool shouldBeActive) {
    Log::print("MazeWall::createDefault(side, &coordinate, mazeSize)");
    auto shouldBeBlocked = (coordinate.vertical == 0 && side == WallSide::LEFT) ||
            (coordinate.vertical == (static_cast<int>(mazeSize) - 1) && side == WallSide::RIGHT) ||
            (coordinate.horizontal == 0 && side == WallSide::TOP) ||
            (coordinate.horizontal == (static_cast<int>(mazeSize) - 1) && side == WallSide::BOTTOM);
    // TODO: neighbour is not passed here
    return new MazeWall(!shouldBeActive ? shouldBeBlocked : true, shouldBeBlocked, side);
}

QJsonObject MazeWall::serializeToJson() const {
    Log::print("MazeWall::serializeToJson()");
    QJsonObject json;

    json.insert(JsonKeys::ACTIVE, this->active);
    json.insert(JsonKeys::BLOCKED, this->blocked);
    json.insert(JsonKeys::SIDE, static_cast<int>(this->side));
    if (this->neighbour) {
        auto neighbour = *this->neighbour;
        json.insert(JsonKeys::NEIGHBOUR, neighbour->serializeToJson());
    }

    return json;
}

void MazeWall::deserializeJson(const QJsonObject &json) {
    Log::print("MazeWall::deserializeJson(&json)");
    this->active = json[JsonKeys::ACTIVE].toBool();
    this->blocked = json[JsonKeys::BLOCKED].toBool();
    this->side = static_cast<WallSide>(json[JsonKeys::SIDE].toInt());
    if (json.find(JsonKeys::NEIGHBOUR) == json.end()) {
        this->neighbour.reset();
    } else {
        this->neighbour.emplace(new MazeField(json[JsonKeys::NEIGHBOUR].toObject()));
    }
}

MazeWall::WallSide MazeWall::getOppositeSide() const {
    Log::print("MazeWall::getOppositeSide()");
    switch (this->side) {
        case WallSide::LEFT:
            return WallSide::RIGHT;
        case WallSide::RIGHT:
            return WallSide::LEFT;
        case WallSide::TOP:
            return WallSide::BOTTOM;
        case WallSide::BOTTOM:
            return WallSide::TOP;
    }
}
