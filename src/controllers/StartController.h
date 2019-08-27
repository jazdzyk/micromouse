//
// Created by Kuba Jazdzyk on 8/15/19.
//

#ifndef MICROMOUSE_STARTCONTROLLER_H
#define MICROMOUSE_STARTCONTROLLER_H


#include <src/elements/RoundedPushButton.h>
#include <src/elements/RadioButtonGroupBox.h>
#include <src/elements/DropDownGroupBox.h>
#include <src/elements/CheckButtonGroupBox.h>
#include <src/protocols/delegates/ReturnToPreviousControllerDelegate.h>
#include "BaseController.h"
#include "src/utils/Logging.h"
#include "SimulationController.h"
#include "MazeController.h"

class StartController : public BaseController, public MazeControllerDelegate, public ReturnToPreviousControllerDelegate {
    Q_OBJECT

public:
    explicit StartController(QWidget *parent = nullptr);
    ~StartController() override;

private:
    RoundedPushButton *startSimulationButton;
    RadioButtonGroupBox *simulationModeBox;
    RadioButtonGroupBox *mazeSizeBox;
    DropDownGroupBox *algorithmModeBox;
    CheckButtonGroupBox *ownMazeBox;

    void setUpUi();

    template<typename Type>
    void moveToNextController(Type *newController) {
        newController->showFullScreen();
        hide();
    }

    void onStartSimulationButtonClicked();
    void onSimulationModeChanged(int id);
    void onMazeSizeChanged(int id);
    void onAlgorithmModeChanged(int dropDownId, int optionId);
    void onCreateOwnMazeButtonClicked(int id);

    // MazeControllerDelegate methods
    void mazeControllerDidAcceptMaze(BaseController *controller, SimulationSettings &simulationSettings) override;

    // ReturnToPreviousControllerDelegate methods
    void controllerWillReturn(BaseController *controller) override;
};


#endif //MICROMOUSE_STARTCONTROLLER_H
