/**
 *  About Page
 *
 *  @author Zack Mudd <zmudd@sdsu.edu>
 */


#include "about.h"
#include "ui_about.h"

/**
 * About Class Constructor
 */
about::about(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::about)
{
    ui->setupUi(this);
}

/**
 * About Class Destructor
 */
about::~about()
{
    delete ui;
}
