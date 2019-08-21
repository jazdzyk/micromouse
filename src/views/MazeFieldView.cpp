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
        : QLabel(), mazeField(mazeField), mazeSize(mazeSize), delegate(std::move(delegate)) {
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

void MazeFieldView::setBorder(MazeFieldView::WallSide side, bool border) const {
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
    auto rotatedPixmap = [pixmapHeight](const QString& url, int rotation) {
        auto pixmap = QPixmap(url);

        QTransform transform;
        transform.rotate(rotation);
        pixmap = pixmap.transformed(transform);
        pixmap = pixmap.scaledToHeight(pixmapHeight);

        return pixmap;
    };

    if (robot) {
        setPixmap(rotatedPixmap(":/images/robot-icon.png", this->currentRobotRotation));
        setAlignment(Qt::AlignCenter);
    } else {
        clear();
    }
}

void MazeFieldView::resetCurrentRobotRotationWith(int angle) {
    Log::print("MazeFieldView::resetCurrentRobotRotationWith(angle: " + std::to_string(angle) + ")");

}

int MazeFieldView::getCurrentRobotRotationAngle() const {
    Log::print("MazeFieldView::getCurrentRobotRotationAngle()");
    return 0;
}

void MazeFieldView::clicked(MazeFieldView::WallSide side, const Coordinate &coordinate) {
    Log::print("MazeFieldView::clicked(side, &coordinate)");

}

void MazeFieldView::updateBorders() const {
    Log::print("MazeFieldView::updateBorders()");

}

bool MazeFieldView::isEdgeSize(MazeFieldView::WallSide side) const {
    Log::print("MazeFieldView::isEdgeSize(side)");
    return false;
}

int MazeFieldView::calculateMazeSideLength() const {
    Log::print("RandomMazeGenerator::calculateMazeSideLength()");
    return static_cast<int>(sqrt(static_cast<int>(this->mazeSize)));
}

void MazeFieldView::paintFieldIfNeeded() const {
    Log::print("MazeFieldView::paintFieldIfNeeded()");

}

void MazeFieldView::mousePressEvent(QMouseEvent *event) {
    Log::print("MazeFieldView::mousePressEvent(*event)");
    QLabel::mousePressEvent(event);
}
