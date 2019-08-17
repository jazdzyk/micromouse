#include <iostream>
#include <QApplication>
#include <src/controllers/StartController.h>
#include <QtWidgets/QStyleFactory>

int main(int argc, char *argv[]) {
    srand(time(nullptr));

    QApplication application(argc, argv);
    application.setStyle(QStyleFactory::create("Fusion"));

    StartController controller;

    return application.exec();
}