#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Model model;
    Controller controller(model);
    MainWindow w(model, controller);
    w.show();
    return a.exec();
}
