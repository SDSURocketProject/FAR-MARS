#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include "about.h"
#include "warning.h"
#include "news.h"
#include "logger.h"

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

    about *aboutPopup;
    warning *warningPopup;
    news *newsPopup;

    int thermos[8];
    int ducers[2];
    int suppressDucers;
    QString warningMessage;
    int appendNewline;
    QTimer *timer;
    int timerDelay;
    int logDataBool;
    logger log;

private slots:
    void on_rand_thermo_clicked();
    void on_rand_pres_clicked();
    void on_ducer1_sliderPressed();
    void on_ducer2_sliderPressed();
    void on_ducer1_sliderMoved(int position);
    void on_ducer2_sliderMoved(int position);
    void on_checkBox_stateChanged(int arg1);
    void on_displaywarning_clicked();
    void on_actionWhats_New_triggered();
    void on_actionAbout_triggered();
    void on_logButton_clicked();
    void onTimer();
    void on_logCheckbox_stateChanged(int arg1);
    void on_logDataCheckbox_stateChanged(int arg1);
};

#endif // MAINWINDOW_H
