/**
 * About Page Header
 *
 * @author Zack Mudd <zmudd@sdsu.edu>
 */

#ifndef ABOUT_H
#define ABOUT_H

#include <QMainWindow>

namespace Ui {
class about;
}

class about : public QMainWindow
{
    Q_OBJECT

public:
    explicit about(QWidget *parent = nullptr);
    ~about();

private:
    Ui::about *ui;
};

#endif // ABOUT_H
