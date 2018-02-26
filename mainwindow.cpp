#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QDebug>
#include <QtGui>
#include <QtWidgets>

using namespace ogdf;
using ogdf::energybased::dtree::GalaxyLevel;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    QIcon iconMW = QIcon("D:/Yandex Disk/Code/Lab4x86QT3/favicon.ico");
    this->setWindowIcon(iconMW);
    ui->setupUi(this);
    ui->graphBox->setVisible(false);
    ui->graphLabel->setVisible(false);
    QStringList stratList = {"MaxTime", "MinTime", "MaxChild", "ByCrits"};
    ui->stratBox->addItems(stratList);
    ui->timeAxisOpen->setVisible(false);
    ui->widget_2->setVisible(false);
    ui->tableGraph->setColumnCount(3);
    QStringList headers;
    headers << "№ узла" << "Tmin" << "Tmax";
    ui->tableGraph->setHorizontalHeaderLabels(headers);
    ui->tableGraph->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->tableGraph->setVisible(false);
    ui->scrollArea->setWidgetResizable(false);
    ui->crWayButton->setVisible(false);
    ui->tableProcKoefs->setColumnCount(3);
    headers.clear();
    headers << "№ Proc" << "Коеф.\nзагр" << "К загр\nс LM";
    ui->tableProcKoefs->setHorizontalHeaderLabels(headers);
    ui->tableProcKoefs->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->tableProcKoefs->setVisible(false);
    ui->tableBusKoefs->setColumnCount(2);
    headers.clear();
    headers << "№ Bus" << "Коеф.\nзагр";
    ui->tableBusKoefs->setHorizontalHeaderLabels(headers);
    ui->tableBusKoefs->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->tableBusKoefs->setVisible(false);
    QLabel *textLabel = new QLabel(ui->scrollArea);
    textLabel->setText("Здесь будет отображен граф");
    ui->scrollArea->setWidget(textLabel);
    ui->autoUpdateMVS->setVisible(false);

}

MainWindow::~MainWindow()
{
    if (ui->graphBox->currentIndex() != -1 || Converter->getErr() != 0)
    {
        delete MVS;
        delete Converter;
    }
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{

    QString selectedFilter;

    files = QFileDialog::getOpenFileNames(
                this,
                tr("Select .DAT files"),
                openFilesPath,
                tr("DAT Files (*.DAT)"),
                &selectedFilter);

    if (files.count() == 1)
    {
        ui->label_2->setText(QString("Режим: Однозадачный"));
        ui->graphBox->setVisible(false);
        ui->graphLabel->setVisible(false);
    }
    else if (files.count() > 1)
    {
        ui->label_2->setText(QString("Режим: Многозадачный"));
    }

    if (files.count())
    {
        filenames.clear();
        for(int i = 0;i < files.count();i++)
            filenames.append(QFileInfo(files[i]).fileName());

//        if (ui->graphBox->currentIndex() != -1 || Converter->getErr() != 0)
//        {
//            delete MVS;
//            delete Converter;
//        }

        int qVal = ui->qValue->value();
        bool LMcheck = true; //ui->checkLM->isChecked();
        QString pth = qApp->applicationDirPath();
        Converter = new TFileToGraph(files, pth, LMcheck, qVal, true, true);

        bool elemVis = true;
        if (Converter->getErr() != 0)
        {
            MVS = new TMachine();
            elemVis = false;
            QLabel *textLabel = new QLabel(ui->scrollArea);
            textLabel->setText("Здесь будет отображен граф");
            ui->scrollArea->setWidget(textLabel);
            ui->label_2->setText(QString("Задайте верный файл графа"));
        }

        ui->graphLabel->setVisible(elemVis);
        ui->graphBox->setVisible(elemVis);
        ui->tableGraph->setVisible(elemVis);
        ui->crWayButton->setVisible(elemVis);
        ui->tableProcKoefs->setVisible(elemVis);
        ui->tableBusKoefs->setVisible(elemVis);
        ui->widget_2->setVisible(elemVis);
        ui->autoUpdateMVS->setVisible(elemVis);
        ui->autoUpdateMVS->setChecked(elemVis);
        ui->timeAxisOpen->setVisible(false);

        QMessageBox msgBox;
        msgBox.setWindowTitle("Ошибка");
        switch (Converter->getErr()) {
        case 1:
            msgBox.setText("Файл не верно задает граф");
            msgBox.exec();
            return;
        case 2:
            msgBox.setText("В файле размер матрицы смежности\nне соответствует количеству узлов");
            msgBox.exec();
            return;
        case 3:
            msgBox.setText("Файл не открывается");
            msgBox.exec();
            return;
        case 4:
            msgBox.setText("Файл задает граф, не соответствующий\nтребуемому типу графов");
            msgBox.exec();
            return;
        default:
            break;
        }

        openFilesPath = files[0];
        ui->tasks->setText("Задачи: " + QString(filenames.join(", ")));

        Strat MachineStrat;
        switch (ui->stratBox->currentIndex()) {
        case 0:
            MachineStrat = MaxTime;
            break;
        case 1:
            MachineStrat = MinTime;
            break;
        case 2:
            MachineStrat = MaxChild;
            break;
        case 3:
            MachineStrat = ByCrits;
            break;
        default:
            break;
        }
        MVS = new TMachine(ui->procCount->value(), ui->busCount->value(),MachineStrat,Converter->getTGraphsVect(),LMcheck,qVal);
        MVS->RunMachine();
        ui->timeAxisOpen->setVisible(true);

        ui->graphBox->clear();
        ui->graphBox->addItems(filenames);
        ui->graphBox->setCurrentIndex(0);

        ui->tableProcKoefs->clearContents();
        ui->tableProcKoefs->setRowCount(MVS->getProcVect().count()+1);

        QTableWidgetItem *newItemNumber;
        QTableWidgetItem *newItemPrK;
        QTableWidgetItem *newItemPrLMK;
        for (int row = 0; row < ui->tableProcKoefs->rowCount()-1; row++)
        {
            newItemNumber = new QTableWidgetItem(QString::number(row+1));
            newItemPrK = new QTableWidgetItem(QString::number(MVS->getProcKoef(row+1)));
            newItemPrLMK = new QTableWidgetItem(QString::number(MVS->getProcLMKoef(row+1)));
            ui->tableProcKoefs->setItem(row,0,newItemNumber);
            ui->tableProcKoefs->setItem(row,1,newItemPrK);
            ui->tableProcKoefs->setItem(row,2,newItemPrLMK);
        }

        newItemNumber = new QTableWidgetItem(QString("AVER"));
        newItemPrK = new QTableWidgetItem(QString::number(MVS->getAverageProcKoef()));
        newItemPrLMK = new QTableWidgetItem(QString::number(MVS->getAverageProcLMKoef()));
        ui->tableProcKoefs->setItem(ui->tableProcKoefs->rowCount()-1,0,newItemNumber);
        ui->tableProcKoefs->setItem(ui->tableProcKoefs->rowCount()-1,1,newItemPrK);
        ui->tableProcKoefs->setItem(ui->tableProcKoefs->rowCount()-1,2,newItemPrLMK);

        ui->tableBusKoefs->clearContents();
        ui->tableBusKoefs->setRowCount(MVS->getBusVect().count()+1);

        QTableWidgetItem *newItemBK;
        for (int row = 0; row < ui->tableBusKoefs->rowCount()-1; row++)
        {
            newItemNumber = new QTableWidgetItem(QString::number(row+1));
            newItemBK = new QTableWidgetItem(QString::number(MVS->getBusKoef(row+1)));
            ui->tableBusKoefs->setItem(row,0,newItemNumber);
            ui->tableBusKoefs->setItem(row,1,newItemBK);
        }
        newItemNumber = new QTableWidgetItem(QString("AVER"));
        newItemBK = new QTableWidgetItem(QString::number(MVS->getAverageBusКoef()));
        ui->tableBusKoefs->setItem(ui->tableBusKoefs->rowCount()-1,0,newItemNumber);
        ui->tableBusKoefs->setItem(ui->tableBusKoefs->rowCount()-1,1,newItemBK);

        double SumGraphsTime = 0;
        for (int i = 0; i < MVS->getGraphVect().count(); i++)
            SumGraphsTime += MVS->getGraphVect()[i].getMaxTime();
        ui->AverTimelabel->setText("Коэф Ускорения:\n" + QString::number((SumGraphsTime * 1.0)/ MVS->getTotalTime()));

        connect(ui->qValue, SIGNAL(valueChanged(int)), this, SLOT(paramsChanged()));
        connect(ui->stratBox, SIGNAL(currentIndexChanged(int)), this, SLOT(paramsChanged()));
        connect(ui->procCount, SIGNAL(valueChanged(int)), this, SLOT(paramsChanged()));
        connect(ui->busCount, SIGNAL(valueChanged(int)), this, SLOT(paramsChanged()));

    }
    else
    {
        ui->label_2->setText(QString("Файл(ы) не выбран(ы)"));
    }
    //qDebug() << "End Push --**";
}


void MainWindow::on_graphBox_currentIndexChanged(int index)
{
    if (index != -1)
    {
        svgWGT = new QSvgWidget(qApp->applicationDirPath() + "/GraphsSVG/Output" + ui->graphBox->currentText() + ".svg",this);

        ui->scrollArea->setWidget(svgWGT);
        double svgKoef = qMin(((1.0 * ui->scrollArea->width()) / svgWGT->width())-1,((1.0 * ui->scrollArea->height()) / svgWGT->height())-1) + 1;
        svgWGT->resize(int(round(svgWGT->width() * svgKoef)) ,int(round(svgWGT->height() * svgKoef)));

        ui->tableGraph->clearContents();
        ui->tableGraph->setRowCount(MVS->getGraphVect()[index].getNodeCount());
        QTableWidgetItem *newItemNumber;
        QTableWidgetItem *newItemMin;
        QTableWidgetItem *newItemMax;
        for (int row = 0; row < ui->tableGraph->rowCount(); row++)
        {
            newItemNumber = new QTableWidgetItem(QString::number(row+1));
            newItemMin = new QTableWidgetItem(QString::number(MVS->getGraphVect()[index].getNode(row+1)->getTMin()));
            newItemMax = new QTableWidgetItem(QString::number(MVS->getGraphVect()[index].getNode(row+1)->getTMax()));
            ui->tableGraph->setItem(row,0,newItemNumber);
            ui->tableGraph->setItem(row,1,newItemMin);
            ui->tableGraph->setItem(row,2,newItemMax);
        }
        double allMin = 0, allMax = 0;
        for (TGraph grph : MVS->getGraphVect())
        {
            allMin = qMax(allMin, grph.getMinTime());
            allMax += grph.getMaxTime();
        }
        ui->statusBar->showMessage("Время задачи: Мин: " + QString::number(MVS->getGraphVect()[index].getMinTime()) +
                                   + " Макс: " + QString::number(MVS->getGraphVect()[index].getMaxTime()) + " Время набора: Мин: " +
                                   QString::number(allMin) + " Макс: " + QString::number(allMax) + " Общее время выполнения: " +
                                   (QString::number(MVS->getTotalTime())));
    }
}

void MainWindow::resizeEvent(QResizeEvent* event)
{
    if (ui->graphBox->currentIndex() != -1)
    {
        double svgKoef = qMin(((1.0 * ui->scrollArea->width()) / svgWGT->width())-1,((1.0 * ui->scrollArea->height()) / svgWGT->height())-1) + 1;
        svgWGT->resize(int(round(svgWGT->width() * svgKoef)) ,int(round(svgWGT->height() * svgKoef)));
    }
}

void MainWindow::on_timeAxisOpen_clicked()
{
    axisForm = new AxisForm(this);
    axisForm->setWindowFlags(axisForm->windowFlags() & ~Qt::WindowContextHelpButtonHint);
    axisForm->setTMachine(MVS);
    axisForm->setFileNames(filenames);
    axisForm->drawTimes();
    axisForm->setAttribute(Qt::WA_DeleteOnClose);
    axisForm->show();
}

void MainWindow::on_crWayButton_clicked()
{
    QVector<QVector<int>> CrWsInts;
    QVector<int> CrInts;
    QVector<QVector<TNode*>> CrWs = MVS->getGraphVect()[ui->graphBox->currentIndex()].getCritWays();
    for (int i = 0; i < CrWs.count(); i++)
    {
        CrInts.clear();
        for (int j = 0; j < CrWs[i].count(); j++)
            CrInts << CrWs[i][j]->getNodeNumber();
        CrWsInts << CrInts;
    }
    Converter->drawCritWays(CrWsInts,MVS->getGraphVect()[ui->graphBox->currentIndex()].getFixedPair(),ui->graphBox->currentIndex());

    svgWGT = new QSvgWidget(qApp->applicationDirPath() + "/GraphsSVG/Output" + ui->graphBox->currentText() + ".svg",this);


    ui->scrollArea->setWidget(svgWGT);
    double svgKoef = qMin(((1.0 * ui->scrollArea->width()) / svgWGT->width())-1,((1.0 * ui->scrollArea->height()) / svgWGT->height())-1) + 1;
    svgWGT->resize(int(round(svgWGT->width() * svgKoef)) ,int(round(svgWGT->height() * svgKoef)));
}

void MainWindow::paramsChanged()
{
    if (ui->autoUpdateMVS->isChecked())
    {
//        delete Converter;
//        delete MVS;
        Strat MachineStrat;
        switch (ui->stratBox->currentIndex()) {
        case 0:
            MachineStrat = MaxTime;
            break;
        case 1:
            MachineStrat = MinTime;
            break;
        case 2:
            MachineStrat = MaxChild;
            break;
        case 3:
            MachineStrat = ByCrits;
            break;
        default:
            break;
        }
        Converter = new TFileToGraph(files, qApp->applicationDirPath(), true , ui->qValue->value(), true, true);
        MVS = new TMachine(ui->procCount->value(), ui->busCount->value(), MachineStrat, Converter->getTGraphsVect(), true, ui->qValue->value());
        MVS->RunMachine();

        ui->tableProcKoefs->clearContents();
        ui->tableProcKoefs->setRowCount(MVS->getProcVect().count()+1);
        QTableWidgetItem *newItemNumber;
        QTableWidgetItem *newItemPrK;
        QTableWidgetItem *newItemPrLMK;

        for (int row = 0; row < ui->tableProcKoefs->rowCount()-1; row++)
        {
            newItemNumber = new QTableWidgetItem(QString::number(row+1));
            newItemPrK = new QTableWidgetItem(QString::number(MVS->getProcKoef(row+1)));
            newItemPrLMK = new QTableWidgetItem(QString::number(MVS->getProcLMKoef(row+1)));
            ui->tableProcKoefs->setItem(row,0,newItemNumber);
            ui->tableProcKoefs->setItem(row,1,newItemPrK);
            ui->tableProcKoefs->setItem(row,2,newItemPrLMK);
        }
        newItemNumber = new QTableWidgetItem(QString("AVER"));
        newItemPrK = new QTableWidgetItem(QString::number(MVS->getAverageProcKoef()));
        newItemPrLMK = new QTableWidgetItem(QString::number(MVS->getAverageProcLMKoef()));
        ui->tableProcKoefs->setItem(ui->tableProcKoefs->rowCount()-1,0,newItemNumber);
        ui->tableProcKoefs->setItem(ui->tableProcKoefs->rowCount()-1,1,newItemPrK);
        ui->tableProcKoefs->setItem(ui->tableProcKoefs->rowCount()-1,2,newItemPrLMK);

        ui->tableBusKoefs->clearContents();
        ui->tableBusKoefs->setRowCount(MVS->getBusVect().count()+1);

        QTableWidgetItem *newItemBK;
        for (int row = 0; row < ui->tableBusKoefs->rowCount()-1; row++)
        {
            newItemNumber = new QTableWidgetItem(QString::number(row+1));
            newItemBK = new QTableWidgetItem(QString::number(MVS->getBusKoef(row+1)));
            ui->tableBusKoefs->setItem(row,0,newItemNumber);
            ui->tableBusKoefs->setItem(row,1,newItemBK);
        }
        newItemNumber = new QTableWidgetItem(QString("AVER"));
        newItemBK = new QTableWidgetItem(QString::number(MVS->getAverageBusКoef()));
        ui->tableBusKoefs->setItem(ui->tableBusKoefs->rowCount()-1,0,newItemNumber);
        ui->tableBusKoefs->setItem(ui->tableBusKoefs->rowCount()-1,1,newItemBK);

        double SumGraphsTime = 0;
        for (int i = 0; i < MVS->getGraphVect().count(); i++)
            SumGraphsTime += MVS->getGraphVect()[i].getMaxTime();
        ui->AverTimelabel->setText("Коэф Ускорения:\n" + QString::number((SumGraphsTime * 1.0)/ MVS->getTotalTime()));

        ui->tableGraph->clearContents();
        ui->tableGraph->setRowCount(MVS->getGraphVect()[ui->graphBox->currentIndex()].getNodeCount());
        QTableWidgetItem *newItemMin;
        QTableWidgetItem *newItemMax;
        for (int row = 0; row < ui->tableGraph->rowCount(); row++)
        {
            newItemNumber = new QTableWidgetItem(QString::number(row+1));
            newItemMin = new QTableWidgetItem(QString::number(MVS->getGraphVect()[ui->graphBox->currentIndex()].getNode(row+1)->getTMin()));
            newItemMax = new QTableWidgetItem(QString::number(MVS->getGraphVect()[ui->graphBox->currentIndex()].getNode(row+1)->getTMax()));
            ui->tableGraph->setItem(row,0,newItemNumber);
            ui->tableGraph->setItem(row,1,newItemMin);
            ui->tableGraph->setItem(row,2,newItemMax);
        }

        double allMin = 0, allMax = 0;
        for (TGraph grph : MVS->getGraphVect())
        {
            allMin = qMax(allMin, grph.getMinTime());
            allMax += grph.getMaxTime();
        }
        ui->statusBar->showMessage("Время задачи: Мин: " + QString::number(MVS->getGraphVect()[ui->graphBox->currentIndex()].getMinTime()) +
                + " Макс: " + QString::number(MVS->getGraphVect()[ui->graphBox->currentIndex()].getMaxTime()) + " Время набора: Мин: " +
                QString::number(allMin) + " Макс: " + QString::number(allMax) + " Общее время выполнения: " +
                (QString::number(MVS->getTotalTime())));
    }
}
