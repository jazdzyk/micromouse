//
// Created by Kuba Jazdzyk on 8/15/19.
//

#ifndef MICROMOUSE_BASECONTROLLER_H
#define MICROMOUSE_BASECONTROLLER_H


#include <QApplication>
#include <QtWidgets/QMainWindow>
#include <src/utils/SimulationSettings.h>
#include <QtWidgets/QPushButton>
#include <src/utils/Localizable.h>
#include <QtWidgets/QHBoxLayout>
#include <src/utils/Logging.h>
#include <src/utils/utils.h>

/**
 * The BaseController class inherits from QMainWindow class and is a base class for all controllers.
 */
class BaseController : public QMainWindow {
    Q_OBJECT

public:
    /**
     * BaseController class constructor.
     *
     * @param parent a parent class to the BaseController
     */
    explicit BaseController(QWidget *parent = nullptr);

    /**
     * BaseController class constructor.
     *
     * @param simulationSettings a set of settings used to perform Micromouse simulation
     * @param parent a parent class to the BaseController
     */
    explicit BaseController(SimulationSettings &simulationSettings, QWidget *parent = nullptr);

    /**
     * BaseController class destructor.
     */
    ~BaseController() override;

    /**
     * A public method which enables a configuration of settings used to perform Micromouse simulation.
     *
     * @param simulationSettings a set of settings used to perform Micromouse simulation
     */
    void setSimulationSettings(SimulationSettings &simulationSettings);

protected:
    using QWidgets = const std::vector<QWidget*>;

    QPushButton *quitButton;
    QPushButton *returnButton;

    Localizable::Locale locale = Localizable::pl;
    SimulationSettings simulationSettings;

    /**
     * A protected method which enables adding a single layout to the parent layout.
     *
     * @param layout a layout to be added
     * @param stretch a size of stretch that should be set to the layout being added
     */
    void addToParentLayout(QLayout *layout, int stretch = 0);

    /**
     * A protected method which enables adding a single widget to the parent layout.
     *
     * @param widget a widget to be added
     * @param stretch a size of stretch that should be set to the layout being added
     */
    void addToParentLayout(QWidget *widget, int stretch = 0);

    /**
     * A protected method which enables adding a multiple widgets to the given layout.
     *
     * @param widgets a vector of widgets to be added
     * @param layout a layout where widgets should be added
     */
    void addWidgetsToLayout(QWidgets &widgets, QLayout *layout);

private:
    QHBoxLayout *parentLayout;

    /**
     * A private method which enables a configuration of controller's UI.
     */
    void setUpUi();

    /**
     * A private method which creates QuitButton.
     */
    void createQuitButton();

    /**
     * A private method which creates ReturnButton.
     */
    void createReturnButton();

    /**
     * A private factory method which creates a button of type QPushButton with given icon.
     *
     * @param iconUrl a url to the location of the icon to be displayed
     * @return a button with an icon
     */
    QPushButton *createButton(const QString &iconUrl);
};


#endif //MICROMOUSE_BASECONTROLLER_H
