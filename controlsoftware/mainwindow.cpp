#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "about.h"

mainwindow::mainwindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::mainwindow)
{
    ui->setupUi(this);
    aboutPopup = new about();
}

mainwindow::~mainwindow()
{
    delete ui;
}

void mainwindow::on_actionAbout_triggered()
{
    aboutPopup->show();
}
