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

/**
 * The RadioButtonGroupBox class inherits from QGroupBox and extends its functionalities.
 * It contains multiple radio buttons.
 */
class RadioButtonGroupBox : public QGroupBox {
public:
    using ActionCallback = std::optional<std::function<void(int)>>;
    using ButtonNames = const std::vector<QString>;

    /**
     * RadioButtonGroupBox class constructor.
     *
     * @param title a title for a box
     * @param radioButtonNames a vector of names for radio buttons
     * @param onRadioButtonClicked a callback for radio buttons
     */
    explicit RadioButtonGroupBox(const QString &title, ButtonNames &radioButtonNames,
                                 ActionCallback onRadioButtonClicked);

    /**
     * RadioButtonGroupBox class destructor.
     */
    ~RadioButtonGroupBox() override;

    /**
     * A public method which enables setting checked a radio button identified with a given id.
     *
     * @param buttonId an id of a radio button
     */
    void setRadioButton(int buttonId) const;

private:
    QButtonGroup *radioButtonGroup;

    /**
     * A private method which enables a configuration of box's UI.
     *
     * @param radioButtonNames a vector of names for radio buttons
     */
    void setUpUi(ButtonNames &radioButtonNames);

    /**
     * A private method which enables setting the callback action for radio buttons.
     *
     * @param onRadioButtonClicked a callback action for radio buttons
     */
    void setRadioButtonsAction(ActionCallback onRadioButtonClicked);
};


#endif //MICROMOUSE_RADIOBUTTONGROUPBOX_H
