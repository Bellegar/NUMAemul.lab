/********************************************************************************
** Form generated from reading UI file 'axisform.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_AXISFORM_H
#define UI_AXISFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QScrollBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AxisForm
{
public:
    QVBoxLayout *verticalLayout;
    QScrollArea *plots;
    QWidget *scrollAreaWidgetContents;
    QScrollBar *horizontalScrollBar;
    QWidget *widget_2;
    QHBoxLayout *horizontalLayout;
    QPushButton *lessSize;
    QPushButton *biggerSize;
    QLabel *totalTimeLabel;
    QLabel *time;
    QWidget *widget;

    void setupUi(QDialog *AxisForm)
    {
        if (AxisForm->objectName().isEmpty())
            AxisForm->setObjectName(QStringLiteral("AxisForm"));
        AxisForm->resize(827, 517);
        verticalLayout = new QVBoxLayout(AxisForm);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        plots = new QScrollArea(AxisForm);
        plots->setObjectName(QStringLiteral("plots"));
        plots->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        plots->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QStringLiteral("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 807, 428));
        plots->setWidget(scrollAreaWidgetContents);

        verticalLayout->addWidget(plots);

        horizontalScrollBar = new QScrollBar(AxisForm);
        horizontalScrollBar->setObjectName(QStringLiteral("horizontalScrollBar"));
        horizontalScrollBar->setValue(0);
        horizontalScrollBar->setOrientation(Qt::Horizontal);

        verticalLayout->addWidget(horizontalScrollBar);

        widget_2 = new QWidget(AxisForm);
        widget_2->setObjectName(QStringLiteral("widget_2"));
        widget_2->setMinimumSize(QSize(0, 40));
        widget_2->setMaximumSize(QSize(16777215, 60));
        horizontalLayout = new QHBoxLayout(widget_2);
        horizontalLayout->setSpacing(3);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(3, 3, 3, 3);
        lessSize = new QPushButton(widget_2);
        lessSize->setObjectName(QStringLiteral("lessSize"));
        lessSize->setMaximumSize(QSize(50, 16777215));

        horizontalLayout->addWidget(lessSize);

        biggerSize = new QPushButton(widget_2);
        biggerSize->setObjectName(QStringLiteral("biggerSize"));
        biggerSize->setMaximumSize(QSize(50, 16777215));

        horizontalLayout->addWidget(biggerSize);

        totalTimeLabel = new QLabel(widget_2);
        totalTimeLabel->setObjectName(QStringLiteral("totalTimeLabel"));
        totalTimeLabel->setMaximumSize(QSize(170, 16777215));
        QFont font;
        font.setPointSize(10);
        totalTimeLabel->setFont(font);

        horizontalLayout->addWidget(totalTimeLabel);

        time = new QLabel(widget_2);
        time->setObjectName(QStringLiteral("time"));
        time->setMaximumSize(QSize(100, 16777215));
        time->setFont(font);

        horizontalLayout->addWidget(time);

        widget = new QWidget(widget_2);
        widget->setObjectName(QStringLiteral("widget"));

        horizontalLayout->addWidget(widget);


        verticalLayout->addWidget(widget_2);


        retranslateUi(AxisForm);

        QMetaObject::connectSlotsByName(AxisForm);
    } // setupUi

    void retranslateUi(QDialog *AxisForm)
    {
        AxisForm->setWindowTitle(QApplication::translate("AxisForm", "\320\222\321\200\320\265\320\274\320\265\320\275\320\275\320\260\321\217 \320\264\320\270\320\260\320\263\321\200\320\260\320\274\320\274\320\260 \321\200\320\260\320\261\320\276\321\202\321\213 \320\234\320\222\320\241", Q_NULLPTR));
        lessSize->setText(QApplication::translate("AxisForm", "-", Q_NULLPTR));
        biggerSize->setText(QApplication::translate("AxisForm", "+", Q_NULLPTR));
        totalTimeLabel->setText(QApplication::translate("AxisForm", " \320\236\320\261\321\211\320\265\320\265 \320\262\321\200\320\265\320\274\321\217 \320\262\321\213\320\277\320\276\320\273\320\275\320\265\320\275\320\270\321\217: ", Q_NULLPTR));
        time->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class AxisForm: public Ui_AxisForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_AXISFORM_H
