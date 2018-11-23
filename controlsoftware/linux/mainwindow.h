#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "about.h"
#include "warning.h"
#include "news.h"

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
    void showWarningBox(QString);
    void createActions();

    about *aboutPopup;
    warning *warningPopup;
    news *newsPopup;

    int thermos[8];
    int ducers[2];
    int suppressDucers;
    QString warningMessage;

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
};

#endif // MAINWINDOW_H