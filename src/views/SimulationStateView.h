//
// Created by Kuba Jazdzyk on 8/29/19.
//

#ifndef MICROMOUSE_SIMULATIONSTATEVIEW_H
#define MICROMOUSE_SIMULATIONSTATEVIEW_H


#include <QtWidgets/QFrame>
#include <src/utils/Enums.h>
#include <src/utils/Localizable.h>
#include <QtWidgets/QLabel>
#include <src/utils/Logging.h>
#include <QtWidgets/QHBoxLayout>
#include "ArrowsView.h"
#include <src/utils/utils.h>

class SimulationStateView : public QFrame {
public:
    SimulationStateView();
    ~SimulationStateView() override;

    void setName(const QString& name) const;

    void setTimeValue(double time);
    void setDistanceValue(int distance);
    void setSpeedValue(double speed);

    void activateArrow(Direction direction) const;
    void deactivateAllArrows() const;

private:
    Localizable::Locale locale = Localizable::pl;

    QLabel *nameLabel;

    QLabel *timeValueLabel;
    QLabel *distanceValueLabel;
    QLabel *speedValueLabel;

    ArrowsView *arrowsView;

    void setUpUi();
    QHBoxLayout* prepareValuesLayout();
};


#endif //MICROMOUSE_SIMULATIONSTATEVIEW_H
