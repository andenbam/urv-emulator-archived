#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);

    a.setOrganizationName("BlackSofa");
    a.setOrganizationDomain("www.google.ru");
    a.setApplicationName("urv-emulator");
    a.setApplicationDisplayName("URV Emulator with SQLite");
    a.setApplicationVersion("0.0.1.0");

    MainWindow *mw = new MainWindow();
    mw->setSQLWorker(new SQLWorker());
    mw->connectTo();
    if (!mw->isHidden())
        return a.exec();
    else return 0;
}
