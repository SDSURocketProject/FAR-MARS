#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <chrono>
#include <math.h>
#include <QMainWindow>
#include <QTimer>
#include <time.h>
#include "csv.h"
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

    warning *warningPopup;

    float data[3];
    int appendNewline;
    int timerDelay;
    int logDataBool;
	int serial_timeout;
    logger log;
    QTimer *timer;
	std::chrono::high_resolution_clock::time_point start;

private slots:
    void onTimer();
    void on_logDataCheckbox_stateChanged(int arg1);
};

#endif // MAINWINDOW_H
