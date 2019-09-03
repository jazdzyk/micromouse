//
// Created by Kuba Jazdzyk on 8/17/19.
//

#ifndef MICROMOUSE_RETURNTOPREVIOUSCONTROLLERDELEGATE_H
#define MICROMOUSE_RETURNTOPREVIOUSCONTROLLERDELEGATE_H


#include <src/controllers/BaseController.h>

/**
 * ReturnToPreviousControllerDelegate is a protocol delegating methods from controllers
 * which want to return to the previous controller.
 */
class ReturnToPreviousControllerDelegate {
public:
    /**
     * A method which delegates work when a controller will return.
     *
     * @param controller an instance of the returning controller
     */
    virtual void controllerWillReturn(BaseController *controller) = 0;

    /**
     * ReturnToPreviousControllerDelegate class destructor.
     */
    virtual ~ReturnToPreviousControllerDelegate() = default;
};


#endif //MICROMOUSE_RETURNTOPREVIOUSCONTROLLERDELEGATE_H
