//
// Created by Kuba Jazdzyk on 8/17/19.
//

#ifndef MICROMOUSE_SERIALIZABLE_H
#define MICROMOUSE_SERIALIZABLE_H


#include <QtCore/QJsonObject>

class Serializable {
public:
    [[nodiscard]] virtual QJsonObject serializeToJson() const = 0;
    virtual void deserializeJson(const QJsonObject& json) = 0;
    virtual ~Serializable() = default;
};


#endif //MICROMOUSE_SERIALIZABLE_H
