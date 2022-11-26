#include <QtGlobal>
#if QT_VERSION >= 0x050000
#include <QApplication>
#else
#include <QGuiApplication>
#endif
#include "mainwindow.h"


int main(int argc, char *argv[])
{
    
    
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    droneDB();
    
    return a.exec();
}
