#include "mainwindow.h"

#include <QApplication>
//Staging a change.
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
