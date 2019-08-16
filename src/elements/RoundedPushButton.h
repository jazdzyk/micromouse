//
// Created by Kuba Jazdzyk on 8/16/19.
//

#ifndef MICROMOUSE_ROUNDEDPUSHBUTTON_H
#define MICROMOUSE_ROUNDEDPUSHBUTTON_H


#include <QtWidgets/QPushButton>
#include <functional>

class RoundedPushButton : public QPushButton {
public:
    using ActionCallback = std::function<void()>;

    explicit RoundedPushButton(const QString &title = "", int padding = 0);

    void setAction(ActionCallback onButtonClicked);

private:
    void setUpStyle(int padding);
};


#endif //MICROMOUSE_ROUNDEDPUSHBUTTON_H
