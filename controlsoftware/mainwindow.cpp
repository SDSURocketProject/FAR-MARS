#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "about.h"

mainwindow::mainwindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::mainwindow)
{
    ui->setupUi(this);
    for (int i = 0; i <= int(sizeof(data)/sizeof(data[0])); i++){
        data[i] = 0; /* Set data values to zero */
    }
}

mainwindow::~mainwindow()
{
    delete ui;
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
