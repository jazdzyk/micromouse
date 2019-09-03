//
// Created by Kuba Jazdzyk on 8/17/19.
//

#ifndef MICROMOUSE_RETURNTOPREVIOUSCONTROLLERDELEGATE_H
#define MICROMOUSE_RETURNTOPREVIOUSCONTROLLERDELEGATE_H


#include <src/controllers/BaseController.h>

class ReturnToPreviousControllerDelegate {
public:
    virtual void controllerWillReturn(BaseController *controller) = 0;
    virtual ~ReturnToPreviousControllerDelegate() = default;
};


#endif //MICROMOUSE_RETURNTOPREVIOUSCONTROLLERDELEGATE_H
