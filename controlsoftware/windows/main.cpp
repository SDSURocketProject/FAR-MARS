/**
 * Control Software Main
 *
 * @author Zack Mudd <zmudd@sdsu.edu>
 */

#include <QApplication>
#include <windows.h>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    mainwindow w;
    w.show();

    return a.exec();
}
