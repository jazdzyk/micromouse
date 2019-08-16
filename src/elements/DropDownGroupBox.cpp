//
// Created by Kuba Jazdzyk on 8/16/19.
//

#include "DropDownGroupBox.h"

#include <utility>

DropDownGroupBox::DropDownGroupBox(const QString &title, DropDownGroupBox::Texts &labels,
                                   DropDownGroupBox::Texts &dropDownOptions,
                                   DropDownGroupBox::ActionCallback onDropDownChanged) : QGroupBox(title) {
    Log::print("DropDownGroupBox::DropDownGroupBox(&title: " + title.toStdString() + ", &labels, &dropDownOptions,"
                                                                                     " onDropDownChanged)");
    setUpUi(labels, dropDownOptions);
    setDropDownAction(std::move(onDropDownChanged));
}

DropDownGroupBox::~DropDownGroupBox() {
    Log::print("DropDownGroupBox::~DropDownGroupBox()");

}

void DropDownGroupBox::setDropDownOption(int id, int option) {
    Log::print("DropDownGroupBox::setDropDownOption(id: " + std::to_string(id) + ", option: "
               + std::to_string(option) + ")");
    this->dropDowns[id].second->setCurrentIndex(option);
}

void DropDownGroupBox::setDropDownVisible(int id, bool visible) {
    Log::print("DropDownGroupBox::setDropDownVisible(id: " + std::to_string(id) + ", visible: "
               + (visible ? "true" : "false") + ")");
    for (auto i = 0; i < this->horizontalLayouts[id]->count(); ++i) {
        auto *widget = this->horizontalLayouts[id]->itemAt(i)->widget();
        if (widget != nullptr) {
            widget->setVisible(visible);
        }
    }

    if (!visible) {
        setDropDownOption(id, 0);
    }
}

void DropDownGroupBox::setUpUi(DropDownGroupBox::Texts &labels, DropDownGroupBox::Texts &dropDownOptions) {
    Log::print("DropDownGroupBox::setUpUi(&labels, &dropDownOptions)");
    this->boxLayout = new QVBoxLayout;
    addDropDowns(labels, dropDownOptions, 0);
    setLayout(this->boxLayout);
}

void DropDownGroupBox::setDropDownAction(DropDownGroupBox::ActionCallback onDropDownChanged) {
    Log::print("DropDownGroupBox::setDropDownAction(onDropDownChanged)");
    if (onDropDownChanged) {
        auto action = *onDropDownChanged;
        for (auto dropDown : this->dropDowns) {
            connect(dropDown.second, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
                    [dropDown, action](int id) {
                        action(dropDown.first, id);
                    });
        }
    }
}

void DropDownGroupBox::addDropDowns(DropDownGroupBox::Texts &labels, DropDownGroupBox::Texts &dropDownOptions,
                                    int initialId) {
    Log::print("DropDownGroupBox::addDropDowns(&labels, &dropDownOptions, initialId: "
               + std::to_string(initialId) + ")");
    auto id = initialId;
    for (const auto& labelText : labels) {
        auto *label = new QLabel(labelText);
        auto *dropDown = prepareDropDown(dropDownOptions);

        auto *layout = new QHBoxLayout;
        layout->addWidget(label, 1);
        layout->addWidget(dropDown, 3);

        this->boxLayout->addLayout(layout);
        this->dropDowns.emplace_back(id++, dropDown);
        this->horizontalLayouts.push_back(layout);
    }
}

QComboBox *DropDownGroupBox::prepareDropDown(DropDownGroupBox::Texts &dropDownOptions) {
    Log::print("DropDownGroupBox::prepareDropDown(&dropDownOptions)");
    auto *dropDown = new QComboBox;

    auto dropDownList = QStringList();
    for (const auto& option : dropDownOptions) {
        dropDownList << option;
    }

    dropDown->addItems(dropDownList);

    return dropDown;
}
