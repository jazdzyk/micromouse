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

}

void ArrowsView::deactivateAll() const {
    Log::print("ArrowsView::deactivateAll()");

}

void ArrowsView::setUpUi() {
    Log::print("ArrowsView::setUpUi()");

}

QString ArrowsView::prepareUrl(Direction direction, bool activated) const {
    Log::print("ArrowsView::prepareUrl(direction, activated)");
    return QString();
}
