#ifndef LIVEPLOT_H
#define LIVEPLOT_H

#include <QApplication>
#include <QMainWindow>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>

QT_CHARTS_USE_NAMESPACE

#define NUM_DATA_POINTS 600

namespace Ui {
class livePlot;
}

class livePlot : public QMainWindow
{
	Q_OBJECT

public:
    explicit livePlot(QWidget *parent = nullptr);
	~livePlot();
	
	void appendData(float*, uint32_t*);
	void setupPlot(void);

private:
	Ui::livePlot *ui;

	QLineSeries *ch4Series;
	QLineSeries *loxSeries;
	QLineSeries *helSeries;
	QLineSeries *cbrSeries;

	QChart *ch4Chart;
	QChart *loxChart;
	QChart *helChart;
	QChart *cbrChart;

	QChartView *ch4View;
	QChartView *loxView;
	QChartView *helView;
	QChartView *cbrView;
};

#endif // LIVEPLOT_H
