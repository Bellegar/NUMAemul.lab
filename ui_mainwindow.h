/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QWidget *widget;
    QGridLayout *gridLayout_3;
    QLabel *stratLabel;
    QLabel *procLabel;
    QSpinBox *procCount;
    QLabel *busLabel;
    QSpinBox *qValue;
    QLabel *tasks;
    QSpinBox *busCount;
    QLabel *label_2;
    QPushButton *pushButton;
    QComboBox *graphBox;
    QComboBox *stratBox;
    QPushButton *timeAxisOpen;
    QLabel *graphLabel;
    QLabel *koefLabel;
    QPushButton *crWayButton;
    QCheckBox *autoUpdateMVS;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QWidget *widget_2;
    QVBoxLayout *verticalLayout;
    QTableWidget *tableGraph;
    QWidget *widget_3;
    QVBoxLayout *verticalLayout_2;
    QTableWidget *tableProcKoefs;
    QTableWidget *tableBusKoefs;
    QLabel *AverTimelabel;
    QStatusBar *statusBar;
    QMenuBar *menuBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(712, 643);
        MainWindow->setDockNestingEnabled(false);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setHorizontalSpacing(6);
        gridLayout->setContentsMargins(6, 6, 6, 6);
        widget = new QWidget(centralWidget);
        widget->setObjectName(QStringLiteral("widget"));
        gridLayout_3 = new QGridLayout(widget);
        gridLayout_3->setSpacing(5);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        gridLayout_3->setContentsMargins(5, 5, 5, 5);
        stratLabel = new QLabel(widget);
        stratLabel->setObjectName(QStringLiteral("stratLabel"));

        gridLayout_3->addWidget(stratLabel, 6, 0, 1, 1);

        procLabel = new QLabel(widget);
        procLabel->setObjectName(QStringLiteral("procLabel"));

        gridLayout_3->addWidget(procLabel, 2, 0, 1, 1);

        procCount = new QSpinBox(widget);
        procCount->setObjectName(QStringLiteral("procCount"));
        procCount->setMinimum(1);

        gridLayout_3->addWidget(procCount, 3, 0, 1, 1);

        busLabel = new QLabel(widget);
        busLabel->setObjectName(QStringLiteral("busLabel"));

        gridLayout_3->addWidget(busLabel, 4, 0, 1, 1);

        qValue = new QSpinBox(widget);
        qValue->setObjectName(QStringLiteral("qValue"));
        qValue->setEnabled(true);
        qValue->setMinimum(1);
        qValue->setMaximum(10000);

        gridLayout_3->addWidget(qValue, 11, 0, 1, 1);

        tasks = new QLabel(widget);
        tasks->setObjectName(QStringLiteral("tasks"));
        tasks->setScaledContents(false);
        tasks->setWordWrap(true);

        gridLayout_3->addWidget(tasks, 9, 0, 1, 1);

        busCount = new QSpinBox(widget);
        busCount->setObjectName(QStringLiteral("busCount"));
        busCount->setMinimum(1);

        gridLayout_3->addWidget(busCount, 5, 0, 1, 1);

        label_2 = new QLabel(widget);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout_3->addWidget(label_2, 8, 0, 1, 1);

        pushButton = new QPushButton(widget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setCheckable(false);

        gridLayout_3->addWidget(pushButton, 0, 0, 1, 1);

        graphBox = new QComboBox(widget);
        graphBox->setObjectName(QStringLiteral("graphBox"));
        graphBox->setEnabled(true);

        gridLayout_3->addWidget(graphBox, 13, 0, 1, 1);

        stratBox = new QComboBox(widget);
        stratBox->setObjectName(QStringLiteral("stratBox"));

        gridLayout_3->addWidget(stratBox, 7, 0, 1, 1);

        timeAxisOpen = new QPushButton(widget);
        timeAxisOpen->setObjectName(QStringLiteral("timeAxisOpen"));
        QFont font;
        font.setPointSize(10);
        font.setBold(true);
        font.setWeight(75);
        timeAxisOpen->setFont(font);

        gridLayout_3->addWidget(timeAxisOpen, 1, 0, 1, 1);

        graphLabel = new QLabel(widget);
        graphLabel->setObjectName(QStringLiteral("graphLabel"));
        graphLabel->setWordWrap(true);

        gridLayout_3->addWidget(graphLabel, 12, 0, 1, 1);

        koefLabel = new QLabel(widget);
        koefLabel->setObjectName(QStringLiteral("koefLabel"));

        gridLayout_3->addWidget(koefLabel, 10, 0, 1, 1);

        crWayButton = new QPushButton(widget);
        crWayButton->setObjectName(QStringLiteral("crWayButton"));

        gridLayout_3->addWidget(crWayButton, 14, 0, 1, 1);

        autoUpdateMVS = new QCheckBox(widget);
        autoUpdateMVS->setObjectName(QStringLiteral("autoUpdateMVS"));
        autoUpdateMVS->setChecked(false);

        gridLayout_3->addWidget(autoUpdateMVS, 15, 0, 1, 1);


        gridLayout->addWidget(widget, 0, 1, 1, 1);

        scrollArea = new QScrollArea(centralWidget);
        scrollArea->setObjectName(QStringLiteral("scrollArea"));
        scrollArea->setMinimumSize(QSize(200, 100));
        scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        scrollArea->setSizeAdjustPolicy(QAbstractScrollArea::AdjustIgnored);
        scrollArea->setWidgetResizable(false);
        scrollArea->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QStringLiteral("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 458, 580));
        scrollArea->setWidget(scrollAreaWidgetContents);

        gridLayout->addWidget(scrollArea, 0, 2, 1, 1);

        widget_2 = new QWidget(centralWidget);
        widget_2->setObjectName(QStringLiteral("widget_2"));
        widget_2->setMinimumSize(QSize(150, 0));
        widget_2->setMaximumSize(QSize(250, 16777215));
        verticalLayout = new QVBoxLayout(widget_2);
        verticalLayout->setSpacing(3);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setSizeConstraint(QLayout::SetMinimumSize);
        verticalLayout->setContentsMargins(3, 3, 3, 3);
        tableGraph = new QTableWidget(widget_2);
        tableGraph->setObjectName(QStringLiteral("tableGraph"));
        tableGraph->setMinimumSize(QSize(140, 250));
        tableGraph->setMaximumSize(QSize(10000, 16777215));
        tableGraph->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tableGraph->verticalHeader()->setVisible(false);

        verticalLayout->addWidget(tableGraph);

        widget_3 = new QWidget(widget_2);
        widget_3->setObjectName(QStringLiteral("widget_3"));
        widget_3->setMinimumSize(QSize(0, 0));
        verticalLayout_2 = new QVBoxLayout(widget_3);
        verticalLayout_2->setSpacing(3);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setSizeConstraint(QLayout::SetDefaultConstraint);
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        tableProcKoefs = new QTableWidget(widget_3);
        tableProcKoefs->setObjectName(QStringLiteral("tableProcKoefs"));
        tableProcKoefs->setMinimumSize(QSize(140, 0));
        tableProcKoefs->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tableProcKoefs->verticalHeader()->setVisible(false);

        verticalLayout_2->addWidget(tableProcKoefs);

        tableBusKoefs = new QTableWidget(widget_3);
        tableBusKoefs->setObjectName(QStringLiteral("tableBusKoefs"));
        tableBusKoefs->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tableBusKoefs->setTabKeyNavigation(true);
        tableBusKoefs->verticalHeader()->setVisible(false);

        verticalLayout_2->addWidget(tableBusKoefs);


        verticalLayout->addWidget(widget_3);

        AverTimelabel = new QLabel(widget_2);
        AverTimelabel->setObjectName(QStringLiteral("AverTimelabel"));
        QFont font1;
        font1.setPointSize(11);
        AverTimelabel->setFont(font1);

        verticalLayout->addWidget(AverTimelabel);


        gridLayout->addWidget(widget_2, 0, 3, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        statusBar->setEnabled(true);
        QFont font2;
        font2.setPointSize(9);
        statusBar->setFont(font2);
        MainWindow->setStatusBar(statusBar);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 712, 21));
        MainWindow->setMenuBar(menuBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "\320\234\320\276\320\264\320\265\320\273\320\270\321\200\320\276\320\262\320\260\320\275\320\270\320\265 \320\234\320\222\320\241 \321\201 \321\200\320\260\321\201\320\277\321\200\320\265\320\264\320\265\320\273\320\265\320\275\320\275\320\276\320\271 \320\277\320\260\320\274\321\217\321\202\321\214\321\216", Q_NULLPTR));
        stratLabel->setText(QApplication::translate("MainWindow", "\320\241\321\202\321\200\320\260\321\202\320\265\320\263\320\270\321\217 \320\275\320\260\320\267\320\275\320\260\321\207\320\265\320\275\320\270\321\217 :", Q_NULLPTR));
        procLabel->setText(QApplication::translate("MainWindow", "\320\232\320\276\320\273\320\270\321\207\320\265\321\201\321\202\320\262\320\276 \320\277\321\200\320\276\321\206\320\265\321\201\321\201\320\276\321\200\320\276\320\262 :", Q_NULLPTR));
        busLabel->setText(QApplication::translate("MainWindow", "\320\232\320\276\320\273\320\270\321\207\320\265\321\201\321\202\320\262\320\276 \321\210\320\270\320\275 :", Q_NULLPTR));
        tasks->setText(QString());
        label_2->setText(QApplication::translate("MainWindow", "\320\222\321\213\320\261\320\265\321\200\320\270\321\202\320\265 \321\204\320\260\320\271\320\273(\321\213)", Q_NULLPTR));
        pushButton->setText(QApplication::translate("MainWindow", "\320\236\321\202\320\272\321\200\321\213\321\202\321\214 \321\204\320\260\320\271\320\273\321\213 \320\263\321\200\320\260\321\204\320\276\320\262\n"
"\320\270 \321\201\320\276\320\267\320\264\320\260\321\202\321\214 \320\234\320\222\320\241", Q_NULLPTR));
        timeAxisOpen->setText(QApplication::translate("MainWindow", "\320\236\321\202\320\272\321\200\321\213\321\202\321\214 \320\264\320\270\320\260\320\263\321\200\320\260\320\274\320\274\321\203", Q_NULLPTR));
        graphLabel->setText(QApplication::translate("MainWindow", "\320\222\321\213\320\261\320\276\321\200 \320\263\321\200\320\260\321\204\320\260 \320\264\320\273\321\217 \320\276\321\202\320\276\320\261\321\200\320\260\320\266\320\265\320\275\320\270\321\217 :", Q_NULLPTR));
        koefLabel->setText(QApplication::translate("MainWindow", "<html><head/><body><p>\320\232\320\276\321\215\321\204\321\204\320\270\321\206\320\270\320\265\320\275\321\202 Q<span style=\" vertical-align:sub;\">LM</span> :</p></body></html>", Q_NULLPTR));
        crWayButton->setText(QApplication::translate("MainWindow", "\320\236\321\202\320\276\320\261\321\200\320\260\320\267\320\270\321\202\321\214 \n"
"\320\272\321\200\320\270\321\202\320\270\321\207\320\265\321\201\320\272\320\270\320\271 \320\277\321\203\321\202\321\214", Q_NULLPTR));
        autoUpdateMVS->setText(QApplication::translate("MainWindow", "\320\220\320\262\321\202\320\276\320\274\320\260\321\202\320\270\321\207\320\265\321\201\320\272\320\270\n"
"\320\277\320\265\321\200\320\265\321\201\321\202\321\200\320\260\320\270\320\262\320\260\321\202\321\214 \320\234\320\222\320\241", Q_NULLPTR));
        AverTimelabel->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
