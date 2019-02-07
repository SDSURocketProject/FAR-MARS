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
    for (int i = 0; i <= int(sizeof(data)/sizeof(data[0])); i++){
        data[i] = 0; /* Set data values to zero */
    }
	/* Initialize new QTimer with 0.1 second timeout and connect to onTimer() slot */
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(onTimer()));
    timer->start(50);
	logDataBool = 0;
	serial_timeout = 0;
}

/**
 * Mainwindow destructor
 */
mainwindow::~mainwindow()
{
    delete ui;
}

/**
 * Randomize Data Button Slot
 *
 * @trigger User Press on button
 */
void mainwindow::on_rand_data_clicked()
{
	showWarningBox("depreciated function");
	update_data();
}

void mainwindow::update_data(){
    this->ui->data1->setValue(ceil(data[0]));
    this->ui->data1lcd->display((double)data[0]);
    this->ui->data2->setValue(ceil(data[1]));
    this->ui->data2lcd->display((double)data[1]);
    this->ui->data3->setValue(ceil(data[2]));
    this->ui->data3lcd->display((double)data[2]);
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
 * Main timer handler
 *
 * @trigger main trigger timeout()
 */
void mainwindow::onTimer(){
    if (logDataBool){
        if (serial_timeout > 50){
			this->ui->logDataCheckbox->setCheckState(Qt::Unchecked);
			return;
		}
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
    if (logDataBool) {
		int u = uart_init();
		if (u != 0){
			showWarningBox("Serial Connection Not Opened");
			logDataBool = 0;
			return;
		}
        QString qfilename = this->ui->logFileNameBox->displayText();
		const char *filename = qfilename.toStdString().c_str();
        log.setFile(filename);
        start = std::chrono::high_resolution_clock::now();
		log.openFile();
		return;
	}
    log.closeFile();
}

/**
 * Global Log Data Handler
 *
 * @trigger onTimer()
 * @return logs global data to file
 */
void mainwindow::logData(){
	std::chrono::high_resolution_clock::time_point now = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> timespan = std::chrono::duration_cast<std::chrono::duration<double>>(now - start);
	int time[1] = { (timespan.count()*1000) };
	getData();
	log.appendData(time, 1, 0);
	log.appendData(data, 3, 1);
}

void mainwindow::getData(){
	char message[11];
	float pressures[3];
	u_int32_t timestamp;
	int n = readMessage(message);
	if (n < 0){
		serial_timeout++;
		return;
	}
	parseMessage(message, pressures, &timestamp);
	for (int i = 0; i < 3; i++){
		data[i] = pressures[i];
	}
	update_data();
}
