//
// Created by Kuba Jazdzyk on 8/15/19.
//

#ifndef MICROMOUSE_BASECONTROLLER_H
#define MICROMOUSE_BASECONTROLLER_H


#include <QtWidgets/QMainWindow>

class BaseController : public QMainWindow {
    Q_OBJECT

public:
    explicit BaseController(QWidget *parent = nullptr);
    ~BaseController();
};


#endif //MICROMOUSE_BASECONTROLLER_H
