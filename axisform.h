#ifndef AXISFORM_H
#define AXISFORM_H

#include <QDialog>
#include <qcustomplot.h>
#include <structs.h>
#include <tmachine.h>

namespace Ui {
class AxisForm;
}

class AxisForm : public QDialog
{
    Q_OBJECT

public:
    explicit AxisForm(QWidget *parent = 0);
    void setTMachine(TMachine* mvs);
    void drawTimes();
    void setFileNames(QStringList fileNames);
    ~AxisForm();

private slots:
    void horzScrollBarChanged(int value);

    void xAxisChanged(QCPRange range);

    void on_lessSize_clicked();

    void on_biggerSize_clicked();

private:
    Ui::AxisForm* ui;
    TMachine* MVS;
    QVector<double> Y;
    QVector<double> X;
    QVector<QCustomPlot*> plotsVect;
    QStringList FileNames;
};

#endif // AXISFORM_H
