#include "mainwindow.h"

#include <QApplication>
#include "DatabaseManager.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    if(!DatabaseManager::instance().open("database.db"))
    {
        return -1;
    }
    else
    {
        DatabaseManager::instance().initialize();
    }

    MainWindow w;
    w.show();
    return a.exec();
}
