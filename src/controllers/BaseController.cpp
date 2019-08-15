//
// Created by Kuba Jazdzyk on 8/15/19.
//

#include "BaseController.h"

BaseController::BaseController(QWidget *parent) {

}

BaseController::BaseController(SimulationSettings &simulationSettings, QWidget *parent) {

}

BaseController::~BaseController() {

}

void BaseController::setSimulationSettings(SimulationSettings &simulationSettings) {

}

void BaseController::addToParentLayout(QLayout *layout, int stretch) {

}

void BaseController::addToParentLayout(QWidget *widget, int stretch) {

}

void BaseController::addWidgetsToLayout(QWidget &widgets, QLayout *layout) {

}

void BaseController::setUpUi() {

}

void BaseController::createQuitButton() {

}

void BaseController::createReturnButton() {

}

QPushButton *BaseController::createButton(const QString &iconUrl) {
    return nullptr;
}
