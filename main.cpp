#include <QApplication>
#include "include/mainwindow.h"



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;

    w.setWindowTitle("Trans F/U");
    w.setWindowIcon(QIcon("images/Application_Ic.png"));
    w.show();

    return a.exec();
}
