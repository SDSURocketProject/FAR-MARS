#include "mainwindow.h"
#include "about.h"
#include "warning.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    mainwindow w;
    w.show();

    return a.exec();
}
