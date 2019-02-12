/**
 * Whats New Window
 *
 * @author Zack Mudd <zmudd@sdsu.edu>
 */

#include "news.h"
#include "ui_news.h"

/**
 * News constructor
 * 
 * @param QWidget* Parent object
 */
news::news(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::news)
{
    ui->setupUi(this);
}

/**
 * News destructor
 */
news::~news()
{
    delete ui;
}
