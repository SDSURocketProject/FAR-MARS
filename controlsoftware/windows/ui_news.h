/********************************************************************************
** Form generated from reading UI file 'news.ui'
**
** Created by: Qt User Interface Compiler version 5.11.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NEWS_H
#define UI_NEWS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_news
{
public:
    QAction *actionAbout;
    QAction *actionExit;
    QWidget *centralWidget;
    QLabel *label_9;
    QLabel *label_10;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QTreeWidget *treeWidget;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *news)
    {
        if (news->objectName().isEmpty())
            news->setObjectName(QStringLiteral("news"));
        news->resize(350, 550);
        news->setMinimumSize(QSize(200, 300));
        news->setMaximumSize(QSize(16777215, 16777215));
        actionAbout = new QAction(news);
        actionAbout->setObjectName(QStringLiteral("actionAbout"));
        actionExit = new QAction(news);
        actionExit->setObjectName(QStringLiteral("actionExit"));
        centralWidget = new QWidget(news);
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
        scrollArea = new QScrollArea(centralWidget);
        scrollArea->setObjectName(QStringLiteral("scrollArea"));
        scrollArea->setGeometry(QRect(19, 143, 311, 371));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QStringLiteral("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 307, 367));
        treeWidget = new QTreeWidget(scrollAreaWidgetContents);
        new QTreeWidgetItem(treeWidget);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem(treeWidget);
        new QTreeWidgetItem(__qtreewidgetitem);
        new QTreeWidgetItem(__qtreewidgetitem);
        new QTreeWidgetItem(__qtreewidgetitem);
        new QTreeWidgetItem(__qtreewidgetitem);
        new QTreeWidgetItem(__qtreewidgetitem);
        new QTreeWidgetItem(__qtreewidgetitem);
        new QTreeWidgetItem(__qtreewidgetitem);
        treeWidget->setObjectName(QStringLiteral("treeWidget"));
        treeWidget->setGeometry(QRect(0, 0, 311, 371));
        scrollArea->setWidget(scrollAreaWidgetContents);
        news->setCentralWidget(centralWidget);
        mainToolBar = new QToolBar(news);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        news->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(news);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        news->setStatusBar(statusBar);

        retranslateUi(news);
        QObject::connect(actionExit, SIGNAL(triggered()), news, SLOT(close()));

        QMetaObject::connectSlotsByName(news);
    } // setupUi

    void retranslateUi(QMainWindow *news)
    {
        news->setWindowTitle(QApplication::translate("news", "About", nullptr));
        actionAbout->setText(QApplication::translate("news", "&About", nullptr));
        actionExit->setText(QApplication::translate("news", "&Exit", nullptr));
        label_9->setText(QApplication::translate("news", "Release Notes", nullptr));
        label_10->setText(QApplication::translate("news", "Whats new is this release", nullptr));
        QTreeWidgetItem *___qtreewidgetitem = treeWidget->headerItem();
        ___qtreewidgetitem->setText(0, QApplication::translate("news", "v0.1.0", nullptr));

        const bool __sortingEnabled = treeWidget->isSortingEnabled();
        treeWidget->setSortingEnabled(false);
        QTreeWidgetItem *___qtreewidgetitem1 = treeWidget->topLevelItem(0);
        ___qtreewidgetitem1->setText(0, QApplication::translate("news", "Initial Release", nullptr));
        QTreeWidgetItem *___qtreewidgetitem2 = treeWidget->topLevelItem(1);
        ___qtreewidgetitem2->setText(0, QApplication::translate("news", "Basic Functionalities for testing", nullptr));
        QTreeWidgetItem *___qtreewidgetitem3 = ___qtreewidgetitem2->child(0);
        ___qtreewidgetitem3->setText(0, QApplication::translate("news", "Menu Bar", nullptr));
        QTreeWidgetItem *___qtreewidgetitem4 = ___qtreewidgetitem2->child(1);
        ___qtreewidgetitem4->setText(0, QApplication::translate("news", "About Menu", nullptr));
        QTreeWidgetItem *___qtreewidgetitem5 = ___qtreewidgetitem2->child(2);
        ___qtreewidgetitem5->setText(0, QApplication::translate("news", "News Menu", nullptr));
        QTreeWidgetItem *___qtreewidgetitem6 = ___qtreewidgetitem2->child(3);
        ___qtreewidgetitem6->setText(0, QApplication::translate("news", "Thermocouple Simulation", nullptr));
        QTreeWidgetItem *___qtreewidgetitem7 = ___qtreewidgetitem2->child(4);
        ___qtreewidgetitem7->setText(0, QApplication::translate("news", "Pressure Transducer Simulation", nullptr));
        QTreeWidgetItem *___qtreewidgetitem8 = ___qtreewidgetitem2->child(5);
        ___qtreewidgetitem8->setText(0, QApplication::translate("news", "Dynamic Warning Messages", nullptr));
        QTreeWidgetItem *___qtreewidgetitem9 = ___qtreewidgetitem2->child(6);
        ___qtreewidgetitem9->setText(0, QApplication::translate("news", "Warning Suppression", nullptr));
        treeWidget->setSortingEnabled(__sortingEnabled);

    } // retranslateUi

};

namespace Ui {
    class news: public Ui_news {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NEWS_H
