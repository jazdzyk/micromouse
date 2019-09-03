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

/**
 * The CheckButtonGroupBox class inherits from QGroupBox and extends its functionalities.
 * It contains pairs of a checkbox and a button. When a checkbox is checked, the button is enabled.
 */
class CheckButtonGroupBox : public QGroupBox {
public:
    using ActionCallback = std::optional<std::function<void(int)>>;
    using ButtonTitles = const std::vector<QString>;

    /**
     * CheckButtonGroupBox class constructor.
     *
     * @param title a title for a box
     * @param buttonTitles a vector of titles for buttons
     * @param onButtonsClicked a callback for buttons
     */
    explicit CheckButtonGroupBox(const QString &title, ButtonTitles &buttonTitles, ActionCallback onButtonsClicked);

    /**
     * CheckButtonGroupBox class destructor.
     */
    ~CheckButtonGroupBox() override;

    /**
     * A public method which informs whether a pair with a given id is currently chosen.
     *
     * @param id an id of a pair checkbox-button
     * @return an appropriate boolean flag
     */
    [[nodiscard]] bool isChosen(int id) const;

private:
    using ButtonGroup = std::pair<int, std::pair<QCheckBox*, RoundedPushButton*>>;

    std::vector<ButtonGroup> buttonGroups;

    /**
     * A private method which enables a configuration of box's UI.
     *
     * @param buttonTitles a vector of titles for buttons
     */
    void setUpUi(ButtonTitles &buttonTitles);

    /**
     * A private method which enables setting the callback action for buttons.
     *
     * @param onButtonsClicked a callback for buttons
     */
    void setButtonsAction(ActionCallback onButtonsClicked);
};


#endif //MICROMOUSE_CHECKBUTTONGROUPBOX_H
