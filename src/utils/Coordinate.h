//
// Created by Kuba Jazdzyk on 8/17/19.
//

#ifndef MICROMOUSE_COORDINATE_H
#define MICROMOUSE_COORDINATE_H


#include "JsonKeys.h"
#include "src/protocols/Serializable.h"

struct Coordinate : Serializable {
    int row;
    int column;

    Coordinate() : row(0), column(0) {}
    Coordinate(int row, int column) : row(row), column(column) {}

    [[nodiscard]] Coordinate transpose() const {
        return Coordinate(this->column, this->row);
    }

    Coordinate operator-(const Coordinate& another) {
        Coordinate result;

        result.row = this->row - another.row;
        result.column = this->column - another.column;

        return result;
    }

    inline bool operator==(const Coordinate& another) {
        return (this->row == another.row) && (this->column == another.column);
    }

    // Serializable methods
    [[nodiscard]] QJsonObject serializeToJson() const override {
        QJsonObject json;

        json.insert(JsonKeys::VERTICAL, this->row);
        json.insert(JsonKeys::HORIZONTAL, this->column);

        return json;
    }

    void deserializeJson(const QJsonObject &json) override {
        this->row = json[JsonKeys::VERTICAL].toInt();
        this->column = json[JsonKeys::HORIZONTAL].toInt();
    }
};


#endif //MICROMOUSE_COORDINATE_H
