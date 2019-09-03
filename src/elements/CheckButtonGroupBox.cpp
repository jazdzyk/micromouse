//
// Created by Kuba Jazdzyk on 8/16/19.
//

#include "CheckButtonGroupBox.h"

#include <utility>

CheckButtonGroupBox::CheckButtonGroupBox(const QString &title, CheckButtonGroupBox::ButtonTitles &buttonTitles,
                                         CheckButtonGroupBox::ActionCallback onButtonsClicked) : QGroupBox(title) {
    Log::print("CheckButtonGroupBox::CheckButtonGroupBox(&title: " + title.toStdString() +
               ", &buttonTitles, onButtonsClicked)");
    setUpUi(buttonTitles);
    setButtonsAction(std::move(onButtonsClicked));
}

CheckButtonGroupBox::~CheckButtonGroupBox() {
    Log::print("CheckButtonGroupBox::~CheckButtonGroupBox()");

}

bool CheckButtonGroupBox::isChosen(const int id) const {
    Log::print("CheckButtonGroupBox::isChosen(id: " + std::to_string(id) + ")");
    return this->buttonGroups[id].second.first->isChecked();
}

void CheckButtonGroupBox::setUpUi(CheckButtonGroupBox::ButtonTitles &buttonTitles) {
    Log::print("CheckButtonGroupBox::setUpUi(&buttonTitles)");
    auto *verticalLayout = new QVBoxLayout;

    auto id = 0;
    for (const auto& title : buttonTitles) {
        auto *checkBox = new QCheckBox("");
        checkBox->setChecked(false);

        auto *button = new RoundedPushButton(title, 5);
        button->setEnabled(false);

        auto *layout = new QHBoxLayout;
        layout->addWidget(checkBox, 1);
        layout->addWidget(button, 8);

        verticalLayout->addLayout(layout);
        this->buttonGroups.push_back({id++, {checkBox, button}});
    }

    setLayout(verticalLayout);
}

void CheckButtonGroupBox::setButtonsAction(CheckButtonGroupBox::ActionCallback onButtonsClicked) {
    Log::print("CheckButtonGroupBox::setButtonsAction(onButtonsClicked)");
    if (onButtonsClicked) {
        auto action = *onButtonsClicked;
        for (auto buttonGroup : this->buttonGroups) {
            connect(buttonGroup.second.first, static_cast<void(QCheckBox::*)(bool)>(&QCheckBox::clicked),
                    [buttonGroup](bool isClicked) {
                buttonGroup.second.second->setEnabled(isClicked);
            });
            connect(buttonGroup.second.second, static_cast<void(QPushButton::*)(bool)>(&QPushButton::clicked),
                    [buttonGroup, action](bool _) {
                action(buttonGroup.first);
            });
        }
    }
}
