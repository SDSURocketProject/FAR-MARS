#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "about.h"

mainwindow::mainwindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::mainwindow)
{
    ui->setupUi(this);
    aboutPopup = new about();
    warningPopup = new warning();
    for (int i = 0; i <= int(sizeof(thermos)/sizeof(thermos[0])); i++){
        thermos[i] = 0;
    }
    for (int i = 0; i <= int(sizeof(ducers)/sizeof(ducers[0])); i++){
        ducers[i] = 0;
    }
}

mainwindow::~mainwindow()
{
    delete ui;
}

void mainwindow::on_actionAbout_triggered()
{
    aboutPopup->show();
}

void mainwindow::on_rand_thermo_clicked()
{
    for (int i = 0; i < 8; i++){
        thermos[i] = rand() % 100 + 1;
    }
    this->ui->thermo1->setValue(thermos[0]);
    this->ui->thermo1lcd->display(thermos[0]);
    this->ui->thermo2->setValue(thermos[1]);
    this->ui->thermo2lcd->display(thermos[1]);
    this->ui->thermo3->setValue(thermos[2]);
    this->ui->thermo3lcd->display(thermos[2]);
    this->ui->thermo4->setValue(thermos[3]);
    this->ui->thermo4lcd->display(thermos[3]);
    this->ui->thermo5->setValue(thermos[4]);
    this->ui->thermo5lcd->display(thermos[4]);
    this->ui->thermo6->setValue(thermos[5]);
    this->ui->thermo6lcd->display(thermos[5]);
    this->ui->thermo7->setValue(thermos[6]);
    this->ui->thermo7lcd->display(thermos[6]);
    this->ui->thermo8->setValue(thermos[7]);
    this->ui->thermo8lcd->display(thermos[7]);
}

void mainwindow::showWarningBox(QString message){
    warning *warningPopup = new warning();
    warningPopup->setWarning(message);
    warningPopup->show();
}

void mainwindow::on_displaywarning_clicked()
{
    showWarningBox(this->ui->warningtext->displayText());
}

void mainwindow::on_ducer2_sliderPressed()
{
    QString warning = "Hey! You cant move that!";
    showWarningBox(warning);
}

void mainwindow::on_ducer1_sliderPressed()
{
    QString warning = "Hey! You cant move that!";
    showWarningBox(warning);
}

void mainwindow::on_rand_pres_clicked()
{
    for (int i = 0; i < 2; i++){
        thermos[i] = rand() % 100 + 1;
    }
    this->ui->ducer1->setValue(ducers[0]);
    this->ui->ducer1lcd->display(ducers[0]);
    this->ui->ducer2->setValue(ducers[1]);
    this->ui->ducer2lcd->display(ducers[1]);
    std::printf("Ducers Clicked");
}
