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
 * GUI Data Updater
 * Sets GUI Elements to display values in static data array
 */
void
mainwindow::update_data(){
	if (logCount++ < 5){
		return;
	}
	logCount = 0;
    this->ui->data1->setValue(ceil(data[0]));
    this->ui->data1lcd->display((int)data[0]);
    this->ui->data2->setValue(ceil(data[1]));
    this->ui->data2lcd->display((int)data[1]);
    this->ui->data3->setValue(ceil(data[2]));
    this->ui->data3lcd->display((int)data[2]);
}

/**
 * Popup Warning Box Generator
 * Generates a popup displaying the QString supplied
 *
 * @param QString message to display on warning popup
 */
void
mainwindow::showWarningBox(QString message){
    warning *warningPopup = new warning();
    warningPopup->setWarning(message);
    warningPopup->show();
}

/**
 * Main timer handler
 * Runs whenever the main timer timeouts to run repeating tasks
 */
void
mainwindow::onTimer(){
    if (logDataBool){
        if (serial_timeout > 50){
			this->ui->logDataCheckbox->setCheckState(Qt::Unchecked);
			return;
		}
		logData();

    }
}

/**
 * Global Log Data Checkbox handler
 * Triggered by state change of Log Data checkbox
 * Initiates UART connection and opens log file
 * @see uart_init()
 * @see openFile()
 * @param int new value of checkbox
 */
void
mainwindow::on_logDataCheckbox_stateChanged(int arg1)
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
 * Logs data from static data array, with timestamp
 * @see appendData()
 */
void
mainwindow::logData(){
	std::chrono::high_resolution_clock::time_point now = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> timespan = std::chrono::duration_cast<std::chrono::duration<double>>(now - start);
	int time[1] = { (timespan.count()*1000) };
	getData();
	log.appendData(time, 1, 0);
	log.appendData(data, 3, 1);
}

/**
 * Data Retrieval Routine
 * Recieves data from UART connection, updates static data array, and updates GUI to reflect changes
 * @see readMessage()
 * @see parseMessage()
 * @see updateData()
 */
void
mainwindow::getData(){
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
