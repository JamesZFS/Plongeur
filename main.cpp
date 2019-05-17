#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QCoreApplication::setOrganizationName("Tsinghua");
    QCoreApplication::setApplicationName("Plongeur");
    QCoreApplication::setApplicationVersion(QT_VERSION_STR);

    MainWindow w;
    w.show();

    return a.exec();
}
