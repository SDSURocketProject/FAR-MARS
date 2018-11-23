#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "about.h"

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
    int thermos[8];
private slots:
    void on_actionAbout_triggered();
    void on_pushButton_clicked();
};

#endif // MAINWINDOW_H
