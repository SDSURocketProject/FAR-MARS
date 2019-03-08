/**
 * Generic Warning Popup Class
 *
 * @author Zack Mudd <zmudd@sdsu.edu>
 */
#include "warning.h"
#include "ui_warning.h"

/**
 * Warning class constructor
 */
warning::warning(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::warning)
{
    ui->setupUi(this);
}

/**
 * Warning class destructor
 */
warning::~warning()
{
    delete ui;
}

/**
 * Set text of warning popup
 *
 * @param QString text to display
 */
void
warning::setWarning(QString message){
    this->ui->warningtext->setText(message);
}
