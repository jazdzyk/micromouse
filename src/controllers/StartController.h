//
// Created by Kuba Jazdzyk on 8/15/19.
//

#ifndef MICROMOUSE_STARTCONTROLLER_H
#define MICROMOUSE_STARTCONTROLLER_H


#include "BaseController.h"

class StartController : public BaseController {
    Q_OBJECT

public:
    explicit StartController(QWidget *parent = nullptr);
    ~StartController();

private:
};


#endif //MICROMOUSE_STARTCONTROLLER_H
