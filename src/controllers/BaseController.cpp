//
// Created by Kuba Jazdzyk on 8/15/19.
//

#include "BaseController.h"

BaseController::BaseController(QWidget *parent) : QMainWindow(parent) {
    Log::print("BaseController::BaseController(*parent)");
    setUpUi();
    createQuitButton();
    createReturnButton();
}

BaseController::BaseController(SimulationSettings &simulationSettings, QWidget *parent) : BaseController(parent) {
    Log::print("BaseController::BaseController(&simulationSettings, *parent)");
    this->simulationSettings = simulationSettings;
}

BaseController::~BaseController() {
    Log::print("BaseController::~BaseController()");
    utils::destruct(this->quitButton);
    utils::destruct(this->returnButton);
}

void BaseController::setSimulationSettings(SimulationSettings &simulationSettings) {
    Log::print("BaseController::setSimulationSettings(&simulationSettings)");
    this->simulationSettings = simulationSettings;
}

void BaseController::addToParentLayout(QLayout *layout, int stretch) {
    Log::print("BaseController::addToParentLayout(*layout, stretch)");
    this->parentLayout->addLayout(layout, stretch);
}

void BaseController::addToParentLayout(QWidget *widget, int stretch) {
    Log::print("BaseController::addToParentLayout(*widget, stretch)");
    this->parentLayout->addWidget(widget, stretch);
}

void BaseController::addWidgetsToLayout(QWidgets &widgets, QLayout *layout) {
    Log::print("BaseController::addWidgetsToLayout(&widgets, *layout)");
    std::for_each(widgets.begin(), widgets.end(), [layout](auto *widget) {
        layout->addWidget(widget);
    });
}

void BaseController::setUpUi() {
    Log::print("BaseController::setUpUi()");
    setCentralWidget(new QWidget(this));

    this->parentLayout = new QHBoxLayout;
    centralWidget()->setLayout(this->parentLayout);
}

void BaseController::createQuitButton() {
    Log::print("BaseController::createQuitButton()");
    this->quitButton = createButton(QString(":/quit-mark"));
    connect(this->quitButton, SIGNAL(clicked()), QApplication::instance(), SLOT(quit()));
}

void BaseController::createReturnButton() {
    Log::print("BaseController::createReturnButton()");
    this->returnButton = createButton(QString(":/return-mark"));
}

QPushButton *BaseController::createButton(const QString &iconUrl) {
    Log::print("BaseController::createButton(&iconUrl)");
    auto *button = new QPushButton;
    button->setIcon(QIcon(iconUrl));
    button->setIconSize(QSize(50, 50));

    return button;
}
