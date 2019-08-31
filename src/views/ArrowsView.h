//
// Created by Kuba Jazdzyk on 8/29/19.
//

#ifndef MICROMOUSE_ARROWSVIEW_H
#define MICROMOUSE_ARROWSVIEW_H


#include <QtWidgets/QWidget>
#include <src/utils/Enums.h>
#include <src/elements/ImageLabel.h>
#include <src/utils/Logging.h>
#include <src/utils/utils.h>

class ArrowsView : public QWidget {
public:
    ArrowsView(QWidget *parent = nullptr);
    ~ArrowsView() override;

    void activateAt(Direction direction) const;
    void deactivateAll() const;

private:
    static const int ARROW_SIZE = 50;

    ImageLabel *leftArrow;
    ImageLabel *topArrow;
    ImageLabel *rightArrow;

    void setUpUi();
    QString prepareUrl(Direction direction, bool activated) const;
};


#endif //MICROMOUSE_ARROWSVIEW_H
