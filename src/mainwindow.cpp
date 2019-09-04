#include "mainwindow.h"
#include "ui_mainwindow.h"

/**
 * @brief Mainwindow Constructor
 *
 * @param[in] QWidget* parent QWidget
 */
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
	board_selection = primary_board;
	serial_timeout = 0;

	QStringList board_options = {"Primary", "Backup 1"};
	ui->boardSelectionComboBox->addItems(board_options);

	helGauge = new QcGaugeWidget;
	loxGauge = new QcGaugeWidget;
	ch4Gauge = new QcGaugeWidget;

	ch4Gauge->addArc(55);
	ch4Gauge->addDegrees(65)->setValueRange(0, ((int)PRESSURE_METHANE_MAX_PRESSURE)+500 );
	QcColorBand *ch4ClrBand = ch4Gauge->addColorBand(100, 0);
	ch4ClrBand->setValueRange(0, ((int)PRESSURE_METHANE_MAX_PRESSURE)+500 );
	ch4Gauge->addValues(80, 0)->setValueRange(0, ((int)PRESSURE_METHANE_MAX_PRESSURE)+500 );
	ch4Gauge->addLabel(70)->setText("Methane");
	QcLabelItem *ch4Label = ch4Gauge->addLabel(40);
	ch4Label->setText("0");
	ch4Needle = ch4Gauge->addNeedle(60);
	ch4Needle->setLabel(ch4Label);
	ch4Needle->setColor(Qt::blue);
	ch4Needle->setValueRange(0, ((int)PRESSURE_METHANE_MAX_PRESSURE)+500 );
	ui->data->addWidget(ch4Gauge);

	QSpacerItem *spacer1 = new QSpacerItem(5, 1);
	ui->data->addItem(spacer1);

	loxGauge->addArc(55);
	loxGauge->addDegrees(65)->setValueRange(0, ((int)PRESSURE_LOX_MAX_PRESSURE)+500 );
	QcColorBand *loxClrBand = loxGauge->addColorBand(100, 0);
	loxClrBand->setValueRange(0, ((int)PRESSURE_LOX_MAX_PRESSURE)+500 );
	loxGauge->addValues(80, 0)->setValueRange(0, ((int)PRESSURE_LOX_MAX_PRESSURE)+500 );
	loxGauge->addLabel(70)->setText("LOX");
	QcLabelItem *loxLabel = loxGauge->addLabel(40);
	loxLabel->setText("0");
	loxNeedle = loxGauge->addNeedle(60);
	loxNeedle->setLabel(loxLabel);
	loxNeedle->setColor(Qt::blue);
	loxNeedle->setValueRange(0, ((int)PRESSURE_LOX_MAX_PRESSURE)+500 );
	ui->data->addWidget(loxGauge);

	QSpacerItem *spacer2 = new QSpacerItem(5, 1);
	ui->data->addItem(spacer2);

	helGauge->addArc(55);
	helGauge->addDegrees(65)->setValueRange(0, ((int)PRESSURE_HELIUM_MAX_PRESSURE)+200 );
	QcColorBand *helClrBand = helGauge->addColorBand(100, 1);
	helClrBand->setValueRange(0, ((int)PRESSURE_HELIUM_MAX_PRESSURE)+200 );
	helGauge->addValues(80, 1)->setValueRange(0, ((int)PRESSURE_HELIUM_MAX_PRESSURE)+200 );
	helGauge->addLabel(70)->setText("Helium");
	QcLabelItem *helLabel = helGauge->addLabel(40);
	helLabel->setText("0");
	helNeedle = helGauge->addNeedle(60);
	helNeedle->setLabel(helLabel);
	helNeedle->setColor(Qt::blue);
	helNeedle->setValueRange(0, ((int)PRESSURE_HELIUM_MAX_PRESSURE)+200 );
	ui->data->addWidget(helGauge);

	thermobar = new QProgressBar;
	thermobar->setOrientation(Qt::Vertical);
	thermobar->setMinimum(0);
	thermobar->setMaximum(1500);
	thermobar->setTextVisible(true);
	ui->data->addWidget(thermobar);
}

/**
 * @brief Mainwindow destructor
 */
mainwindow::~mainwindow()
{
	delete ui;
}

/**
 * @brief GUI Data Updater
 * @brief Sets GUI Elements to display values in static data array
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

	QPalette lox_palette = ui->hall_lox_status->palette();
	lox_palette.setColor(QPalette::Base, halleffect[LOX_VNT] ? Qt::green : Qt::red);
	ui->hall_lox_status->setPalette(lox_palette);
	ui->hall_lox_status->setText( halleffect[LOX_VNT] ? "OPEN" : "CLOSED" );

	QPalette ch4_palette = ui->hall_ch4_status->palette();
	ch4_palette.setColor(QPalette::Base, halleffect[CH4_VNT] ? Qt::green : Qt::red);
	ui->hall_ch4_status->setPalette(ch4_palette);
	ui->hall_ch4_status->setText( halleffect[CH4_VNT] ? "OPEN" : "CLOSED" );
}

/**
 * @brief Main timer handler
 * @brief Runs whenever the main timer timeouts to run repeating tasks
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

void
mainwindow::on_boardSelectionComboBox_currentIndexChanged(int index) {
	board_selection = index;
}

/**
 * @brief Global Log Data Checkbox handler
 * @brief Triggered by state change of Log Data checkbox
 * @brief Initiates UART connection and opens log file
 * @see uart_init()
 * @see openFile()
 * @param[in] int new value of checkbox
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
		struct timespec spec;
		return;
	}
	log.closeFile();
}

/**
 * @brief Global Log Data Handler
 * @brief Logs data from static data array, with timestamp
 * @see appendData()
 */
void
mainwindow::logData(){
	std::chrono::milliseconds ms = std::chrono::duration_cast< std::chrono::milliseconds >(
			std::chrono::system_clock::now().time_since_epoch()
			);

	long time[] = {(long)ms.count()};

	getData();

	log.appendData(time, 1, 0);
	log.appendData(pressures, 5, 0);
	log.appendData(thermo, 1, 0);
	log.appendData(halleffect, 2, 0);
	log.appendData(battVoltage, 1, 1);
}

/**
 * @brief Data Retrieval Routine
 * @brief Recieves data from UART connection, updates static data array, and updates GUI to reflect changes
 * @see readMessage()
 * @see parseMessage()
 * @see updateData()
 */
void
mainwindow::getData(){
	struct daqSensors message;
	struct daqParsed readings;

	int n = readMessage(&message);
	if (n < 0){
		//serial_timeout++;
		return;
	}

	parsePressureMessage(&message, &readings, board_selection);

	pressures[CH4_READING] = readings.PT_methane;
	pressures[LOX_READING] = readings.PT_lox;
	pressures[HEL_READING] = readings.PT_helium;
	pressures[CBR_READING] = readings.PT_chamber;
	pressures[REG_READING] = readings.PT_heliumReg;
	halleffect[CH4_VNT]    = readings.HALL_methane;
	halleffect[LOX_VNT]    = readings.HALL_lox;
	thermo[UAF]            = readings.TC_uaf;
	battVoltage[0]         = readings.BATT_voltage;
	timestamp              = readings.timestamp;
	update_data();
}

/**
 * @brief Handler for live plot button
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
 * @brief Update plots with new data[] values
 */
void
mainwindow::updatePlots(){
	plot->appendData(pressures, &timestamp);
}
