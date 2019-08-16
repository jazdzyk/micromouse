//
// Created by Kuba Jazdzyk on 8/16/19.
//

#ifndef MICROMOUSE_RADIOBUTTONGROUPBOX_H
#define MICROMOUSE_RADIOBUTTONGROUPBOX_H


#include <QtWidgets/QGroupBox>
#include <QtWidgets/QRadioButton>
#include <functional>
#include <optional>
#include <QtWidgets/QButtonGroup>
#include "src/utils/Logging.h"
#include <src/utils/utils.h>
#include <QtWidgets/QHBoxLayout>

class RadioButtonGroupBox : public QGroupBox {
public:
    using ActionCallback = std::optional<std::function<void(int)>>;
    using ButtonNames = const std::vector<QString>;

    explicit RadioButtonGroupBox(const QString &title, ButtonNames &radioButtonNames,
            ActionCallback onRadioButtonClicked);
    ~RadioButtonGroupBox();

    void setRadioButton(int buttonId) const;

private:
    QButtonGroup *radioButtonGroup;

    void setUpUi(ButtonNames &radioButtonNames);
    void setRadioButtonsAction(ActionCallback onRadioButtonClicked);
};


#endif //MICROMOUSE_RADIOBUTTONGROUPBOX_H
