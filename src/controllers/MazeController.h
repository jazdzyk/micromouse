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

/**
 * The MazeController class inherits from BaseController and is a controller class
 * for a window related to own maze's creation.
 *
 * It enables:
 *  - 'building' a maze by a user,
 *  - loading a maze from a binary file,
 *  - saving a maze to the binary file.
 */
class MazeController : public BaseController {
    Q_OBJECT

public:
    /**
     * MazeController class constructor.
     *
     * @param simulationSettings a set of settings used to perform Micromouse simulation
     * @param mazeControllerDelegate an optional delegate for MazeController
     * @param returnDelegate an optional delegate due to the purpose of returning to the previous controller
     * @param parent a parent class to the MazeController
     */
    explicit MazeController(SimulationSettings &simulationSettings,
                            std::optional<MazeControllerDelegate *> mazeControllerDelegate,
                            std::optional<ReturnToPreviousControllerDelegate *> returnDelegate,
                            QWidget *parent = nullptr);

    /**
     * MazeController class destructor.
     */
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

    /**
     * A private method which enables a configuration of controller's UI.
     */
    void setUpUi();

    /**
     * A private method which prepares layout with buttons for displaying in a UI.
     *
     * @return a layout with buttons
     */
    QVBoxLayout *prepareButtonsLayout();

    /**
     * A private method which assigns MazeView into its placeholder.
     *
     * @param mazeView a MazeView object to be assigned into placeholder
     */
    void setMazeHolder(MazeView *mazeView);

    /**
     * A private method which is a callback for AcceptButton.
     */
    void onAcceptButtonClicked();

    /**
     * A private method which is a callback for SaveButton.
     */
    void onSaveButtonClicked();

    /**
     * A private method which is a callback for LoadButton.
     */
    void onLoadButtonClicked();

    /**
     * A private method which is a callback for ReturnButton.
     */
    void onReturnButtonClicked();
};


#endif //MICROMOUSE_MAZECONTROLLER_H
