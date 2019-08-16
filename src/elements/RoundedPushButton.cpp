//
// Created by Kuba Jazdzyk on 8/16/19.
//

#include "RoundedPushButton.h"

RoundedPushButton::RoundedPushButton(const QString &title, int padding) : QPushButton(title) {
    Log::print("RoundedPushButton::RoundedPushButton(&title: "
        + title.toStdString() + ", padding: " + std::to_string(padding) + ")");
    setUpStyle(padding);
}

void RoundedPushButton::setAction(RoundedPushButton::ActionCallback onButtonClicked) {
    Log::print("RoundedPushButton::setAction(onButtonClicked)");
    connect(this, static_cast<void(QPushButton::*)(bool)>(&QPushButton::clicked), [=](bool _) {
        onButtonClicked();
    });
}

void RoundedPushButton::setUpStyle(int padding) {
    Log::print("RoundedPushButton::setUpStyle(padding: " + std::to_string(padding) + ")");
    setStyleSheet(
        "QPushButton {\n"
        "\tfont-weight: bold;\n"
        "\tbackground-color: rgb(239, 239, 239);\n"
        "\tborder: 1px solid rgb(215, 215, 215);\n"
        "\tborder-radius: 10px;\n"
        "\tpadding: " + QString::number(padding) + "px 10px " + QString::number(padding) + "px 10px;\n"
        "}\n"
        "\n"
        "QPushButton:pressed {\n"
        "\tbackground-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #ffffff, stop: 1 #d7d7d7);\n"
        "}\n"
        "\n"
        "QPushButton:flat {\n"
        "\tbackground-color: rgb(255, 255, 255);\n"
        "}"
    );
}
