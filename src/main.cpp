﻿/**
 * Control Software Main
 *
 * @author Zack Mudd <zmudd@sdsu.edu>
 */

#include "mainwindow.h"
#include <QApplication>
#include <QtCharts/QLineSeries>
#include <QtCharts/QChartView>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	mainwindow w;
	w.show();

	return a.exec();
}
