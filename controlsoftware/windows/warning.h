#ifndef WARNING_H
#define WARNING_H

#include <QMainWindow>

namespace Ui {
class warning;
}

class warning : public QMainWindow
{
    Q_OBJECT

public:
    explicit warning(QWidget *parent = nullptr);
    ~warning();
    void setWarning(QString);

private:
    Ui::warning *ui;
};

#endif // WARNING_H
