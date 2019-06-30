#include "mainwindow.h"
#include "pool.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QCoreApplication::setOrganizationName("Tsinghua");
    QCoreApplication::setApplicationName("Plongeur");
    QCoreApplication::setApplicationVersion(QT_VERSION_STR);

    Pool::s_texture = new QPixmap(QPixmap(":/images/resources/tile2.jpg").scaledToHeight(28));

    MainWindow w;
    w.show();

    return a.exec();
}
