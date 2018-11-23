/********************************************************************************
** Form generated from reading UI file 'about.ui'
**
** Created by: Qt User Interface Compiler version 5.11.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ABOUT_H
#define UI_ABOUT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_about
{
public:
    QAction *actionAbout;
    QAction *actionExit;
    QWidget *centralWidget;
    QLabel *label_9;
    QLabel *label_10;
    QLabel *label_11;
    QWidget *layoutWidget;
    QGridLayout *gridLayout;
    QLabel *label;
    QLabel *label_6;
    QLabel *label_2;
    QLabel *label_5;
    QLabel *label_4;
    QLabel *label_7;
    QLabel *label_3;
    QLabel *label_8;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *about)
    {
        if (about->objectName().isEmpty())
            about->setObjectName(QStringLiteral("about"));
        about->resize(200, 300);
        about->setMinimumSize(QSize(200, 300));
        about->setMaximumSize(QSize(200, 300));
        actionAbout = new QAction(about);
        actionAbout->setObjectName(QStringLiteral("actionAbout"));
        actionExit = new QAction(about);
        actionExit->setObjectName(QStringLiteral("actionExit"));
        centralWidget = new QWidget(about);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        label_9 = new QLabel(centralWidget);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setGeometry(QRect(10, 20, 181, 41));
        QFont font;
        font.setPointSize(19);
        label_9->setFont(font);
        label_9->setAlignment(Qt::AlignCenter);
        label_10 = new QLabel(centralWidget);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setGeometry(QRect(10, 60, 181, 41));
        QFont font1;
        font1.setPointSize(11);
        label_10->setFont(font1);
        label_10->setAlignment(Qt::AlignCenter);
        label_11 = new QLabel(centralWidget);
        label_11->setObjectName(QStringLiteral("label_11"));
        label_11->setGeometry(QRect(10, 100, 181, 41));
        label_11->setFont(font1);
        label_11->setAlignment(Qt::AlignCenter);
        layoutWidget = new QWidget(centralWidget);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 150, 181, 101));
        gridLayout = new QGridLayout(layoutWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(layoutWidget);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        label_6 = new QLabel(layoutWidget);
        label_6->setObjectName(QStringLiteral("label_6"));

        gridLayout->addWidget(label_6, 0, 1, 1, 1);

        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        label_5 = new QLabel(layoutWidget);
        label_5->setObjectName(QStringLiteral("label_5"));

        gridLayout->addWidget(label_5, 1, 1, 1, 1);

        label_4 = new QLabel(layoutWidget);
        label_4->setObjectName(QStringLiteral("label_4"));

        gridLayout->addWidget(label_4, 2, 0, 1, 1);

        label_7 = new QLabel(layoutWidget);
        label_7->setObjectName(QStringLiteral("label_7"));

        gridLayout->addWidget(label_7, 2, 1, 1, 1);

        label_3 = new QLabel(layoutWidget);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout->addWidget(label_3, 3, 0, 1, 1);

        label_8 = new QLabel(layoutWidget);
        label_8->setObjectName(QStringLiteral("label_8"));

        gridLayout->addWidget(label_8, 3, 1, 1, 1);

        about->setCentralWidget(centralWidget);
        mainToolBar = new QToolBar(about);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        about->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(about);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        about->setStatusBar(statusBar);

        retranslateUi(about);
        QObject::connect(actionExit, SIGNAL(triggered()), about, SLOT(close()));

        QMetaObject::connectSlotsByName(about);
    } // setupUi

    void retranslateUi(QMainWindow *about)
    {
        about->setWindowTitle(QApplication::translate("about", "About", nullptr));
        actionAbout->setText(QApplication::translate("about", "&About", nullptr));
        actionExit->setText(QApplication::translate("about", "&Exit", nullptr));
        label_9->setText(QApplication::translate("about", "Lady Elizabeth", nullptr));
        label_10->setText(QApplication::translate("about", "Launch Control Software", nullptr));
        label_11->setText(QApplication::translate("about", "SDSU Rocket Project", nullptr));
        label->setText(QApplication::translate("about", "Version", nullptr));
        label_6->setText(QApplication::translate("about", "v0.1.0", nullptr));
        label_2->setText(QApplication::translate("about", "Release", nullptr));
        label_5->setText(QApplication::translate("about", "2018.11.22", nullptr));
        label_4->setText(QApplication::translate("about", "License", nullptr));
        label_7->setText(QApplication::translate("about", "None", nullptr));
        label_3->setText(QApplication::translate("about", "Contact", nullptr));
        label_8->setText(QApplication::translate("about", "alefir@cock.li", nullptr));
    } // retranslateUi

};

namespace Ui {
    class about: public Ui_about {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ABOUT_H
