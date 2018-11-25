/********************************************************************************
** Form generated from reading UI file 'warning.ui'
**
** Created by: Qt User Interface Compiler version 5.11.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WARNING_H
#define UI_WARNING_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_warning
{
public:
    QAction *actionAbout;
    QAction *actionExit;
    QWidget *centralWidget;
    QLabel *Header;
    QLabel *warningtext;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *warning)
    {
        if (warning->objectName().isEmpty())
            warning->setObjectName(QStringLiteral("warning"));
        warning->resize(1000, 300);
        warning->setMinimumSize(QSize(200, 300));
        warning->setMaximumSize(QSize(1000, 300));
        actionAbout = new QAction(warning);
        actionAbout->setObjectName(QStringLiteral("actionAbout"));
        actionExit = new QAction(warning);
        actionExit->setObjectName(QStringLiteral("actionExit"));
        centralWidget = new QWidget(warning);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        Header = new QLabel(centralWidget);
        Header->setObjectName(QStringLiteral("Header"));
        Header->setGeometry(QRect(0, 10, 181, 41));
        QFont font;
        font.setPointSize(19);
        Header->setFont(font);
        Header->setAlignment(Qt::AlignCenter);
        warningtext = new QLabel(centralWidget);
        warningtext->setObjectName(QStringLiteral("warningtext"));
        warningtext->setGeometry(QRect(0, 70, 1001, 211));
        warningtext->setFont(font);
        warningtext->setAlignment(Qt::AlignCenter);
        warning->setCentralWidget(centralWidget);
        mainToolBar = new QToolBar(warning);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        warning->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(warning);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        warning->setStatusBar(statusBar);

        retranslateUi(warning);
        QObject::connect(actionExit, SIGNAL(triggered()), warning, SLOT(close()));

        QMetaObject::connectSlotsByName(warning);
    } // setupUi

    void retranslateUi(QMainWindow *warning)
    {
        warning->setWindowTitle(QApplication::translate("warning", "About", nullptr));
        actionAbout->setText(QApplication::translate("warning", "&About", nullptr));
        actionExit->setText(QApplication::translate("warning", "&Exit", nullptr));
        Header->setText(QApplication::translate("warning", "WARNING!", nullptr));
        warningtext->setText(QApplication::translate("warning", "WARNING!", nullptr));
    } // retranslateUi

};

namespace Ui {
    class warning: public Ui_warning {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WARNING_H
