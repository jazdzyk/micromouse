//
// Created by Kuba Jazdzyk on 8/16/19.
//

#include "RadioButtonGroupBox.h"

RadioButtonGroupBox::RadioButtonGroupBox(const QString &title, RadioButtonGroupBox::ButtonNames &radioButtonNames,
                                         RadioButtonGroupBox::ActionCallback onRadioButtonClicked) : QGroupBox(title) {
    Log::print("RadioButtonGroupBox::RadioButtonGroupBox(&title: " + title.toStdString() + ", &radioButtonNames, "
                                                                                          "onRadioButtonClicked)");
    setUpUi(radioButtonNames);
    setRadioButtonsAction(onRadioButtonClicked);
}

RadioButtonGroupBox::~RadioButtonGroupBox() {
    Log::print("RadioButtonGroupBox::~RadioButtonGroupBox()");
    utils::destruct(this->radioButtonGroup);
}

void RadioButtonGroupBox::setRadioButton(int buttonId) const {
    Log::print("RadioButtonGroupBox::setRadioButton(buttonId: " + std::to_string(buttonId) + ")");
    this->radioButtonGroup->button(buttonId)->setChecked(true);
}

void RadioButtonGroupBox::setUpUi(RadioButtonGroupBox::ButtonNames &radioButtonNames) {
    Log::print("RadioButtonGroupBox::setUpUi(&radioButtonNames)");
    auto *layout = new QHBoxLayout;
    this->radioButtonGroup = new QButtonGroup;

    auto id = 0;
    for (auto name : radioButtonNames) {
        auto *radioButton = new QRadioButton(name);
        radioButton->setChecked(false);

        this->radioButtonGroup->addButton(radioButton, id++);
        layout->addWidget(radioButton);
    }

    this->radioButtonGroup->button(0)->setChecked(true);
    this->setLayout(layout);
}

void RadioButtonGroupBox::setRadioButtonsAction(RadioButtonGroupBox::ActionCallback onRadioButtonClicked) {
    Log::print("RadioButtonGroupBox::setRadioButtonsAction(onRadioButtonClicked)");
    if (onRadioButtonClicked) {
        auto action = *onRadioButtonClicked;
        connect(this->radioButtonGroup, static_cast<void(QButtonGroup::*)(int)>(&QButtonGroup::buttonClicked),
                [action](int id) {
            action(id);
        });
    }
}
