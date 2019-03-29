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
#include "warning.h"

namespace Ui {
class mainwindow;
}

class mainwindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit mainwindow(QWidget *parent = nullptr);
    static void showWarningBox(QString);
    ~mainwindow();

private:
    Ui::mainwindow *ui;
    void createActions();
	void getData();
    void logData();
	void update_data();
	void updatePlots();

    warning *warningPopup;
	livePlot *plot;

    float pressures[4];
	float thermo[1];
	uint8_t halleffect[2];

    int appendNewline;
	int logCount = 0;
    int logDataBool;
	int plotBool;
    int timerDelay;
	uint32_t timestamp;
	int serial_timeout;
    logger log;
	QProgressBar *chamberbar;
    QTimer *timer;
	QcGaugeWidget *helGauge;
	QcGaugeWidget *loxGauge;
	QcGaugeWidget *ch4Gauge;
	QcNeedleItem *helNeedle;
	QcNeedleItem *loxNeedle;
	QcNeedleItem *ch4Needle;
	std::chrono::high_resolution_clock::time_point start;



private slots:
    void onTimer();
    void on_logDataCheckbox_stateChanged(int arg1);
    void on_livePlotButton_clicked();
};

#endif // MAINWINDOW_H
