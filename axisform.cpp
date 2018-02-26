#include "axisform.h"
#include "ui_axisform.h"

AxisForm::AxisForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AxisForm)
{
    ui->setupUi(this);
}

void AxisForm::setTMachine(TMachine *mvs)
{
    MVS = mvs;
    ui->time->setText(QString::number(MVS->getTotalTime()));
}

void AxisForm::drawTimes()
{
    QVBoxLayout *plotsLay = new QVBoxLayout;
    QVector<double> StatTemp;
    QVector<QColor> Colors;
    QVector<StatusTime<PStat>> ProcStats;
    QVector<StatusTime<BStat>> BusStats;
    QVector<TNode*> ProcNodes;
    QVector<int> FromNodes;
    QVector<int> ToNodes;
    QVector<int> GraphNum;
    QWidget *plot = new QWidget(ui->plots);
    QVector<double> GN;
    QVector<double> NN;

    QHBoxLayout *lay = new QHBoxLayout(ui->widget);

    int Grcount = MVS->getGraphVect().count();
    float currentHue = 0.37;
    for (int i = 0; i < Grcount; i++){
        Colors.push_back( QColor::fromHslF(currentHue, 1.0, 0.5,0.7) );
        currentHue += 0.618033988749895f;
        currentHue = std::fmod(currentHue, 1.0f);
    }

    for (int i = 0; i < Grcount; i++)
    {
        QLabel *fileColor = new QLabel(ui->widget);
        fileColor->setText(FileNames.at(i));
        QPalette palette = fileColor->palette();
        palette.setColor(fileColor->backgroundRole(), Colors[i]);
        fileColor->setPalette(palette);
        fileColor->setAutoFillBackground(true);
        lay->addWidget(fileColor);
    }
    ui->widget->setLayout(lay);

    int p;
    for (p = 0; p < MVS->getProcVect().count(); p++)
    {
        X.clear();
        Y.clear();
        GN.clear();
        NN.clear();

        ProcStats = MVS->getProcVect()[p].getProcStatsHistory();
        ProcNodes = MVS->getProcVect()[p].getNodesHistory();
        for (int i = 0; i < ProcStats.count(); i++)
        {
            X << ProcStats[i].Time;
            Y << ProcStats[i].Stat;
        }
        for (int i = 0; i < ProcNodes.count(); i++)
        {
            GN << ProcNodes[i]->getMyTGraph()->getGraphNumber();
            NN << ProcNodes[i]->getNodeNumber();
        }

        plotsVect << new QCustomPlot(plot);
        for (int gr = 0; gr < Grcount; gr++)
        {

            StatTemp = Y;
            plotsVect[p]->addGraph();
            for (int i = 0; i < Y.count(); i++)
                if (GN[i] != (gr+1))
                    StatTemp.replace(i,0);
            plotsVect[p]->graph(gr)->setData(X, StatTemp);
            plotsVect[p]->graph(gr)->setLineStyle(QCPGraph::LineStyle::lsStepLeft);
            plotsVect[p]->graph(gr)->setBrush(QBrush(Colors[gr]));

        }

        for (int i = 0; i < X.count()-1; i++)
        {
            if (X[i+1] == X[i])
            {
                X.remove(i);
                Y.remove(i);
                NN.remove(i);
            }
        }

        for (int tms = 0; tms < X.count(); tms++)
        {

            QCPItemText *textLabel = new QCPItemText(plotsVect[p]);
            textLabel->setPositionAlignment(Qt::AlignTop|Qt::AlignHCenter);
            textLabel->setFont(QFont("Verdana", 9));
            textLabel->setPen(Qt::NoPen);
            textLabel->position->setType(QCPItemPosition::ptPlotCoords);
            textLabel->position->setCoords(X[tms]+0.35, Y[tms]); // place position at center/top of axis rect
            textLabel->setText(QString::number(NN[tms]));

        }

        QSharedPointer<QCPAxisTicker> tickers(new QCPAxisTicker);
        plotsVect[p]->xAxis->setTicker(tickers);
        tickers->setTickCount(25);

        plotsVect[p]->yAxis->setLabel(QString("PROC %1").arg(p+1));
        plotsVect[p]->xAxis->setRange(0,50); //X.last())
        plotsVect[p]->yAxis->setRange(0,7);
        plotsVect[p]->setMinimumHeight(70);
        plotsVect[p]->yAxis->setTickLabels(false);
        plotsLay->addWidget(plotsVect[p]);
    }

    for (int b = p; b < MVS->getBusVect().count() + p; b++)
    {
        X.clear();
        Y.clear();

        BusStats = MVS->getBusVect()[b-p].getBusStatsHistory();
        ToNodes = MVS->getBusVect()[b-p].getToProcNumHistory();
        FromNodes = MVS->getBusVect()[b-p].getFromProcNumHistory();
        GraphNum = MVS->getBusVect()[b-p].getGraphNumHistory();

        for (int i = 0; i < BusStats.count(); i++)
        {
            X << BusStats[i].Time;
            Y << BusStats[i].Stat;
        }

        plotsVect << new QCustomPlot(plot);
        for (int gr = 0; gr < Grcount; gr++)
        {
            StatTemp = Y;
            plotsVect[b]->addGraph();
            for (int i = 0; i < Y.count(); i++)
                if (GraphNum[i] != (gr+1))
                    StatTemp.replace(i,0);
            plotsVect[b]->graph(gr)->setData(X, StatTemp);
            plotsVect[b]->graph(gr)->setLineStyle(QCPGraph::LineStyle::lsStepLeft);
            plotsVect[b]->graph(gr)->setBrush(QBrush(Colors[gr]));
        }


        for (int tms = 0; tms < X.count()-1; tms++)
        {
            if (Y[tms] == BBusy)
            {
                QCPItemText *textLabel = new QCPItemText(plotsVect[b]);
                textLabel->setPositionAlignment(Qt::AlignTop|Qt::AlignHCenter);
                textLabel->setFont(QFont("Verdana", 10));
                textLabel->setPen(Qt::NoPen);
                textLabel->position->setType(QCPItemPosition::ptPlotCoords);
                textLabel->position->setCoords(X[tms]+0.3, (int(X[tms]) % 5) / 10.0 + 0.42); // place position at center/top of axis rect
                textLabel->setText(QString::number(FromNodes[tms]) + "->" + QString::number(ToNodes[tms]));
            }
        }

        QSharedPointer<QCPAxisTicker> tickers(new QCPAxisTicker);
        plotsVect[b]->xAxis->setTicker(tickers);
        tickers->setTickCount(25);
        plotsVect[b]->yAxis->setTickLabels(false);


        plotsVect[b]->yAxis->setLabel(QString("BUS %1").arg(b-p+1));
        plotsVect[b]->xAxis->setRange(0,50); //X.last())
        plotsVect[b]->yAxis->setRange(0,1);
        plotsVect[b]->setMinimumHeight(60);

        plotsLay->addWidget(plotsVect[b]);

    }

    plot->setLayout(plotsLay);
    ui->plots->setWidget(plot);
    ui->horizontalScrollBar->setRange(0,int(round(MVS->getTotalTime())));
    ui->horizontalScrollBar->setPageStep(qRound(plotsVect[0]->xAxis->range().size()));
    connect(ui->horizontalScrollBar, SIGNAL(valueChanged(int)), this, SLOT(horzScrollBarChanged(int)));
    connect(plotsVect[0]->xAxis, SIGNAL(rangeChanged(QCPRange)), this, SLOT(xAxisChanged(QCPRange)));
}

void AxisForm::setFileNames(QStringList fileNames)
{
    FileNames = fileNames;
}

AxisForm::~AxisForm()
{
    delete ui;
}


void AxisForm::horzScrollBarChanged(int value)
{
    plotsVect[0]->xAxis->setRange(value, plotsVect[0]->xAxis->range().size(), Qt::AlignLeft);
    plotsVect[0]->replot();
    QCPRange rng0 = plotsVect[0]->xAxis->range();
    for (int i = 1; i < plotsVect.count(); i++)
    {
        plotsVect[i]->xAxis->setRange(rng0);
        plotsVect[i]->replot();
    }
}

void AxisForm::xAxisChanged(QCPRange range)
{
    ui->horizontalScrollBar->setValue(qRound(range.lower)); // adjust position of scroll bar slider
    ui->horizontalScrollBar->setPageStep(qRound(range.size())); // adjust size of scroll bar slider
}

void AxisForm::on_lessSize_clicked()
{
    for (int i = 0; i < plotsVect.count(); i++)
    {
        plotsVect[i]->xAxis->scaleRange(0.5, plotsVect[i]->xAxis->range().lower);
        plotsVect[i]->replot();
    }
}

void AxisForm::on_biggerSize_clicked()
{
    double maxRange = 0;
    for (int i = 0; i < plotsVect.count(); i++)
    {
        maxRange = qMax(maxRange,plotsVect[i]->xAxis->range().upper);
    }
    if (maxRange < MVS->getTotalTime())
    {
        for (int i = 0; i < plotsVect.count(); i++)
        {
            plotsVect[i]->xAxis->scaleRange(2, plotsVect[i]->xAxis->range().lower);
            plotsVect[i]->replot();
        }
    }
}
