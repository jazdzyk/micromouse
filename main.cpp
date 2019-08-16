#include <iostream>
#include <QApplication>
#include <src/controllers/BaseController.h>

int main(int argc, char *argv[]) {
    srand(time(nullptr));

    QApplication application(argc, argv);

    BaseController controller;

    return application.exec();
}