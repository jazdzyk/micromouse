//
// Created by Kuba Jazdzyk on 8/17/19.
//

#ifndef MICROMOUSE_MAZECONTROLLER_H
#define MICROMOUSE_MAZECONTROLLER_H


#include <src/utils/SimulationSettings.h>
#include <src/protocols/delegates/ReturnToPreviousControllerDelegate.h>
#include <optional>
#include <src/protocols/delegates/MazeControllerDelegate.h>
#include <src/elements/RoundedPushButton.h>
#include <QtWidgets/QStackedLayout>
#include <src/views/MazeView.h>
#include <utility>
#include <QFile>

class MazeController : public BaseController {
    Q_OBJECT

public:
    explicit MazeController(SimulationSettings &simulationSettings,
                            std::optional<MazeControllerDelegate *> mazeControllerDelegate,
                            std::optional<ReturnToPreviousControllerDelegate *> returnDelegate,
                            QWidget *parent = nullptr);
    ~MazeController() override;

private:
    using MazeHolder = QStackedLayout;

    std::optional<MazeControllerDelegate *> mazeControllerDelegate;
    std::optional<ReturnToPreviousControllerDelegate *> returnDelegate;

    RoundedPushButton *acceptButton;
    RoundedPushButton *saveButton;
    RoundedPushButton *loadButton;

    MazeView *mazeView;
    MazeHolder *mazeHolder;

    void setUpUi();
    QVBoxLayout* prepareButtonsLayout();
    void setMazeHolder(MazeView *mazeView);

    void onAcceptButtonClicked();
    void onSaveButtonClicked();
    void onLoadButtonClicked();
    void onReturnButtonClicked();
};


#endif //MICROMOUSE_MAZECONTROLLER_H
