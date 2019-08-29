//
// Created by Kuba Jazdzyk on 8/17/19.
//

#include <QtWidgets/QFileDialog>
#include <utility>
#include <QtCore/QJsonDocument>
#include "MazeController.h"

using namespace Localizable;

MazeController::MazeController(SimulationSettings &simulationSettings,
                               std::optional<MazeControllerDelegate *> mazeControllerDelegate,
                               std::optional<ReturnToPreviousControllerDelegate *> returnDelegate, QWidget *parent)
        : BaseController(simulationSettings, parent),
          mazeControllerDelegate(std::move(mazeControllerDelegate)),
          returnDelegate(std::move(returnDelegate)) {
    Log::print("MazeController::MazeController(&simulationSettings, returnDelegate?, *parent)");
    setUpUi();
}

MazeController::~MazeController() {
    Log::print("MazeController::~MazeController()");
    utils::destruct(this->acceptButton);
    utils::destruct(this->saveButton);
    utils::destruct(this->loadButton);
    utils::destruct(this->mazeView);

    if (this->mazeControllerDelegate) {
        auto delegate = *this->mazeControllerDelegate;
        utils::destruct(delegate);
    }

    if (this->returnDelegate) {
        auto delegate = *this->returnDelegate;
        utils::destruct(delegate);
    }
}

void MazeController::setUpUi() {
    Log::print("MazeController::setUpUi()");
    addToParentLayout(prepareButtonsLayout(), 1);

    this->mazeView = new MazeView(this->simulationSettings.mazeSize, this->simulationSettings.simulationMode);

    this->mazeHolder = new MazeHolder;
    setMazeHolder(this->mazeView);
    addToParentLayout(this->mazeHolder, 8);
}

QVBoxLayout *MazeController::prepareButtonsLayout() {
    Log::print("MazeController::prepareButtonsLayout()");
    this->acceptButton = new RoundedPushButton(this->locale[PL::ACCEPT_MAZE_BUTTON_TITLE], 15);
    this->acceptButton->setAction([this]() {
        this->onAcceptButtonClicked();
    });

    this->saveButton = new RoundedPushButton(this->locale[PL::SAVE_MAZE_BUTTON_TITLE], 15);
    this->saveButton->setAction([this]() {
        this->onSaveButtonClicked();
    });

    this->loadButton = new RoundedPushButton(this->locale[PL::LOAD_MAZE_BUTTON_TITLE], 15);
    this->loadButton->setAction([this]() {
        this->onLoadButtonClicked();
    });

    auto quitButtonLayout = new QHBoxLayout;
    quitButtonLayout->addWidget(this->quitButton);
    quitButtonLayout->addWidget(this->returnButton);
    connect(this->returnButton, &QPushButton::clicked, [this]() {
        this->onReturnButtonClicked();
    });
    quitButtonLayout->addStretch(1);

    auto *buttonsLayout = new QVBoxLayout;
    addWidgetsToLayout({
                               this->acceptButton,
                               this->saveButton,
                               this->loadButton
                       }, buttonsLayout);
    buttonsLayout->addStretch(1);
    buttonsLayout->addLayout(quitButtonLayout);

    return buttonsLayout;
}

void MazeController::setMazeHolder(MazeView *mazeView) {
    Log::print("MazeController::setMazeHolder(*mazeView)");
    auto *_temp = new QWidget;
    _temp->setLayout(mazeView);

    this->mazeHolder->takeAt(0);
    this->mazeHolder->addWidget(_temp);
    this->mazeHolder->setCurrentIndex(0);
}

void MazeController::onAcceptButtonClicked() {
    Log::print("MazeController::onAcceptButtonClicked()");
    this->simulationSettings.maze.emplace(this->mazeView->getMaze());
    if (this->mazeControllerDelegate) {
        auto delegate = *this->mazeControllerDelegate;
        delegate->mazeControllerDidAcceptMaze(this, this->simulationSettings);
    }
}

void MazeController::onSaveButtonClicked() {
    Log::print("MazeController::onSaveButtonClicked()");
    auto fileName = QFileDialog::getSaveFileName(
            this,
            this->locale[PL::SAVE_FILE_DIALOG_TEXT],
            "maze.dat",
            this->locale[PL::MAZE_BINARY_FILE_DESCRIPTION]
    );

    if (fileName.isEmpty()) {
        return;
    }

    QFile saveFile(fileName);
    if (!saveFile.open(QIODevice::WriteOnly)) {
        qWarning("Couldn't open save file.");
        return;
    }

    QJsonDocument jsonDocument(this->mazeView->getMaze()->serializeToJson());
    saveFile.write(jsonDocument.toBinaryData());
    saveFile.close();
}

void MazeController::onLoadButtonClicked() {
    Log::print("MazeController::onLoadButtonClicked()");
    auto fileName = QFileDialog::getOpenFileName(
            this,
            this->locale[PL::OPEN_FILE_DIALOG_TEXT],
            "",
            this->locale[PL::MAZE_BINARY_FILE_DESCRIPTION]
    );

    if (fileName.isEmpty()) {
        return;
    }

    QFile loadFile(fileName);
    if (!loadFile.open(QIODevice::ReadOnly)) {
        qWarning("Couldn't open load file.");
        return;
    }

    auto loadedJsonDocument = QJsonDocument::fromBinaryData(loadFile.readAll());

    if (this->simulationSettings.maze) {
        auto maze = *this->simulationSettings.maze;
        delete maze;
    }

    this->simulationSettings.maze.emplace(new Maze(loadedJsonDocument.object()));
    delete this->mazeView;
    this->mazeView = new MazeView(*this->simulationSettings.maze, false);
    setMazeHolder(this->mazeView);
}

void MazeController::onReturnButtonClicked() {
    Log::print("MazeController::onReturnButtonClicked()");
    if (this->returnDelegate) {
        auto delegate = *this->returnDelegate;
        delegate->controllerWillReturn(this);
    }
}
