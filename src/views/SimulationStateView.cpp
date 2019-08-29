//
// Created by Kuba Jazdzyk on 8/29/19.
//

#include "SimulationStateView.h"

using namespace Localizable;

SimulationStateView::SimulationStateView() {
    Log::print("SimulationStateView::SimulationStateView()");
    setUpUi();
}

SimulationStateView::~SimulationStateView() {
    Log::print("SimulationStateView::~SimulationStateView()");
    utils::destruct(this->nameLabel);
    utils::destruct(this->timeValueLabel);
    utils::destruct(this->distanceValueLabel);
    utils::destruct(this->speedValueLabel);
    utils::destruct(arrowsView);
}

void SimulationStateView::setName(const QString &name) const {
    Log::print("void SimulationStateView::setName(&name: " + name.toStdString() + ")");
    this->nameLabel->setText(name);
}

void SimulationStateView::setTimeValue(double time) {
    Log::print("SimulationStateView::setTimeValue(time: " + std::to_string(time) + ")");
    this->timeValueLabel->setText(QString::number(time, 'g', 2) + this->locale[PL::RESULT_TIME_SUFFIX_LABEL]);
}

void SimulationStateView::setDistanceValue(int distance) {
    Log::print("SimulationStateView::setDistanceValue(distance: " + std::to_string(distance) + ")");
    this->distanceValueLabel->setText(QString::number(distance) + this->locale[PL::RESULT_DISTANCE_SUFFIX_LABEL]);
}

void SimulationStateView::setSpeedValue(double speed) {
    Log::print("SimulationStateView::setSpeedValue(speed: " + std::to_string(speed) + ")");
    this->speedValueLabel->setText(QString::number(speed, 'g', 2) +
                                   this->locale[PL::RESULT_SPEED_SUFFIX_LABEL]);
}

void SimulationStateView::activateArrow(Direction direction) const {
    Log::print("SimulationStateView::activateArrow(direction)");
    this->arrowsView->activateAt(direction);
}

void SimulationStateView::deactivateAllArrows() const {
    Log::print("SimulationStateView::deactivateAllArrows()");
    this->arrowsView->deactivateAll();
}

void SimulationStateView::setUpUi() {
    Log::print("SimulationStateView::setUpUi()");
    this->nameLabel = new QLabel();
    this->nameLabel->setStyleSheet("margin-top: 22px; margin-bottom: 10px; font-weight: bold;");

    auto leftLayout = new QVBoxLayout;
    leftLayout->addWidget(this->nameLabel);
    leftLayout->addLayout(prepareValuesLayout());
    leftLayout->addWidget(new QLabel());

    this->arrowsView = new ArrowsView;
    auto innerRightLayout = new QHBoxLayout;
    innerRightLayout->addStretch(1);
    innerRightLayout->addWidget(this->arrowsView, 3);
    innerRightLayout->addStretch(1);

    auto rightLayout = new QVBoxLayout;
    rightLayout->addStretch(1);
    rightLayout->addLayout(innerRightLayout, 5);
    rightLayout->addStretch(1);

    auto layout = new QHBoxLayout;
    layout->addStretch(1);
    layout->addLayout(leftLayout, 7);
    layout->addLayout(rightLayout, 9);

    setLayout(layout);

    setFrameStyle(QFrame::Box | QFrame::Raised);
    setStyleSheet("background-color: rgb(255, 255, 255);");
}

QHBoxLayout *SimulationStateView::prepareValuesLayout() {
    Log::print("SimulationStateView::prepareValuesLayout()");
    auto timeLabel = new QLabel(this->locale[PL::RESULT_TIME_LABEL]);
    auto distanceLabel = new QLabel(this->locale[PL::RESULT_DISTANCE_LABEL]);
    auto speedLabel = new QLabel(this->locale[PL::RESULT_SPEED_LABEL]);

    auto leftLayout = new QVBoxLayout;
    leftLayout->addWidget(timeLabel);
    leftLayout->addWidget(distanceLabel);
    leftLayout->addWidget(speedLabel);

    this->timeValueLabel = new QLabel(QString::number(0) + this->locale[PL::RESULT_TIME_SUFFIX_LABEL]);
    this->distanceValueLabel = new QLabel(QString::number(0) + this->locale[PL::RESULT_DISTANCE_SUFFIX_LABEL]);
    this->speedValueLabel = new QLabel(QString::number(0) + this->locale[PL::RESULT_SPEED_SUFFIX_LABEL]);

    auto rightLayout = new QVBoxLayout;
    auto widgets = {this->timeValueLabel, this->distanceValueLabel, this->speedValueLabel};
    std::for_each(widgets.begin(), widgets.end(), [rightLayout](auto widget) {
        rightLayout->addWidget(widget);
        rightLayout->setAlignment(widget, Qt::AlignRight);
    });

    auto layout = new QHBoxLayout;
    layout->addLayout(leftLayout);
    layout->addLayout(rightLayout);

    return layout;
}
