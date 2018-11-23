#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "about.h"

mainwindow::mainwindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::mainwindow)
{
    ui->setupUi(this);
}

mainwindow::~mainwindow()
{
    delete ui;
}

void mainwindow::about(){
}
