/**
 * Control Software Main Window
 *
 * @author Zack Mudd <zmudd@sdsu.edu>
 */
#include "mainwindow.h"
#include "ui_mainwindow.h"

/**
 * Mainwindow Constructor
 *
 * @param QWidget* parent QWidget
 */
mainwindow::mainwindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::mainwindow)
{
    ui->setupUi(this);
    aboutPopup = new about();
    for (int i = 0; i <= int(sizeof(thermos)/sizeof(thermos[0])); i++){
        thermos[i] = 0; /* Set thermocouple values to zero */
    }
    for (int i = 0; i <= int(sizeof(ducers)/sizeof(ducers[0])); i++){
        ducers[i] = 0; /* Set pressure transducer values to zero */
    }

	/* Initialize new QTimer with 0.1 second timeout and connect to onTimer() slot */
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(onTimer()));
    timer->start(100);
	logDataBool = 0;
}

/**
 * Mainwindow destructor
 */
mainwindow::~mainwindow()
{
    delete ui;
}

/**
 * Randomize Thermocouples Button Slot
 *
 * @trigger User Press on button
 */
void mainwindow::on_rand_thermo_clicked()
{
    for (int i = 0; i < 8; i++){ /* Set thermocouples to random values from 0 to 100 */
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

/**
 * Randomize Pressure Transducers Button Slot
 *
 * @trigger User Press on button
 */
void mainwindow::on_rand_pres_clicked()
{
    for (int i = 0; i < 2; i++){ /* Set pressure transducers to random values from 0 to 100 */
        ducers[i] = rand() % 100 + 1;
    }
    this->ui->ducer1->setValue(ducers[0]);
    this->ui->ducer1lcd->display(ducers[0]);
    this->ui->ducer2->setValue(ducers[1]);
    this->ui->ducer2lcd->display(ducers[1]);
}

/**
 * Pressure Transducer 1 Move Warning
 *
 * @trigger User Click on slider
 */
void mainwindow::on_ducer1_sliderPressed()
{
    if (suppressDucers)
        return;
    QString warning = "Hey! You cant move that!";
    showWarningBox(warning);
}

/**
 * Pressure Transducer 2 Move Warning
 *
 * @trigger User Click on slider
 */
void mainwindow::on_ducer2_sliderPressed()
{
    if (suppressDucers)
        return;
    QString warning = "Hey! You cant move that!";
    showWarningBox(warning);
}

/**
 * Pressure Transducer 1 LCD Updater
 *
 * @trigger Pressure transducer 1 slider moving
 * @param int new value of slider
 */
void mainwindow::on_ducer1_sliderMoved(int position)
{
    ducers[0] = position;
    this->ui->ducer1lcd->display(ducers[0]);
}

/**
 * Pressure Transducer 2 LCD Updater
 *
 * @trigger Pressure transducer 2 slider moving
 * @param int new value of slider
 */
void mainwindow::on_ducer2_sliderMoved(int position)
{
    ducers[1] = position;
    this->ui->ducer2lcd->display(ducers[1]);
}

/**
 * Pressure Transducer Warning Suppression Slot
 *
 * @trigger state change of pressure transducer suppression checkbox
 * @param int bool value of checkbox
 */
void mainwindow::on_checkBox_stateChanged(int arg1)
{
    suppressDucers = arg1;
}

/**
 * About Page Menu Slot
 *
 * @trigger Trigger of About action in application menu
 */
void mainwindow::on_actionAbout_triggered()
{
    aboutPopup->show();
}

/**
 * Whats New Menu Slot
 *
 * @trigger Trigger of Whats New action in application menu
 */
void mainwindow::on_actionWhats_New_triggered()
{
    newsPopup = new news();
    newsPopup->show();
}

/**
 * Popup Warning Box Generator
 *
 * @param QString message to display on warning popup
 * @return Generates warning popup
 */
void mainwindow::showWarningBox(QString message){
    warning *warningPopup = new warning();
    warningPopup->setWarning(message);
    warningPopup->show();
}

/**
 * Display user-generated warning popup
 *
 * @trigger User click of Display Warning button
 * @return Generates warning popup with text specified by user
 */
void mainwindow::on_displaywarning_clicked()
{
    showWarningBox(this->ui->warningtext->displayText());
}

/**
 * Manual log user data
 *
 * @trigger User clock of Log Data button
 * @return logs user-specified data to default file of logger
 */
void mainwindow::on_logButton_clicked()
{
    logger l;
    l.openFile(); /* initialize new logger */
    QString qdata = this->ui->logData->displayText(); /* take data from user input box */
    const char *data = qPrintable(qdata);
    l.appendData(data);
    l.closeFile();
}

/**
 * Manual Log Newline Checkbox
 *
 * @trigger State change of Append Newline checkbox
 * @param int bool value of checkbox
 */
void mainwindow::on_logCheckbox_stateChanged(int arg1)
{
    appendNewline = arg1;
}

/**
 * Main timer handler
 *
 * @trigger main trigger timeout()
 */
void mainwindow::onTimer(){
    if (logDataBool){
        logData();
    }
}

/**
 * Global Log Data Checkbox
 *
 * @trigger state change of global log checkbox
 * @param int bool value of checkbox
 */
void mainwindow::on_logDataCheckbox_stateChanged(int arg1)
{
    logDataBool = arg1;
    if (logDataBool) { log.openFile(); return; }
    log.closeFile();
}

/**
 * Global Log Data Handler
 *
 * @trigger onTimer()
 * @return logs global data to file
 */
void mainwindow::logData(){
    for (int i = 0; i < 8; i++){
		std::string sdata = std::to_string(thermos[i]);
		const char *data = sdata.c_str();
        log.appendData(data, 0); /* append thermocouple data with no newline */
    }
    for (int i = 0; i < 2; i++){
		std::string sdata = std::to_string(ducers[i]);
		const char *data = sdata.c_str();
        log.appendData(data, 0);
    }
    log.newLine(); /* append newline to end of thermocouples + ducers */
}
