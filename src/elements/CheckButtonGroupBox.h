//
// Created by Kuba Jazdzyk on 8/16/19.
//

#ifndef MICROMOUSE_CHECKBUTTONGROUPBOX_H
#define MICROMOUSE_CHECKBUTTONGROUPBOX_H


#include <QtWidgets/QGroupBox>
#include <functional>
#include <optional>
#include <QtWidgets/QCheckBox>
#include <src/elements/RoundedPushButton.h>
#include <QtWidgets/QVBoxLayout>

class CheckButtonGroupBox : public QGroupBox {
public:
    using ActionCallback = std::optional<std::function<void(int)>>;
    using ButtonTitles = const std::vector<QString>;

    explicit CheckButtonGroupBox(const QString &title, ButtonTitles &buttonTitles, ActionCallback onButtonsClicked);
    ~CheckButtonGroupBox();

    bool isChosen(const int id) const;

private:
    using ButtonGroup = std::pair<int, std::pair<QCheckBox*, RoundedPushButton*>>;

    std::vector<ButtonGroup> buttonGroups;

    void setUpUi(ButtonTitles &buttonTitles);
    void setButtonsAction(ActionCallback onButtonsClicked);
};


#endif //MICROMOUSE_CHECKBUTTONGROUPBOX_H
