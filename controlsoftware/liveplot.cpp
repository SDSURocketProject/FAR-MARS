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

	ch4Chart = new QChart();
	loxChart = new QChart();
	helChart = new QChart();

	ch4Chart->addSeries(ch4Series);
	loxChart->addSeries(loxSeries);
	helChart->addSeries(helSeries);

	ch4Chart->setTitle("Methane");
	loxChart->setTitle("LOX");
	helChart->setTitle("Helium");

	ch4Chart->createDefaultAxes();
	loxChart->createDefaultAxes();
	helChart->createDefaultAxes();

	ch4Chart->axisY()->setMin(0.0);
	loxChart->axisY()->setMin(0.0);
	helChart->axisY()->setMin(0.0);

	ch4Chart->legend()->hide();
	loxChart->legend()->hide();
	helChart->legend()->hide();

	ch4View = new QChartView(ch4Chart);
	loxView = new QChartView(loxChart);
	helView = new QChartView(helChart);

	/** Antialiasing causes a massive performance hit on my machine **/
	//ch4View->setRenderHint(QPainter::Antialiasing);
	//loxView->setRenderHint(QPainter::Antialiasing);
	//helView->setRenderHint(QPainter::Antialiasing);

	this->ui->chartDisplay->addWidget(ch4View);
	this->ui->chartDisplay->addWidget(loxView);
	this->ui->chartDisplay->addWidget(helView);
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

	ch4Series->append(ch4Point);
	loxSeries->append(loxPoint);
	helSeries->append(helPoint);

	if ((double)data[0] > ch4Max){
		ch4Max = (double)data[0];
	}
	if ((double)data[1] > loxMax){
		loxMax = (double)data[1];
	}
	if ((double)data[2] > helMax){
		helMax = (double)data[2];
	}

	if (ch4Series->count() > 1200){
		ch4Series->remove(0);
		loxSeries->remove(0);
		helSeries->remove(0);
	}

	ch4Chart->removeSeries(ch4Series);
	loxChart->removeSeries(loxSeries);
	helChart->removeSeries(helSeries);

	ch4Chart->addSeries(ch4Series);
	loxChart->addSeries(loxSeries);
	helChart->addSeries(helSeries);

	ch4Chart->createDefaultAxes();
	loxChart->createDefaultAxes();
	helChart->createDefaultAxes();

	ch4Chart->axisY()->setMin(0.0);
	loxChart->axisY()->setMin(0.0);
	helChart->axisY()->setMin(0.0);

	ch4View->repaint();
	loxView->repaint();
	helView->repaint();
}
