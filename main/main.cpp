#include <QtGlobal>
#if QT_VERSION >= 0x050000
#include <QApplication>
#else
#include <QGuiApplication>
#endif

#include "mainwindow.h"
#include <iostream>
#include "aws.h"
#include "dbserver.h"
#include <fstream>
#include <windows.h>

int main(int argc, char *argv[])
{

    std::ifstream ifs;

    droneDB();
    coordinate_code();


    QApplication a(argc, argv);

       MainWindow w;

       w.show();






       return a.exec();

}
