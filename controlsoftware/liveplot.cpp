/**
 * Liveplot display window class
 * @author Zack Mudd <zmudd@sdsu.edu>
 */
#include "liveplot.h"
#include "ui_liveplot.h"

/**
 * Liveplot class constructor
 */
livePlot::livePlot(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::livePlot)
{
	ui->setupUi(this);
}

/**
 * Liveplot class destructor
 */
livePlot::~livePlot()
{
	delete ui;
}

void
livePlot::setupPlot(){
	ch4Series = new QLineSeries();
	loxSeries = new QLineSeries();
	helSeries = new QLineSeries();
	cbrSeries = new QLineSeries();

	ch4Chart = new QChart();
	loxChart = new QChart();
	helChart = new QChart();
	cbrChart = new QChart();

	ch4Chart->addSeries(ch4Series);
	loxChart->addSeries(loxSeries);
	helChart->addSeries(helSeries);
	cbrChart->addSeries(cbrSeries);

	ch4Chart->setTitle("Methane");
	loxChart->setTitle("LOX");
	helChart->setTitle("Helium");
	cbrChart->setTitle("Chamber Pressure");

	ch4Chart->createDefaultAxes();
	loxChart->createDefaultAxes();
	helChart->createDefaultAxes();
	cbrChart->createDefaultAxes();

	ch4Chart->axisY()->setMin(0.0);
	loxChart->axisY()->setMin(0.0);
	helChart->axisY()->setMin(0.0);
	cbrChart->axisY()->setMin(0.0);

	ch4Chart->axisY()->setMax(15.0);
	loxChart->axisY()->setMax(15.0);
	helChart->axisY()->setMax(30.0);
	cbrChart->axisY()->setMax(15.0);

	ch4Chart->legend()->hide();
	loxChart->legend()->hide();
	helChart->legend()->hide();
	cbrChart->legend()->hide();

	ch4View = new QChartView(ch4Chart);
	loxView = new QChartView(loxChart);
	helView = new QChartView(helChart);
	cbrView = new QChartView(cbrChart);

	/** Antialiasing causes a massive performance hit on my machine **/
	//ch4View->setRenderHint(QPainter::Antialiasing);
	//loxView->setRenderHint(QPainter::Antialiasing);
	//helView->setRenderHint(QPainter::Antialiasing);

	this->ui->chartDisplay->addWidget(ch4View);
	this->ui->chartDisplay->addWidget(loxView);
	this->ui->chartDisplay->addWidget(helView);
	this->ui->chartDisplay->addWidget(cbrView);
}

/**
 * Append data to graph, removing old data to keep length at NUM_DATA_POINTS
 * @param float* 3-index float array containing new values to append
 * @param uint32_t* timestamp to plot
 */
void
livePlot::appendData(float *data, uint32_t *timestamp){
	QPointF ch4Point(*timestamp, (int)data[0]);
	QPointF loxPoint(*timestamp, (int)data[1]);
	QPointF helPoint(*timestamp, (int)data[2]);
	QPointF cbrPoint(*timestamp, (int)data[3]);

	ch4Series->append(ch4Point);
	loxSeries->append(loxPoint);
	helSeries->append(helPoint);
	cbrSeries->append(cbrPoint);

	if (ch4Series->count() > 1200){
		ch4Series->remove(0);
		loxSeries->remove(0);
		helSeries->remove(0);
		cbrSeries->remove(0);
	}

	ch4Chart->removeSeries(ch4Series);
	loxChart->removeSeries(loxSeries);
	helChart->removeSeries(helSeries);
	cbrChart->removeSeries(cbrSeries);

	ch4Chart->addSeries(ch4Series);
	loxChart->addSeries(loxSeries);
	helChart->addSeries(helSeries);
	cbrChart->addSeries(cbrSeries);

	ch4Chart->createDefaultAxes();
	loxChart->createDefaultAxes();
	helChart->createDefaultAxes();
	cbrChart->createDefaultAxes();

	ch4Chart->axisY()->setMin(0.0);
	loxChart->axisY()->setMin(0.0);
	helChart->axisY()->setMin(0.0);
	cbrChart->axisY()->setMin(0.0);

	if ((int)data[0] > 15 && (int)data[0] > ch4Max){
	    ch4Chart->axisY()->setMax((int)data[0]);
	    ch4Max = (int)data[0];
	} else {
	    ch4Chart->axisY()->setMax(15.0);
	}

	if ((int)data[1] > 15 && (int)data[1] > loxMax){
	    loxChart->axisY()->setMax((int)data[1]);
	    loxMax = (int)data[1];
	} else {
	    loxChart->axisY()->setMax(15.0);
	}

	if ((int)data[2] > 30 && (int)data[2] > helMax){
	    helChart->axisY()->setMax((int)data[2]);
	    helMax = (int)data[2];
	} else {
	    helChart->axisY()->setMax(30.0);
	}

	if ((int)data[3] > 15 && (int)data[3] > cbrMax){
	    cbrChart->axisY()->setMax((int)data[3]);
	    cbrMax = (int)data[3];
	} else {
	    cbrChart->axisY()->setMax(15.0);
	}

	ch4View->repaint();
	loxView->repaint();
	helView->repaint();
	cbrView->repaint();
}
