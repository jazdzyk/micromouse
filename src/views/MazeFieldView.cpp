//
// Created by Kuba Jazdzyk on 8/21/19.
//

#include "MazeFieldView.h"

#include <utility>

MazeFieldView::MazeFieldView(const Coordinate &coordinate, MazeSize mazeSize,
                             std::optional<MazeFieldViewDelegate *> delegate, MazeFieldType mazeFieldType)
        : MazeFieldView(new MazeField(coordinate, mazeSize), mazeSize, std::move(delegate)) {
    Log::print("MazeFieldView::MazeFieldView(&coordinate, mazeSize, delegate?, mazeFieldType)");
    this->fieldType = mazeFieldType;
}

MazeFieldView::MazeFieldView(MazeField *mazeField, MazeSize mazeSize, std::optional<MazeFieldViewDelegate *> delegate)
        : QLabel(/*"(" + QString::number(mazeField->getCoordinate().row) + ", " + QString::number(mazeField->getCoordinate().column) + ")"*/), mazeField(mazeField), mazeSize(mazeSize), delegate(std::move(delegate)), fieldType(::PLAIN), currentRobotRotation(0) {
    Log::print("MazeFieldView::MazeFieldView(*mazeField, mazeSize, delegate?)");
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    setEnabled(true);
}

MazeFieldView::~MazeFieldView() {
    Log::print("MazeFieldView::~MazeFieldView()");
    utils::destruct(this->mazeField);
}

void MazeFieldView::setEnabled(bool enabled) {
    Log::print("MazeFieldView::setEnabled(enabled)");
    this->isEnabled = enabled;
    updateBorders();
}

void MazeFieldView::setBorder(MazeFieldView::WallSide side, bool border) {
    Log::print("MazeFieldView::setBorder(side, border)");
    this->mazeField->setWallAt(side, border);
    updateBorders();
}

void MazeFieldView::setFieldType(MazeFieldType type) {
    Log::print("MazeFieldView::setFieldType(type)");
    this->fieldType = type;
    paintFieldIfNeeded();
}

MazeField *MazeFieldView::getMazeField() const {
    Log::print("MazeFieldView::getMazeField()");
    return this->mazeField;
}

Coordinate MazeFieldView::getCoordinate() const {
    Log::print("MazeFieldView::getCoordinate()");
    return this->mazeField->getCoordinate();
}

void MazeFieldView::showRobot(bool robot, int rotation) {
    Log::print("MazeFieldView::showRobot(robot, rotation: " + std::to_string(rotation) + ")");
    this->currentRobotRotation += rotation;

    auto pixmapHeight = QApplication::desktop()->screenGeometry().height() / (calculateMazeSideLength() + 5);
    auto rotatedPixmap = [pixmapHeight](const QString &url, int rotation) {
        auto pixmap = QPixmap(url);

        QTransform transform;
        transform.rotate(rotation);
        pixmap = pixmap.transformed(transform);
        pixmap = pixmap.scaledToHeight(pixmapHeight);

        return pixmap;
    };

    if (robot) {
        setPixmap(rotatedPixmap(":/robot-icon", this->currentRobotRotation));
        setAlignment(Qt::AlignCenter);
    } else {
        clear();
    }
}

void MazeFieldView::resetCurrentRobotRotationWith(int angle) {
    Log::print("MazeFieldView::resetCurrentRobotRotationWith(angle: " + std::to_string(angle) + ")");
    this->currentRobotRotation = angle;
}

int MazeFieldView::getCurrentRobotRotationAngle() const {
    Log::print("MazeFieldView::getCurrentRobotRotationAngle()");
    return this->currentRobotRotation;
}

void MazeFieldView::updateBorders() {
    Log::print("MazeFieldView::updateBorders()");
    auto borderWidth = [this](int coordinate, bool isFront) {
        return coordinate == (isFront ? 0 : (calculateMazeSideLength() - 1)) ? 4 : 2;
    };

    auto colorHex = [this](bool hasBorder, WallSide side) {
        return (hasBorder || isEdgeSide(side)) ? "0, 0, 0" : (this->isEnabled ? "215, 215, 215" : "239, 239, 239");
    };

    auto styleSheet = QString("border-left:  %2px solid rgb(%1);")
                              .arg(colorHex(this->mazeField->hasWallAt(WallSide::LEFT), WallSide::LEFT))
                              .arg(borderWidth(this->getCoordinate().column, true)) +
                      QString("border-right: %2px solid rgb(%1);")
                              .arg(colorHex(this->mazeField->hasWallAt(WallSide::RIGHT), WallSide::RIGHT))
                              .arg(borderWidth(this->getCoordinate().column, false)) +
                      QString("border-top: %2px solid rgb(%1);")
                              .arg(colorHex(this->mazeField->hasWallAt(WallSide::TOP), WallSide::TOP))
                              .arg(borderWidth(this->getCoordinate().row, true)) +
                      QString("border-bottom: %2px solid rgb(%1);")
                              .arg(colorHex(this->mazeField->hasWallAt(WallSide::BOTTOM), WallSide::BOTTOM))
                              .arg(borderWidth(this->getCoordinate().row, false));

    setStyleSheet(styleSheet);
    paintFieldIfNeeded();
}

bool MazeFieldView::isEdgeSide(MazeFieldView::WallSide side) const {
    Log::print("MazeFieldView::isEdgeSide(side)");
    switch (side) {
        case Direction::LEFT:
            return this->getCoordinate().column == 0;
        case Direction::RIGHT:
            return this->getCoordinate().column == (calculateMazeSideLength() - 1);
        case Direction::TOP:
            return this->getCoordinate().row == 0;
        case Direction::BOTTOM:
            return this->getCoordinate().row == (calculateMazeSideLength() - 1);
    }
}

int MazeFieldView::calculateMazeSideLength() const {
    Log::print("MazeFieldView::calculateMazeSideLength()");
    return static_cast<int>(sqrt(static_cast<int>(this->mazeSize)));
}

void MazeFieldView::paintFieldIfNeeded() {
    Log::print("MazeFieldView::paintFieldIfNeeded()");
    auto backgroundColor = [this]() {
        switch (this->fieldType) {
            case ROBOT1_START:
                return "green";
            case ROBOT2_START:
                return "blue";
            case END:
                return "red";
            case PLAIN:
                return "";
        }
    };

    setStyleSheet(this->styleSheet() + QString("background-color: %1;").arg(backgroundColor()));
}

void MazeFieldView::mousePressEvent(QMouseEvent *event) {
    Log::print("MazeFieldView::mousePressEvent(*event)");
    if (!this->isEnabled) {
        return;
    }

    auto FACTOR = 0.1;
    auto clickedPoint = event->pos();
    std::vector<MazeFieldWallUpdateInfo> info;

    if (clickedPoint.x() < FACTOR * this->width() && !isEdgeSide(WallSide::LEFT)) {
        this->mazeField->toggleWallAt(WallSide::LEFT);
        info.emplace_back(this->getCoordinate(), WallSide::LEFT,
                                      this->mazeField->hasWallAt(WallSide::LEFT));
    } else if (clickedPoint.x() > (1 - FACTOR) * this->width() && !isEdgeSide(WallSide::RIGHT)) {
        this->mazeField->toggleWallAt(WallSide::RIGHT);
        info.emplace_back(this->getCoordinate(), WallSide::RIGHT,
                                      this->mazeField->hasWallAt(WallSide::RIGHT));
    }

    if (clickedPoint.y() < FACTOR * this->height() && !isEdgeSide(WallSide::TOP)) {
        this->mazeField->toggleWallAt(WallSide::TOP);
        info.emplace_back(this->getCoordinate(), WallSide::TOP,
                                      this->mazeField->hasWallAt(WallSide::TOP));
    } else if (clickedPoint.y() > (1 - FACTOR) * this->height() && !isEdgeSide(WallSide::BOTTOM)) {
        this->mazeField->toggleWallAt(WallSide::BOTTOM);
        info.emplace_back(this->getCoordinate(), WallSide::BOTTOM,
                                      this->mazeField->hasWallAt(WallSide::BOTTOM));
    }

    updateBorders();
    if (this->delegate) {
        auto delegate = *this->delegate;
        delegate->mazeFieldWallDidSet(info);
    }
}
