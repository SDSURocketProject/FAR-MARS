/**
 * Whats New Window
 *
 * @author Zack Mudd <zmudd@sdsu.edu>
 */

#include "news.h"
#include "ui_news.h"

news::news(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::news)
{
    ui->setupUi(this);
}

news::~news()
{
    delete ui;
}
