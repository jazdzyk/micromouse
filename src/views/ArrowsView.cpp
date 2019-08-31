//
// Created by Kuba Jazdzyk on 8/29/19.
//

#include "ArrowsView.h"

ArrowsView::ArrowsView(QWidget *parent) : QWidget(parent) {
    Log::print("ArrowsView::ArrowsView(*parent)");
    setUpUi();
}

ArrowsView::~ArrowsView() {
    Log::print("ArrowsView::~ArrowsView()");
    utils::destruct(this->leftArrow);
    utils::destruct(this->topArrow);
    utils::destruct(this->rightArrow);
}

void ArrowsView::activateAt(Direction direction) const {
    Log::print("ArrowsView::activateAt(direction)");
    this->leftArrow->updatePixmap(prepareUrl(Direction::LEFT, direction == Direction::LEFT));
    this->rightArrow->updatePixmap(prepareUrl(Direction::RIGHT, direction == Direction::RIGHT));
    this->topArrow->updatePixmap(prepareUrl(Direction::TOP, direction == Direction::TOP));
}

void ArrowsView::deactivateAll() const {
    Log::print("ArrowsView::deactivateAll()");
    this->leftArrow->updatePixmap(prepareUrl(Direction::LEFT, false));
    this->rightArrow->updatePixmap(prepareUrl(Direction::RIGHT, false));
    this->topArrow->updatePixmap(prepareUrl(Direction::TOP, false));
}

void ArrowsView::setUpUi() {
    Log::print("ArrowsView::setUpUi()");
    this->leftArrow = new ImageLabel(":/images/left-arrow-inactive.png", ARROW_SIZE);
    this->leftArrow->setParent(this);
    this->leftArrow->move(QPoint(0, 35));

    this->topArrow = new ImageLabel(":/images/up-arrow-inactive.png", ARROW_SIZE);
    this->topArrow->setParent(this);
    this->topArrow->move(QPoint(35, 0));

    this->rightArrow = new ImageLabel(":/images/right-arrow-inactive.png", ARROW_SIZE);
    this->rightArrow->setParent(this);
    this->rightArrow->move(QPoint(71, 35));
}

QString ArrowsView::prepareUrl(Direction direction, bool activated) const {
    Log::print("ArrowsView::prepareUrl(direction, activated)");
    QString urlPrefix = ":/images/";
    QString urlSuffix = activated ? ".png" : "-inactive.png";

    switch (direction) {
        case Direction::LEFT:
            urlPrefix += "left-arrow";
            break;
        case Direction::RIGHT:
            urlPrefix += "right-arrow";
            break;
        case Direction::TOP:
            urlPrefix += "up-arrow";
            break;
        case Direction::BOTTOM:
            break;
    }

    return urlPrefix + urlSuffix;
}
