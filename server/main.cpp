#include <QtGlobal>
#if QT_VERSION >= 0x050000
#include <QApplication>
#else
#include <QGuiApplication>
#endif
#include "mainwindow.h"
#include <iostream>
#include "aws.h"
#include <fstream>

int main(int argc, char *argv[])
{

    std::ifstream ifs;
    double coordinate[100][3] = { {0, } };
    int j;
    droneDB();

    QApplication a(argc, argv);
    MainWindow w;
    w.show();





    return a.exec();
}
