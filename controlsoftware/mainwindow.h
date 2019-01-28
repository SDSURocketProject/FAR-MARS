#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include "about.h"
#include "csv.h"
#include "warning.h"
#include "news.h"
#include "logger.h"
#include <time.h>
#include <chrono>
#include "serial.h"

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

    about *aboutPopup;
    warning *warningPopup;
    news *newsPopup;

    int data[7];
    QString warningMessage;
    int appendNewline;
    QTimer *timer;
    int timerDelay;
    int logDataBool;
	int serial_timeout;
    logger log;
	std::chrono::high_resolution_clock::time_point start;

private slots:
    void on_rand_data_clicked();
    void on_displaywarning_clicked();
    void on_actionWhats_New_triggered();
    void on_actionAbout_triggered();
    void onTimer();
    void on_logDataCheckbox_stateChanged(int arg1);
};

#endif // MAINWINDOW_H
