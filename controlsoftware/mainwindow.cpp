﻿#include "mainwindow.h"
#include "ui_mainwindow.h"

mainwindow::mainwindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::mainwindow)
{
	ui->setupUi(this);
	/* Initialize new QTimer with 0.1 second timeout and connect to onTimer() slot */
	timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(onTimer()));
	timer->start(50);
	logDataBool = 0;
	plotBool = 0;
	serial_timeout = 0;

	helGauge = new QcGaugeWidget;
	loxGauge = new QcGaugeWidget;
	ch4Gauge = new QcGaugeWidget;

	ch4Gauge->addArc(55);
	ch4Gauge->addDegrees(65)->setValueRange(0,2000);
	QcColorBand *ch4ClrBand = ch4Gauge->addColorBand(100, 0);
	ch4ClrBand->setValueRange(0,2000);
	ch4Gauge->addValues(80, 0)->setValueRange(0,2000);
	ch4Gauge->addLabel(70)->setText("Methane");
	QcLabelItem *ch4Label = ch4Gauge->addLabel(40);
	ch4Label->setText("0");
	ch4Needle = ch4Gauge->addNeedle(60);
	ch4Needle->setLabel(ch4Label);
	ch4Needle->setColor(Qt::blue);
	ch4Needle->setValueRange(0,2000);
	//ch4Needle->addBackground(7);
	ui->data->addWidget(ch4Gauge);

	QSpacerItem *spacer1 = new QSpacerItem(5, 1);
	ui->data->addItem(spacer1);

	loxGauge->addArc(55);
	loxGauge->addDegrees(65)->setValueRange(0,2000);
	QcColorBand *loxClrBand = loxGauge->addColorBand(100, 0);
	loxClrBand->setValueRange(0,2000);
	loxGauge->addValues(80, 0)->setValueRange(0,2000);
	loxGauge->addLabel(70)->setText("LOX");
	QcLabelItem *loxLabel = loxGauge->addLabel(40);
	loxLabel->setText("0");
	loxNeedle = loxGauge->addNeedle(60);
	loxNeedle->setLabel(loxLabel);
	loxNeedle->setColor(Qt::blue);
	loxNeedle->setValueRange(0,2000);
	//loxNeedle->addBackground(7);
	ui->data->addWidget(loxGauge);

	QSpacerItem *spacer2 = new QSpacerItem(5, 1);
	ui->data->addItem(spacer2);

	helGauge->addArc(55);
	helGauge->addDegrees(65)->setValueRange(0,6000);
	QcColorBand *helClrBand = helGauge->addColorBand(100, 1);
	helClrBand->setValueRange(0,6000);
	helGauge->addValues(80, 1)->setValueRange(0,6000);
	helGauge->addLabel(70)->setText("Helium");
	QcLabelItem *helLabel = helGauge->addLabel(40);
	helLabel->setText("0");
	helNeedle = helGauge->addNeedle(60);
	helNeedle->setLabel(helLabel);
	helNeedle->setColor(Qt::blue);
	helNeedle->setValueRange(0,6000);
	//helNeedle->addBackground(7);
	ui->data->addWidget(helGauge);

	thermobar = new QProgressBar;
	thermobar->setOrientation(Qt::Vertical);
	thermobar->setMinimum(0);
	thermobar->setMaximum(1500);
	thermobar->setTextVisible(true);
	ui->data->addWidget(thermobar);
}

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
	ch4Needle->setCurrentValue(pressures[CH4_READING]);
	loxNeedle->setCurrentValue(pressures[LOX_READING]);
	helNeedle->setCurrentValue(pressures[HEL_READING]);
	thermobar->setValue(pressures[CBR_READING]);
	ui->chamberLCD->display(pressures[CBR_READING]);
	ui->tcLCD->display(thermo[0]);
	ui->batteryLCD->display(battVoltage[0]);
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
	if (plotBool){
		updatePlots();
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
	long time[1];
	struct timespec spec;
	clock_gettime(CLOCK_REALTIME, &spec);
	time[0] = spec.tv_nsec / 1000000l;

	getData();

	log.appendData(time, 1, 0);
	log.appendData(pressures, 5, 0);
	log.appendData(thermo, 1, 0);
	log.appendData(halleffect, 2, 0);
	log.appendData(battVoltage, 1, 1);
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
	struct daqSensors message;
	int n = readMessage(&message);
	if (n < 0){
		//serial_timeout++;
		return;
	}
	parsePressureMessage(&message);
	
	//printf("%i\n", message.timestamp);
	pressures[CH4_READING] = message.PT_methane;
	pressures[LOX_READING] = message.PT_LOX;
	pressures[HEL_READING] = message.PT_helium;
	pressures[CBR_READING] = message.PT_chamber;
	pressures[REG_READING] = message.PT_heliumReg;
	halleffect[CH4_VNT]    = message.HALL_methane;
	halleffect[LOX_VNT]    = message.HALL_LOX;
	thermo[UAF]            = message.TC_uaf;
	battVoltage[1]         = message.BATT_voltage;
	timestamp              = message.timestamp;
	update_data();
}

/**
 * Handler for live plot button
 * @param bool value of button
 * @see liveplot.h
 */
void
mainwindow::on_livePlotButton_clicked()
{
	if (plotBool){
		plot->close();
		plotBool = 0;
	}else{
		plot = new livePlot();
		plot->setupPlot();
		plot->show();
		plotBool = 1;
	}
}

/**
 * Update plots with new data[] values
 */
void
mainwindow::updatePlots(){
	plot->appendData(pressures, &timestamp);
}
