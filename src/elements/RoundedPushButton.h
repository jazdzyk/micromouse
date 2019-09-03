//
// Created by Kuba Jazdzyk on 8/16/19.
//

#ifndef MICROMOUSE_ROUNDEDPUSHBUTTON_H
#define MICROMOUSE_ROUNDEDPUSHBUTTON_H


#include <QtWidgets/QPushButton>
#include <functional>
#include <optional>
#include "src/utils/Logging.h"

/**
 * The RoundedPushButton class inherits from QPushButton and customizes its style.
 */
class RoundedPushButton : public QPushButton {
public:
    using ActionCallback = std::optional<std::function<void()>>;

    /**
     * RoundedPushButton class constructor.
     *
     * @param title a title for a button
     * @param padding a padding size value
     */
    explicit RoundedPushButton(const QString &title = "", int padding = 0);

    /**
     * A public method which enables setting the callback action for a button.
     *
     * @param onButtonClicked a callback for a button
     */
    void setAction(ActionCallback onButtonClicked);

private:
    /**
     * A private method which customizes button's style.
     *
     * @param padding a padding size value
     */
    void setUpStyle(int padding);
};


#endif //MICROMOUSE_ROUNDEDPUSHBUTTON_H
