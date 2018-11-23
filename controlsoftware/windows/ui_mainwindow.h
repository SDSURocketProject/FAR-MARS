/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.11.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDial>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_mainwindow
{
public:
    QAction *actionExit;
    QAction *actionAbout;
    QAction *actionFullscreen;
    QAction *actionMinimize;
    QAction *actionWhats_New;
    QWidget *centralWidget;
    QPushButton *rand_thermo;
    QWidget *layoutWidget;
    QGridLayout *thermos;
    QLCDNumber *thermo2lcd;
    QLCDNumber *thermo7lcd;
    QLCDNumber *thermo4lcd;
    QLCDNumber *thermo5lcd;
    QLCDNumber *thermo1lcd;
    QProgressBar *thermo1;
    QLCDNumber *thermo8lcd;
    QProgressBar *thermo4;
    QProgressBar *thermo3;
    QLCDNumber *thermo6lcd;
    QLCDNumber *thermo3lcd;
    QProgressBar *thermo8;
    QProgressBar *thermo6;
    QProgressBar *thermo7;
    QProgressBar *thermo5;
    QProgressBar *thermo2;
    QWidget *layoutWidget1;
    QVBoxLayout *verticalLayout;
    QLineEdit *warningtext;
    QPushButton *displaywarning;
    QDial *ducer1;
    QDial *ducer2;
    QLCDNumber *ducer1lcd;
    QLCDNumber *ducer2lcd;
    QWidget *widget;
    QVBoxLayout *verticalLayout_2;
    QPushButton *rand_pres;
    QCheckBox *checkBox;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuEdit;
    QMenu *menuTools;
    QMenu *menuWindow;
    QMenu *menuHelp;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *mainwindow)
    {
        if (mainwindow->objectName().isEmpty())
            mainwindow->setObjectName(QStringLiteral("mainwindow"));
        mainwindow->resize(1280, 720);
        actionExit = new QAction(mainwindow);
        actionExit->setObjectName(QStringLiteral("actionExit"));
        actionAbout = new QAction(mainwindow);
        actionAbout->setObjectName(QStringLiteral("actionAbout"));
        actionFullscreen = new QAction(mainwindow);
        actionFullscreen->setObjectName(QStringLiteral("actionFullscreen"));
        actionMinimize = new QAction(mainwindow);
        actionMinimize->setObjectName(QStringLiteral("actionMinimize"));
        actionWhats_New = new QAction(mainwindow);
        actionWhats_New->setObjectName(QStringLiteral("actionWhats_New"));
        centralWidget = new QWidget(mainwindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        rand_thermo = new QPushButton(centralWidget);
        rand_thermo->setObjectName(QStringLiteral("rand_thermo"));
        rand_thermo->setGeometry(QRect(200, 170, 181, 34));
        layoutWidget = new QWidget(centralWidget);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 11, 588, 122));
        thermos = new QGridLayout(layoutWidget);
        thermos->setSpacing(6);
        thermos->setContentsMargins(11, 11, 11, 11);
        thermos->setObjectName(QStringLiteral("thermos"));
        thermos->setContentsMargins(0, 0, 0, 0);
        thermo2lcd = new QLCDNumber(layoutWidget);
        thermo2lcd->setObjectName(QStringLiteral("thermo2lcd"));
        QPalette palette;
        QBrush brush(QColor(170, 0, 0, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Active, QPalette::Light, brush);
        QBrush brush1(QColor(255, 0, 0, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Text, brush1);
        palette.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Light, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Text, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        QBrush brush2(QColor(56, 59, 66, 255));
        brush2.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Disabled, QPalette::WindowText, brush2);
        palette.setBrush(QPalette::Disabled, QPalette::Light, brush);
        QBrush brush3(QColor(48, 51, 58, 255));
        brush3.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Disabled, QPalette::Text, brush3);
        QBrush brush4(QColor(49, 54, 67, 255));
        brush4.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Disabled, QPalette::ButtonText, brush4);
        thermo2lcd->setPalette(palette);

        thermos->addWidget(thermo2lcd, 1, 1, 1, 1);

        thermo7lcd = new QLCDNumber(layoutWidget);
        thermo7lcd->setObjectName(QStringLiteral("thermo7lcd"));
        QPalette palette1;
        palette1.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette1.setBrush(QPalette::Active, QPalette::Light, brush);
        palette1.setBrush(QPalette::Active, QPalette::Text, brush1);
        palette1.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::Light, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::Text, brush1);
        palette1.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        palette1.setBrush(QPalette::Disabled, QPalette::WindowText, brush2);
        palette1.setBrush(QPalette::Disabled, QPalette::Light, brush);
        palette1.setBrush(QPalette::Disabled, QPalette::Text, brush3);
        palette1.setBrush(QPalette::Disabled, QPalette::ButtonText, brush4);
        thermo7lcd->setPalette(palette1);

        thermos->addWidget(thermo7lcd, 1, 6, 1, 1);

        thermo4lcd = new QLCDNumber(layoutWidget);
        thermo4lcd->setObjectName(QStringLiteral("thermo4lcd"));
        QPalette palette2;
        palette2.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette2.setBrush(QPalette::Active, QPalette::Light, brush);
        palette2.setBrush(QPalette::Active, QPalette::Text, brush1);
        palette2.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        palette2.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette2.setBrush(QPalette::Inactive, QPalette::Light, brush);
        palette2.setBrush(QPalette::Inactive, QPalette::Text, brush1);
        palette2.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        palette2.setBrush(QPalette::Disabled, QPalette::WindowText, brush2);
        palette2.setBrush(QPalette::Disabled, QPalette::Light, brush);
        palette2.setBrush(QPalette::Disabled, QPalette::Text, brush3);
        palette2.setBrush(QPalette::Disabled, QPalette::ButtonText, brush4);
        thermo4lcd->setPalette(palette2);

        thermos->addWidget(thermo4lcd, 1, 3, 1, 1);

        thermo5lcd = new QLCDNumber(layoutWidget);
        thermo5lcd->setObjectName(QStringLiteral("thermo5lcd"));
        QPalette palette3;
        palette3.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette3.setBrush(QPalette::Active, QPalette::Light, brush);
        palette3.setBrush(QPalette::Active, QPalette::Text, brush1);
        palette3.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        palette3.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette3.setBrush(QPalette::Inactive, QPalette::Light, brush);
        palette3.setBrush(QPalette::Inactive, QPalette::Text, brush1);
        palette3.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        palette3.setBrush(QPalette::Disabled, QPalette::WindowText, brush2);
        palette3.setBrush(QPalette::Disabled, QPalette::Light, brush);
        palette3.setBrush(QPalette::Disabled, QPalette::Text, brush3);
        palette3.setBrush(QPalette::Disabled, QPalette::ButtonText, brush4);
        thermo5lcd->setPalette(palette3);

        thermos->addWidget(thermo5lcd, 1, 4, 1, 1);

        thermo1lcd = new QLCDNumber(layoutWidget);
        thermo1lcd->setObjectName(QStringLiteral("thermo1lcd"));
        QPalette palette4;
        palette4.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette4.setBrush(QPalette::Active, QPalette::Light, brush);
        palette4.setBrush(QPalette::Active, QPalette::Text, brush1);
        palette4.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        palette4.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette4.setBrush(QPalette::Inactive, QPalette::Light, brush);
        palette4.setBrush(QPalette::Inactive, QPalette::Text, brush1);
        palette4.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        palette4.setBrush(QPalette::Disabled, QPalette::WindowText, brush2);
        palette4.setBrush(QPalette::Disabled, QPalette::Light, brush);
        palette4.setBrush(QPalette::Disabled, QPalette::Text, brush3);
        palette4.setBrush(QPalette::Disabled, QPalette::ButtonText, brush4);
        thermo1lcd->setPalette(palette4);

        thermos->addWidget(thermo1lcd, 1, 0, 1, 1);

        thermo1 = new QProgressBar(layoutWidget);
        thermo1->setObjectName(QStringLiteral("thermo1"));
        thermo1->setValue(24);
        thermo1->setAlignment(Qt::AlignBottom|Qt::AlignJustify);
        thermo1->setTextVisible(true);
        thermo1->setOrientation(Qt::Vertical);
        thermo1->setInvertedAppearance(false);
        thermo1->setTextDirection(QProgressBar::BottomToTop);

        thermos->addWidget(thermo1, 0, 0, 1, 1);

        thermo8lcd = new QLCDNumber(layoutWidget);
        thermo8lcd->setObjectName(QStringLiteral("thermo8lcd"));
        QPalette palette5;
        palette5.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette5.setBrush(QPalette::Active, QPalette::Light, brush);
        palette5.setBrush(QPalette::Active, QPalette::Text, brush1);
        palette5.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        palette5.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette5.setBrush(QPalette::Inactive, QPalette::Light, brush);
        palette5.setBrush(QPalette::Inactive, QPalette::Text, brush1);
        palette5.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        palette5.setBrush(QPalette::Disabled, QPalette::WindowText, brush2);
        palette5.setBrush(QPalette::Disabled, QPalette::Light, brush);
        palette5.setBrush(QPalette::Disabled, QPalette::Text, brush3);
        palette5.setBrush(QPalette::Disabled, QPalette::ButtonText, brush4);
        thermo8lcd->setPalette(palette5);

        thermos->addWidget(thermo8lcd, 1, 7, 1, 1);

        thermo4 = new QProgressBar(layoutWidget);
        thermo4->setObjectName(QStringLiteral("thermo4"));
        thermo4->setValue(24);
        thermo4->setAlignment(Qt::AlignBottom|Qt::AlignJustify);
        thermo4->setTextVisible(true);
        thermo4->setOrientation(Qt::Vertical);
        thermo4->setInvertedAppearance(false);
        thermo4->setTextDirection(QProgressBar::BottomToTop);

        thermos->addWidget(thermo4, 0, 3, 1, 1);

        thermo3 = new QProgressBar(layoutWidget);
        thermo3->setObjectName(QStringLiteral("thermo3"));
        thermo3->setValue(24);
        thermo3->setAlignment(Qt::AlignBottom|Qt::AlignJustify);
        thermo3->setTextVisible(true);
        thermo3->setOrientation(Qt::Vertical);
        thermo3->setInvertedAppearance(false);
        thermo3->setTextDirection(QProgressBar::BottomToTop);

        thermos->addWidget(thermo3, 0, 2, 1, 1);

        thermo6lcd = new QLCDNumber(layoutWidget);
        thermo6lcd->setObjectName(QStringLiteral("thermo6lcd"));
        QPalette palette6;
        palette6.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette6.setBrush(QPalette::Active, QPalette::Light, brush);
        palette6.setBrush(QPalette::Active, QPalette::Text, brush1);
        palette6.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        palette6.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette6.setBrush(QPalette::Inactive, QPalette::Light, brush);
        palette6.setBrush(QPalette::Inactive, QPalette::Text, brush1);
        palette6.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        palette6.setBrush(QPalette::Disabled, QPalette::WindowText, brush2);
        palette6.setBrush(QPalette::Disabled, QPalette::Light, brush);
        palette6.setBrush(QPalette::Disabled, QPalette::Text, brush3);
        palette6.setBrush(QPalette::Disabled, QPalette::ButtonText, brush4);
        thermo6lcd->setPalette(palette6);

        thermos->addWidget(thermo6lcd, 1, 5, 1, 1);

        thermo3lcd = new QLCDNumber(layoutWidget);
        thermo3lcd->setObjectName(QStringLiteral("thermo3lcd"));
        QPalette palette7;
        palette7.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette7.setBrush(QPalette::Active, QPalette::Light, brush);
        palette7.setBrush(QPalette::Active, QPalette::Text, brush1);
        palette7.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        palette7.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette7.setBrush(QPalette::Inactive, QPalette::Light, brush);
        palette7.setBrush(QPalette::Inactive, QPalette::Text, brush1);
        palette7.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        palette7.setBrush(QPalette::Disabled, QPalette::WindowText, brush2);
        palette7.setBrush(QPalette::Disabled, QPalette::Light, brush);
        palette7.setBrush(QPalette::Disabled, QPalette::Text, brush3);
        palette7.setBrush(QPalette::Disabled, QPalette::ButtonText, brush4);
        thermo3lcd->setPalette(palette7);

        thermos->addWidget(thermo3lcd, 1, 2, 1, 1);

        thermo8 = new QProgressBar(layoutWidget);
        thermo8->setObjectName(QStringLiteral("thermo8"));
        thermo8->setValue(24);
        thermo8->setAlignment(Qt::AlignBottom|Qt::AlignJustify);
        thermo8->setTextVisible(true);
        thermo8->setOrientation(Qt::Vertical);
        thermo8->setInvertedAppearance(false);
        thermo8->setTextDirection(QProgressBar::BottomToTop);

        thermos->addWidget(thermo8, 0, 7, 1, 1);

        thermo6 = new QProgressBar(layoutWidget);
        thermo6->setObjectName(QStringLiteral("thermo6"));
        thermo6->setValue(24);
        thermo6->setAlignment(Qt::AlignBottom|Qt::AlignJustify);
        thermo6->setTextVisible(true);
        thermo6->setOrientation(Qt::Vertical);
        thermo6->setInvertedAppearance(false);
        thermo6->setTextDirection(QProgressBar::BottomToTop);

        thermos->addWidget(thermo6, 0, 5, 1, 1);

        thermo7 = new QProgressBar(layoutWidget);
        thermo7->setObjectName(QStringLiteral("thermo7"));
        thermo7->setValue(24);
        thermo7->setAlignment(Qt::AlignBottom|Qt::AlignJustify);
        thermo7->setTextVisible(true);
        thermo7->setOrientation(Qt::Vertical);
        thermo7->setInvertedAppearance(false);
        thermo7->setTextDirection(QProgressBar::BottomToTop);

        thermos->addWidget(thermo7, 0, 6, 1, 1);

        thermo5 = new QProgressBar(layoutWidget);
        thermo5->setObjectName(QStringLiteral("thermo5"));
        thermo5->setValue(24);
        thermo5->setAlignment(Qt::AlignBottom|Qt::AlignJustify);
        thermo5->setTextVisible(true);
        thermo5->setOrientation(Qt::Vertical);
        thermo5->setInvertedAppearance(false);
        thermo5->setTextDirection(QProgressBar::BottomToTop);

        thermos->addWidget(thermo5, 0, 4, 1, 1);

        thermo2 = new QProgressBar(layoutWidget);
        thermo2->setObjectName(QStringLiteral("thermo2"));
        thermo2->setValue(24);
        thermo2->setAlignment(Qt::AlignBottom|Qt::AlignJustify);
        thermo2->setTextVisible(true);
        thermo2->setOrientation(Qt::Vertical);
        thermo2->setInvertedAppearance(false);
        thermo2->setTextDirection(QProgressBar::BottomToTop);

        thermos->addWidget(thermo2, 0, 1, 1, 1);

        layoutWidget1 = new QWidget(centralWidget);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(10, 260, 351, 74));
        verticalLayout = new QVBoxLayout(layoutWidget1);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        warningtext = new QLineEdit(layoutWidget1);
        warningtext->setObjectName(QStringLiteral("warningtext"));

        verticalLayout->addWidget(warningtext);

        displaywarning = new QPushButton(layoutWidget1);
        displaywarning->setObjectName(QStringLiteral("displaywarning"));

        verticalLayout->addWidget(displaywarning);

        ducer1 = new QDial(centralWidget);
        ducer1->setObjectName(QStringLiteral("ducer1"));
        ducer1->setGeometry(QRect(1071, 11, 200, 200));
        ducer1->setTracking(false);
        ducer1->setNotchesVisible(true);
        ducer2 = new QDial(centralWidget);
        ducer2->setObjectName(QStringLiteral("ducer2"));
        ducer2->setGeometry(QRect(1071, 204, 200, 200));
#ifndef QT_NO_ACCESSIBILITY
        ducer2->setAccessibleName(QStringLiteral(""));
#endif // QT_NO_ACCESSIBILITY
        ducer2->setTracking(false);
        ducer2->setNotchesVisible(true);
        ducer1lcd = new QLCDNumber(centralWidget);
        ducer1lcd->setObjectName(QStringLiteral("ducer1lcd"));
        ducer1lcd->setGeometry(QRect(1140, 100, 64, 23));
        QPalette palette8;
        palette8.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette8.setBrush(QPalette::Active, QPalette::Light, brush);
        palette8.setBrush(QPalette::Active, QPalette::Text, brush1);
        palette8.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        palette8.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette8.setBrush(QPalette::Inactive, QPalette::Light, brush);
        palette8.setBrush(QPalette::Inactive, QPalette::Text, brush1);
        palette8.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        palette8.setBrush(QPalette::Disabled, QPalette::WindowText, brush2);
        palette8.setBrush(QPalette::Disabled, QPalette::Light, brush);
        palette8.setBrush(QPalette::Disabled, QPalette::Text, brush3);
        palette8.setBrush(QPalette::Disabled, QPalette::ButtonText, brush4);
        ducer1lcd->setPalette(palette8);
        ducer2lcd = new QLCDNumber(centralWidget);
        ducer2lcd->setObjectName(QStringLiteral("ducer2lcd"));
        ducer2lcd->setGeometry(QRect(1140, 300, 64, 23));
        QPalette palette9;
        palette9.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette9.setBrush(QPalette::Active, QPalette::Light, brush);
        palette9.setBrush(QPalette::Active, QPalette::Text, brush1);
        palette9.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        palette9.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette9.setBrush(QPalette::Inactive, QPalette::Light, brush);
        palette9.setBrush(QPalette::Inactive, QPalette::Text, brush1);
        palette9.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        palette9.setBrush(QPalette::Disabled, QPalette::WindowText, brush2);
        palette9.setBrush(QPalette::Disabled, QPalette::Light, brush);
        palette9.setBrush(QPalette::Disabled, QPalette::Text, brush3);
        palette9.setBrush(QPalette::Disabled, QPalette::ButtonText, brush4);
        ducer2lcd->setPalette(palette9);
        widget = new QWidget(centralWidget);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(860, 190, 216, 64));
        verticalLayout_2 = new QVBoxLayout(widget);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        rand_pres = new QPushButton(widget);
        rand_pres->setObjectName(QStringLiteral("rand_pres"));

        verticalLayout_2->addWidget(rand_pres);

        checkBox = new QCheckBox(widget);
        checkBox->setObjectName(QStringLiteral("checkBox"));

        verticalLayout_2->addWidget(checkBox);

        mainwindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(mainwindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1280, 30));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menuEdit = new QMenu(menuBar);
        menuEdit->setObjectName(QStringLiteral("menuEdit"));
        menuTools = new QMenu(menuBar);
        menuTools->setObjectName(QStringLiteral("menuTools"));
        menuWindow = new QMenu(menuBar);
        menuWindow->setObjectName(QStringLiteral("menuWindow"));
        menuHelp = new QMenu(menuBar);
        menuHelp->setObjectName(QStringLiteral("menuHelp"));
        mainwindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(mainwindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        mainwindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(mainwindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        mainwindow->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuEdit->menuAction());
        menuBar->addAction(menuTools->menuAction());
        menuBar->addAction(menuWindow->menuAction());
        menuBar->addAction(menuHelp->menuAction());
        menuFile->addAction(actionExit);
        menuWindow->addAction(actionFullscreen);
        menuWindow->addAction(actionMinimize);
        menuHelp->addAction(actionAbout);
        menuHelp->addAction(actionWhats_New);

        retranslateUi(mainwindow);
        QObject::connect(actionExit, SIGNAL(triggered()), mainwindow, SLOT(close()));
        QObject::connect(actionFullscreen, SIGNAL(triggered()), mainwindow, SLOT(showFullScreen()));
        QObject::connect(actionMinimize, SIGNAL(triggered()), mainwindow, SLOT(hide()));

        QMetaObject::connectSlotsByName(mainwindow);
    } // setupUi

    void retranslateUi(QMainWindow *mainwindow)
    {
        mainwindow->setWindowTitle(QApplication::translate("mainwindow", "Lady Elizabeth Control Software", nullptr));
        actionExit->setText(QApplication::translate("mainwindow", "&Exit", nullptr));
        actionAbout->setText(QApplication::translate("mainwindow", "&About", nullptr));
        actionFullscreen->setText(QApplication::translate("mainwindow", "Fullscreen", nullptr));
        actionMinimize->setText(QApplication::translate("mainwindow", "Minimize", nullptr));
        actionWhats_New->setText(QApplication::translate("mainwindow", "Whats New?", nullptr));
        rand_thermo->setText(QApplication::translate("mainwindow", "Randomize Thermocuples", nullptr));
        thermo1->setFormat(QApplication::translate("mainwindow", "%p", nullptr));
        thermo4->setFormat(QApplication::translate("mainwindow", "%p", nullptr));
        thermo3->setFormat(QApplication::translate("mainwindow", "%p", nullptr));
        thermo8->setFormat(QApplication::translate("mainwindow", "%p", nullptr));
        thermo6->setFormat(QApplication::translate("mainwindow", "%p", nullptr));
        thermo7->setFormat(QApplication::translate("mainwindow", "%p", nullptr));
        thermo5->setFormat(QApplication::translate("mainwindow", "%p", nullptr));
        thermo2->setFormat(QApplication::translate("mainwindow", "%p", nullptr));
        warningtext->setText(QApplication::translate("mainwindow", "General Warning", nullptr));
        displaywarning->setText(QApplication::translate("mainwindow", "Display Warning", nullptr));
        rand_pres->setText(QApplication::translate("mainwindow", "Randomize Pressure Transducers", nullptr));
        checkBox->setText(QApplication::translate("mainwindow", "Disable Ducer Warning", nullptr));
        menuFile->setTitle(QApplication::translate("mainwindow", "Fi&le", nullptr));
        menuEdit->setTitle(QApplication::translate("mainwindow", "Edit", nullptr));
        menuTools->setTitle(QApplication::translate("mainwindow", "Tool&s", nullptr));
        menuWindow->setTitle(QApplication::translate("mainwindow", "Wi&ndow", nullptr));
        menuHelp->setTitle(QApplication::translate("mainwindow", "Help", nullptr));
    } // retranslateUi

};

namespace Ui {
    class mainwindow: public Ui_mainwindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
