#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <chrono>
#include <math.h>
#include <QMainWindow>
#include <QProgressBar>
#include <QTimer>
#include <qcgaugewidget.h>
#include <time.h>

#include "csv.h"
#include "liveplot.h"
#include "logger.h"
#include "serial.h"

namespace Ui {
	class mainwindow;
}

class mainwindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit mainwindow(QWidget *parent = nullptr);
	~mainwindow();

private:
	Ui::mainwindow *ui;
	void createActions(void);
	void getData(void);
	void logData(void);
	void update_data(void);
	void updatePlots(void);

	livePlot *plot;

	float pressures[4];
	float thermo[1];
	int halleffect[2];
	float battVoltage[1];

	int appendNewline;
	int logCount = 0;
	int logDataBool;
	int plotBool;
	int timerDelay;
	uint32_t timestamp;
	int serial_timeout;
	logger log;
	QProgressBar *thermobar;
	QTimer *timer;
	QcGaugeWidget *helGauge;
	QcGaugeWidget *loxGauge;
	QcGaugeWidget *ch4Gauge;
	QcNeedleItem *helNeedle;
	QcNeedleItem *loxNeedle;
	QcNeedleItem *ch4Needle;
	std::chrono::high_resolution_clock::time_point start;



private slots:
	void onTimer(void);
	void on_logDataCheckbox_stateChanged(int arg1);
	void on_livePlotButton_clicked(void);
};

#endif // MAINWINDOW_H
