//
// Created by Kuba Jazdzyk on 8/17/19.
//

#ifndef MICROMOUSE_COORDINATE_H
#define MICROMOUSE_COORDINATE_H


#include "JsonKeys.h"
#include "src/protocols/Serializable.h"

struct Coordinate : Serializable {
    int vertical;
    int horizontal;

    Coordinate() : vertical(0), horizontal(0) {}
    Coordinate(int vertical, int horizontal) : vertical(vertical), horizontal(horizontal) {}

    Coordinate operator-(const Coordinate& another) {
        Coordinate result;

        result.vertical = this->vertical - another.vertical;
        result.horizontal = this->horizontal - another.horizontal;

        return result;
    }

    // Serializable methods
    [[nodiscard]] QJsonObject serializeToJson() const override {
        QJsonObject json;

        json.insert(JsonKeys::VERTICAL, this->vertical);
        json.insert(JsonKeys::HORIZONTAL, this->horizontal);

        return json;
    }

    void deserializeJson(const QJsonObject &json) override {
        this->vertical = json[JsonKeys::VERTICAL].toInt();
        this->horizontal = json[JsonKeys::HORIZONTAL].toInt();
    }
};


#endif //MICROMOUSE_COORDINATE_H
