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

class BaseController : public QMainWindow {
    Q_OBJECT

public:
    explicit BaseController(QWidget *parent = nullptr);
    explicit BaseController(SimulationSettings &simulationSettings, QWidget *parent = nullptr);
    ~BaseController();

    void setSimulationSettings(SimulationSettings &simulationSettings);

protected:
    using QWidgets = const std::vector<QWidget*>;

    QPushButton *quitButton;
    QPushButton *returnButton;

    Localizable::Locale locale = Localizable::PL;
    SimulationSettings simulationSettings;

    void addToParentLayout(QLayout *layout, int stretch = 0);
    void addToParentLayout(QWidget *widget, int stretch = 0);
    void addWidgetsToLayout(QWidgets &widgets, QLayout *layout);

private:
    QHBoxLayout *parentLayout;

    void setUpUi();
    void createQuitButton();
    void createReturnButton();

    QPushButton* createButton(const QString &iconUrl);
};


#endif //MICROMOUSE_BASECONTROLLER_H
