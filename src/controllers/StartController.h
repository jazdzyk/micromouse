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

/**
 * The StartController class inherits from BaseController
 * and implements MazeControllerDelegate and ReturnToPreviousControllerDelegate.
 * It is a controller class for a window related to the start view.
 *
 * It enables:
 *  - a configutation of the simulation to be performed,
 *  - moving to a window related to the simulation,
 *  - moving to a window related to user's own maze creation.
 */
class StartController : public BaseController, public MazeControllerDelegate, public ReturnToPreviousControllerDelegate {
    Q_OBJECT

public:
    /**
     * StartController class constructor.
     *
     * @param parent a parent class to the StartController
     */
    explicit StartController(QWidget *parent = nullptr);

    /**
     * StartController class destructor.
     */
    ~StartController() override;

private:
    RoundedPushButton *startSimulationButton;
    RadioButtonGroupBox *simulationModeBox;
    RadioButtonGroupBox *mazeSizeBox;
    DropDownGroupBox *algorithmModeBox;
    CheckButtonGroupBox *ownMazeBox;

    /**
     * A private method which enables a configuration of controller's UI.
     */
    void setUpUi();

    /**
     * A private template function which enables moving to the next controller.
     *
     * @tparam Type a type of the next controller
     * @param newController an instance of the next controller
     */
    template<typename Type>
    void moveToNextController(Type *newController) {
        newController->showFullScreen();
        hide();
    }

    /**
     * A private method which is a callback for StartSimulationButton.
     */
    void onStartSimulationButtonClicked();

    /**
     * A private method which is a callback for SimulationMode box with radio buttons.
     *
     * @param id an id of a chosen radio button
     */
    void onSimulationModeChanged(int id);

    /**
     * A private method which is a callback for MazeSize box with radio buttons.
     *
     * @param id an id of a chosen radio button
     */
    void onMazeSizeChanged(int id);

    /**
     * A private method which is a callback for AlgorithmMode box with a drop-down list.
     *
     * @param dropDownId an id of a used drop-down list
     * @param optionId an id of the chosen option in a list
     */
    void onAlgorithmModeChanged(int dropDownId, int optionId);

    /**
     * A private method which is a callback for OwnMaze box with a checkbox and a button.
     *
     * @param id an id of a checkbox clicked
     */
    void onCreateOwnMazeButtonClicked(int id);

    // MazeControllerDelegate methods
    /**
     * A private method which delegates work when MazeController did accept a maze.
     *
     * @param controller an instance of the MazeController
     * @param simulationSettings a set of settings used to perform Micromouse simulation
     */
    void mazeControllerDidAcceptMaze(BaseController *controller, SimulationSettings &simulationSettings) override;

    // ReturnToPreviousControllerDelegate methods
    /**
     * A private method which delegates work when a controller will return.
     *
     * @param controller an instance of the returning controller
     */
    void controllerWillReturn(BaseController *controller) override;
};


#endif //MICROMOUSE_STARTCONTROLLER_H
