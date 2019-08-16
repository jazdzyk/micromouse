#include <iostream>
#include <QApplication>
#include <src/controllers/StartController.h>

int main(int argc, char *argv[]) {
    srand(time(nullptr));

    QApplication application(argc, argv);

    StartController controller;
    controller.show();

    return application.exec();
}