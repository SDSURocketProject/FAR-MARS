#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "about.h"
#include "warning.h"

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
    void createActions();
    about *aboutPopup;
    warning *warningPopup;
    int thermos[8];
    QString warningMessage;
    void showWarningBox(QString);
    int ducers[2];
    int suppressDucers;
private slots:
    void on_actionAbout_triggered();
    void on_rand_thermo_clicked();
    void on_displaywarning_clicked();
    void on_ducer2_sliderPressed();
    void on_ducer1_sliderPressed();
    void on_rand_pres_clicked();
    void on_ducer2_sliderMoved(int position);
    void on_ducer1_sliderMoved(int position);
    void on_checkBox_stateChanged(int arg1);
};

#endif // MAINWINDOW_H
