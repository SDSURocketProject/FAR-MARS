#include "mainwindow.h"
#include "about.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    mainwindow w;
    w.show();

    about ab;
    ab.show();

    return a.exec();
}
