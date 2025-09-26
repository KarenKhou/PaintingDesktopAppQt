#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
qDebug() << "Qt version:" << QT_VERSION_STR;
    return a.exec();
}
