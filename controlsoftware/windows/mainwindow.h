#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include "csv.h"
#include "warning.h"
#include "logger.h"
#include <time.h>
#include <chrono>
#include "serial.h"
#include <math.h>
#include <windows.h>

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
    void logData();
	void getData();
	void update_data();

    warning *warningPopup;

    float data[3];
    int appendNewline;
    QTimer *timer;
    int timerDelay;
    int logDataBool;
	int serial_timeout;
    logger log;
	std::chrono::high_resolution_clock::time_point start;

private slots:
    void onTimer();
    void on_logDataCheckbox_stateChanged(int arg1);
};

#endif // MAINWINDOW_H
