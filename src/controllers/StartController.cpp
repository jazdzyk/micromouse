//
// Created by Kuba Jazdzyk on 8/15/19.
//

#include "StartController.h"

StartController::StartController(QWidget *parent) : BaseController(parent) {
    Log::print("StartController::StartController(*parent)");
}

StartController::~StartController() {
    Log::print("StartController::~StartController()");
}
