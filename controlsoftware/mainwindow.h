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
private slots:
    void on_actionAbout_triggered();
    void on_pushButton_clicked();
    void on_displaywarning_clicked();
    };

#endif // MAINWINDOW_H
