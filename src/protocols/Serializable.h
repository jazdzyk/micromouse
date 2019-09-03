//
// Created by Kuba Jazdzyk on 8/17/19.
//

#ifndef MICROMOUSE_SERIALIZABLE_H
#define MICROMOUSE_SERIALIZABLE_H


#include <QtCore/QJsonObject>

/**
 * Serializable is a protocol which defines methods that class must implement
 * if has need for being able to (de)serialize JSON data.
 */
class Serializable {
public:
    /**
     * A method which enables JSON serialization.
     *
     * @return a serialized JSON object
     */
    [[nodiscard]] virtual QJsonObject serializeToJson() const = 0;

    /**
     * A method which enables JSON deserialization.
     *
     * @param json a serialized json object
     */
    virtual void deserializeJson(const QJsonObject &json) = 0;

    /**
     * Serializable class destructor.
     */
    virtual ~Serializable() = default;
};


#endif //MICROMOUSE_SERIALIZABLE_H
