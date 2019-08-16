//
// Created by Kuba Jazdzyk on 8/15/19.
//

#ifndef MICROMOUSE_STARTCONTROLLER_H
#define MICROMOUSE_STARTCONTROLLER_H


#include <src/elements/RoundedPushButton.h>
#include <src/elements/RadioButtonGroupBox.h>
#include "BaseController.h"
#include "src/utils/Logging.h"

class StartController : public BaseController {
    Q_OBJECT

public:
    explicit StartController(QWidget *parent = nullptr);
    ~StartController();

private:
    RoundedPushButton *startSimulationButton;
    RadioButtonGroupBox *simulationModeBox;
    RadioButtonGroupBox *mazeSizeBox;
};


#endif //MICROMOUSE_STARTCONTROLLER_H
