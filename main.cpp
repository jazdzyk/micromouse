#include <iostream>
#include <QApplication>

int main(int argc, char *argv[]) {
    srand(time(nullptr));
    QApplication application(argc, argv);

    return application.exec();
}