#include "tmachine.h"
#include <qDebug>
bool static sortMinTime(const TNode *v1, const TNode *v2);
bool static sortMaxTime(const TNode *v1, const TNode *v2);
bool static sortMaxChild(const TNode *v1, const TNode *v2);
bool static sortByCrits(const TNode *v1, const TNode *v2);
bool static sortByFixed(const TNode *v1, const TNode *v2);
bool static sortProcByFinishTime(const TProc *p1, const TProc *p2);
bool static sortProcByNum(const TProc *p1, const TProc *p2);
bool static sortBusByNum(const TBus *b1, const TBus *b2);
void sortNodes(QVector<TNode*> &targetVector, Strat targetStrategy);

TMachine::TMachine()
{

}

TMachine::TMachine(int countOfProc, int countOfBus, Strat strat, QVector<TGraph> vectorOfGraph, bool isLM, int q)
{
    IsLocalMem = isLM;
    QKoef = q;
    GraphVect = vectorOfGraph;
    for (int i = 0; i < GraphVect.count(); i++)
        for (int j = 0; j < GraphVect[i].getNodeCount(); j++)
            GraphVect[i].getNode(j+1)->setMyTGraph(&GraphVect[i]);

    for (int i = 0; i < countOfProc; i++)
        ProcVect.push_back(TProc(i,this));
    for (int i = 0; i < countOfBus; i++)
        BusVect.push_back(TBus(i));
    Strategy = strat;
    Time = 0;
    TotalTime = 0;
    AllCompleted = false;

    for (int i = 0; i < GraphVect.count(); i++)
        for (int j = 0; j < GraphVect[i].getNodeCount(); j++)
            QueueOfNotReadyNodes << GraphVect[i].getNode(j+1);
    NodesCount = QueueOfNotReadyNodes.count();
    sortNodes(QueueOfNotReadyNodes,Strategy);

    for (int i = 0; i < ProcVect.count(); i++)
        QueueOfFreeProc << &ProcVect[i];

    for (int i = 0; i < BusVect.count(); i++)
        QueueOfFreeBus << &BusVect[i];

    QueueOfBusyProc.clear();
    QueueOfReadyNodes.clear();
    QueueOfExecNodes.clear();
    QueueOfCompletedNodes.clear();
    QueueOfBusyBus.clear();
}

double TMachine::getTotalTime() const
{
    return TotalTime;
}

bool TMachine::isCompleted() const
{
    return AllCompleted;
}

double TMachine::getProcKoef(int number) const
{
    return (ProcVect[number-1].getProcBusyTime() * 1.0) / TotalTime;
}

double TMachine::getProcLMKoef(int number) const
{
    return (ProcVect[number-1].getProcLMBusyTime() * 1.0) / TotalTime;
}

double TMachine::getAverageProcKoef() const
{
    double aver = 0;
    for (TProc prc : ProcVect)
        aver += prc.getProcBusyTime();
    return (aver * 1.0) / (ProcVect.count() * TotalTime);
}

double TMachine::getAverageProcLMKoef() const
{
    double aver = 0;
    for (TProc prc : ProcVect)
        aver += prc.getProcLMBusyTime();
    return (aver * 1.0) / (ProcVect.count() * TotalTime);
}

double TMachine::getBusKoef(int number) const
{
    return (BusVect[number-1].getBusBusyTime() * 1.0) / TotalTime;
}

double TMachine::getAverageBusКoef() const
{
    double aver = 0;
    for (TBus prc : BusVect)
        aver += prc.getBusBusyTime();
    return (aver * 1.0) / (BusVect.count() * TotalTime);
}

Strat TMachine::getStrategy() const
{
    return Strategy;
}

QVector<TProc> TMachine::getProcVect()
{
    return ProcVect;
}

QVector<TBus> TMachine::getBusVect()
{
    return BusVect;
}

QVector<TGraph> TMachine::getGraphVect()
{
    return GraphVect;
}

void TMachine::RunMachine()
{

    TNode * currNode;
    TProc * currProc;
    TNode * currPredNode;
    TNode * nrdNode;
    NStat rdstat;
    int downParts;
    double timeEvent;
    bool needDownload;
    PStat ProcStatus;
    LMStat LMStatus;
    TProc * tempProc;
    QVector<TNode*> tempN;
    bool newDownRound;
    bool newBusy;
    do
    {
        do
        {
            do
            {
                qSort(QueueOfBusyProc.begin(),QueueOfBusyProc.end(),sortProcByFinishTime);
                qSort(QueueOfFreeProc.begin(),QueueOfFreeProc.end(),sortProcByNum);
                needDownload = true;
                downParts = 0;
                timeEvent = 0;
                newBusy = false;
                newDownRound = false;


                for (int j = 0; j < QueueOfBusyProc.count(); j++)
                {
                    qSort(QueueOfFreeBus.begin(),QueueOfFreeBus.end(),sortBusByNum);
                    currProc = QueueOfBusyProc[j];
                    currNode = currProc->getExecNode();
                    ProcStatus = currProc->getProcStatus().Stat;
                    LMStatus = currProc->getLocalMemoryStatus().Stat;

                    downParts = currProc->getDownloadedPartsCount();
                    needDownload = (downParts != currNode->getPredNodes().count());
                    if (needDownload)
                    {
                        currPredNode = currNode->getMyTGraph()->getNode(currNode->getPredNodes()[downParts].DestNodeNum);
                        //Если на том же процессоре:
                        while (currProc->getProcNumber() == currPredNode->getExecTProc()->getProcNumber())
                        {
                            currProc->setDownloadedPartsCount(currProc->getDownloadedPartsCount() + 1);
                            downParts = currProc->getDownloadedPartsCount();
                            needDownload = (downParts != currNode->getPredNodes().count());
                            if (needDownload)
                                currPredNode = currNode->getMyTGraph()->getNode(currNode->getPredNodes()[downParts].DestNodeNum);
                            else
                            {
                                currPredNode = currNode;
                                ProcStatus = WaitForOtherLMFree;
                                break;
                                //ProcStatus = LoadFromLocalMem;
                            }
                        }
                    }
                    else
                        currPredNode = currNode;

                    currProc->setFromTProc(currPredNode->getExecTProc());




                    //START SET

                    if (needDownload)
                    {
                        switch (ProcStatus)
                        {
                        case Free:
                            ProcStatus = WaitForBus;
                        case WaitForBus:
                        {
                            if (!QueueOfFreeBus.isEmpty())
                            {
                                QueueOfFreeBus[0]->setFromProcNum(currProc->getFromTProc()->getProcNumber());
                                QueueOfFreeBus[0]->setToProcNum(currProc->getProcNumber());
                                QueueOfFreeBus[0]->setGraphNum(currNode->getMyTGraph()->getGraphNumber());
                                QueueOfFreeBus[0]->setBusStatus({BBusy, Time});
                                currProc->setUsingTBus(QueueOfFreeBus[0]);
                                //qDebug() << "takeAT in FreeBus";
                                QueueOfBusyBus << QueueOfFreeBus.takeAt(0);
                                ProcStatus = WaitForMyLMFree;
                            }
                            else if (currProc->getProcStatus().Stat != ProcStatus)
                            {
                                currProc->setProcStatus({ProcStatus, Time});
                                break;
                            }
                            else
                                break;

                        }
                        case WaitForMyLMFree:
                        {
                            if (LMStatus == LMFree)
                            {
                                currProc->setLocalMemoryStatus({LMBusy, Time});
                                ProcStatus = WaitForOtherLMFree;
                            }
                            else if (currProc->getProcStatus().Stat != ProcStatus)
                            {
                                currProc->setProcStatus({ProcStatus, Time});
                                break;
                            }
                            else
                                break;

                        }
                        case WaitForOtherLMFree:
                        {//currNode->getNodeNumber() == currPredNode->getNodeNumber()
                            if (currProc->getFromTProc()->getLocalMemoryStatus().Stat == LMFree)
                            {
                                currProc->getFromTProc()->setLocalMemoryStatus({LMBusy, Time});
                                ProcStatus = WaitForDownload;
                            }
                            else if (currProc->getProcStatus().Stat != ProcStatus)
                            {
                                currProc->setProcStatus({ProcStatus, Time});
                                break;
                            }
                            else
                                break;

                        }
                        case WaitForDownload:
                        {
                            if (currProc->getProcStatus().Stat == ProcStatus)
                                if (Time >= currProc->getFinishTime())
                                {
                                    ProcStatus = Free;
                                    currProc->getFromTProc()->setLocalMemoryStatus({LMFree, Time});
                                    LMStatus = LMFree;
                                    currProc->setLocalMemoryStatus({LMFree, Time});
                                    QueueOfFreeBus << currProc->getUsingTBus();
                                    QueueOfBusyBus.removeOne(currProc->getUsingTBus());
                                    QueueOfFreeBus.last()->setBusStatus({BFree, Time});
                                    currProc->setDownloadedPartsCount(downParts + 1);
                                    if (currProc->getDownloadedPartsCount() == currNode->getPredNodes().count())
                                    {
                                        needDownload = false;
                                        ProcStatus = LoadFromLocalMem;
                                        break;
                                    }
                                    else
                                    {
                                        currProc->setProcStatus({WaitForBus,Time});
                                        newDownRound = true;

                                    }
                                    break;
                                }
                                else
                                    break;
                            else
                            {
                                currProc->setProcStatus({ProcStatus, Time});
                                timeEvent = Time + currPredNode->getSuccEdgeWeight(currNode->getNodeNumber());
                                currProc->setFinishTime(timeEvent);
                                TimeEvents << timeEvent;
                                break;
                            }

                        }
                        default:
                            //qDebug() << "Не верный статус при needDownload *+*+*+*+*+*+*"<< ProcStatus;
                            break;

                        }
                    }

                    if (!needDownload)
                    {
                        switch (ProcStatus)
                        {
                        case WaitForOtherLMFree:
                        {//same Proc, OtherLM = MyLM
                            if (LMStatus == LMFree)
                                ProcStatus = LoadFromLocalMem;
                            else if (currProc->getProcStatus().Stat != ProcStatus)
                            {
                                currProc->setProcStatus({ProcStatus, Time});
                                break;
                            }
                            else
                                break;

                        }
                        case LoadFromLocalMem:
                        {
                            if (currProc->getProcStatus().Stat == ProcStatus)
                                if (Time >= currProc->getFinishTime())
                                {
                                    ProcStatus = Busy;
                                }
                                else
                                    break;
                            else
                            {
                                currProc->setProcStatus({ProcStatus, Time});
                                currNode->setStatusNode(Exec);
                                if (currProc->getLocalMemoryStatus().Stat == LMFree)
                                    currProc->setLocalMemoryStatus({LMBusy,Time});
                                timeEvent = Time + (currNode->getInWeights() * 1.0) / QKoef;
                                currProc->setFinishTime(timeEvent);
                                TimeEvents << timeEvent;
                                break;
                            }

                        }
                        case Busy:
                        {
                            if (currProc->getProcStatus().Stat == ProcStatus)
                                if (Time >= currProc->getFinishTime())
                                    ProcStatus = WaitForMyLMFree;
                                else
                                    break;
                            else
                            {
                                currProc->setLocalMemoryStatus({LMFree, Time});
                                currProc->setProcStatus({Busy, Time});
                                timeEvent = Time + currNode->getNodeTime();
                                currProc->setFinishTime(timeEvent);
                                TimeEvents << timeEvent;
                                break;
                            }
                        }
                        case WaitForMyLMFree:
                        {
                            if (LMStatus == LMFree)
                                ProcStatus = LoadToLocalMem;
                            else if (currProc->getProcStatus().Stat != ProcStatus)
                            {
                                currProc->setProcStatus({ProcStatus, Time});
                                break;
                            }
                            else
                                break;

                        }
                        case LoadToLocalMem:
                        {
                            if (currProc->getProcStatus().Stat == ProcStatus)
                                if (Time >= currProc->getFinishTime())
                                {
                                    currProc->setLocalMemoryStatus({LMFree, Time});
                                    currProc->setProcStatus({Free, Time});
                                    currNode->setStatusNode(Completed);
                                    currProc->setDownloadedPartsCount(0);
                                    QueueOfFreeProc << currProc;
                                    QueueOfBusyProc.removeOne(currProc);
                                    j--;
                                    QueueOfExecNodes.removeOne(currNode);
                                    QueueOfCompletedNodes << currNode;
                                    break;
                                }
                                else
                                    break;
                            else
                            {
                                currProc->setLocalMemoryStatus({LMBusy, Time});
                                currProc->setProcStatus({ProcStatus, Time});
                                timeEvent = Time + (currNode->getOutWeights() * 1.0) / QKoef;
                                currProc->setFinishTime(timeEvent);
                                TimeEvents << timeEvent;
                                break;
                            }

                        }
                        case Free:
                        {//начальный узел
                            currProc->setProcStatus({Busy, Time});
                            currNode->setStatusNode(Exec);
                            timeEvent = Time + currNode->getNodeTime();
                            currProc->setFinishTime(timeEvent);
                            TimeEvents << timeEvent;
                            break;
                        }
                        default:
                            //qDebug() << "Не верный статус при NOneedDownload *-*-*-*-*-*-*-*-*"<< ProcStatus;
                            break;
                        }
                    }
                }

            } while (newDownRound);


            for (int i = 0; i < QueueOfNotReadyNodes.count(); i++)
            {
                nrdNode = QueueOfNotReadyNodes[i];
                rdstat = nrdNode->getMyTGraph()->calcPredStatusNode(nrdNode->getNodeNumber());
                nrdNode->setStatusNode(rdstat);
                if (rdstat == Ready)
                {
                    //qDebug() << "takeAT in NotReadyNodes";
                    QueueOfReadyNodes << QueueOfNotReadyNodes.takeAt(i--);
                }
            }


            tempN = QueueOfReadyNodes;
            while (!QueueOfReadyNodes.isEmpty() && !QueueOfFreeProc.isEmpty() && !tempN.isEmpty())
            {
                tempN = QueueOfReadyNodes;
                qSort(tempN.begin(),tempN.end(),sortByFixed);
                for (int i = 0; i < tempN.count(); i++)

                    while (tempN[0]->hasPredFix())
                    {
                        tempProc = tempN[0]->getMyTGraph()->getNode(tempN[0]->getPredFixNodeNum())->getExecTProc();
                        if (QueueOfFreeProc.contains(tempProc))
                        {
                            currNode = tempN[0];
                            currProc = tempProc;
                            break;
                        }
                        else
                        {
                            tempN.remove(0);
                            if (!tempN.isEmpty())
                                continue;
                            else
                                break;
                        }
                    }

                if (!tempN.isEmpty())
                {
                    if (!(tempN[0]->hasPredFix()))
                    {
                        sortNodes(tempN,Strategy);
                        currNode = tempN[0];
                        currProc = QueueOfFreeProc[0];
                    }

                    QueueOfFreeProc.removeOne(currProc);
                    QueueOfReadyNodes.removeOne(currNode);
                    currNode->setExecTProc(currProc);
                    currProc->setExecNode(currNode);
                    QueueOfExecNodes << currNode;
                    QueueOfBusyProc << currProc;
                    newBusy = true;
                }
            }

        } while (newBusy);


        if (QueueOfCompletedNodes.count() == NodesCount)
        {
            AllCompleted = true;
            TotalTime = Time;
            break;
        }

        qSort(TimeEvents.begin(),TimeEvents.end());
        Time = TimeEvents.takeAt(0);
        //qDebug() << "Time" << Time;
    } while (!AllCompleted);
}

bool static sortMinTime(const TNode *v1, const TNode *v2)
{
    if (v2->getNodeTime() > v1->getNodeTime())
        return true;
    else if (v2->getNodeTime() < v1->getNodeTime())
        return false;

    if (v1->getMyTGraph()->getGraphNumber() < v2->getMyTGraph()->getGraphNumber())
        return true;
    else if (v1->getMyTGraph()->getGraphNumber() > v2->getMyTGraph()->getGraphNumber())
        return false;

    return v1->getNodeNumber() < v2->getNodeNumber();
}

bool static sortMaxTime(const TNode *v1, const TNode *v2)
{
    if (v1->getNodeTime() > v2->getNodeTime())
        return true;
    else if (v1->getNodeTime() < v2->getNodeTime())
        return false;

    if (v1->getMyTGraph()->getGraphNumber() < v2->getMyTGraph()->getGraphNumber())
        return true;
    else if (v1->getMyTGraph()->getGraphNumber() > v2->getMyTGraph()->getGraphNumber())
        return false;

    return v1->getNodeNumber() < v2->getNodeNumber();
}

bool static sortMaxChild(const TNode *v1, const TNode *v2)
{
    if (v1->getSuccNodes().count() > v2->getSuccNodes().count())
        return true;
    else if (v1->getSuccNodes().count() < v2->getSuccNodes().count())
        return false;

    if (v1->getMyTGraph()->getGraphNumber() < v2->getMyTGraph()->getGraphNumber())
        return true;
    else if (v1->getMyTGraph()->getGraphNumber() > v2->getMyTGraph()->getGraphNumber())
        return false;

    return v1->getNodeNumber() < v2->getNodeNumber();
}

bool static sortByCrits(const TNode *v1, const TNode *v2)
{
    int inCritsCountV1 = 0;
    int inCritsCountV2 = 0;
    QVector<QVector<TNode*>> CrWays = v1->getMyTGraph()->getCritWays();
    for (int i = 0; i < CrWays.count(); i++)
    {
        for (int j = 0; j < CrWays[i].count(); j++)
            inCritsCountV1 += (CrWays[i][j]->getNodeNumber() == v1->getNodeNumber())? 1 : 0;
    }
    CrWays = v2->getMyTGraph()->getCritWays();
    for (int i = 0; i < CrWays.count(); i++)
    {
        for (int j = 0; j < CrWays[i].count(); j++)
            inCritsCountV2 += (CrWays[i][j]->getNodeNumber() == v2->getNodeNumber())? 1 : 0;
    }

    if (inCritsCountV1 > inCritsCountV2)
        return true;
    else if (inCritsCountV1 < inCritsCountV2)
        return false;

    if (v1->getNodeTime() > v2->getNodeTime())
        return true;
    else if (v1->getNodeTime() < v2->getNodeTime())
        return false;

    if (v1->getMyTGraph()->getGraphNumber() < v2->getMyTGraph()->getGraphNumber())
        return true;
    else if (v1->getMyTGraph()->getGraphNumber() > v2->getMyTGraph()->getGraphNumber())
        return false;

    return v1->getNodeNumber() < v2->getNodeNumber();
}

bool static sortByFixed(const TNode *v1, const TNode *v2)
{
    if ((v1->hasPredFix()) > (v2->hasPredFix()))
        return true;
    else if ((v1->hasPredFix()) < (v2->hasPredFix()))
        return false;

    if ((v1->hasSuccFix()) > (v2->hasSuccFix()))
        return true;
    else if ((v1->hasSuccFix()) < (v2->hasSuccFix()))
        return false;

    if (v1->getNodeTime() > v2->getNodeTime())
        return true;
    else if (v1->getNodeTime() < v2->getNodeTime())
        return false;

    if (v1->getMyTGraph()->getGraphNumber() < v2->getMyTGraph()->getGraphNumber())
        return true;
    else if (v1->getMyTGraph()->getGraphNumber() > v2->getMyTGraph()->getGraphNumber())
        return false;

    return v1->getNodeNumber() < v2->getNodeNumber();
}

bool static sortProcByFinishTime(const TProc *p1, const TProc *p2)
{
    if ((p1->getProcStatus().Stat <= WaitForOtherLMFree) || (p2->getProcStatus().Stat <= WaitForOtherLMFree))
        if ((p1->getProcStatus().Stat <= WaitForOtherLMFree) && (p2->getProcStatus().Stat <= WaitForOtherLMFree))
            switch (p1->getTMachine()->getStrategy())
            {
            case MinTime:
                return sortMinTime(p1->getExecNode(),p2->getExecNode());
                break;
            case MaxTime:
                return sortMaxTime(p1->getExecNode(),p2->getExecNode());
                break;
            case MaxChild:
                return sortMaxChild(p1->getExecNode(),p2->getExecNode());
                break;
            case ByCrits:
                return sortByCrits(p1->getExecNode(),p2->getExecNode());
                break;
            }
        else
            return p1->getProcStatus().Stat > p2->getProcStatus().Stat;
    if (p1->getFinishTime() < p2->getFinishTime())
        return true;
    else if (p1->getFinishTime() > p2->getFinishTime())
        return false;

    return p1->getProcNumber() < p2->getProcNumber();
}

bool static sortProcByNum(const TProc *p1, const TProc *p2)
{
    return p1->getProcNumber() < p2->getProcNumber();
}

bool static sortBusByNum(const TBus *b1, const TBus *b2)
{
    return b1->getBusNumber() < b2->getBusNumber();
}

void sortNodes(QVector<TNode *> &targetVector, Strat targetStrategy)
{
    switch (targetStrategy)
    {
    case MinTime:
        qSort(targetVector.begin(),targetVector.end(),sortMinTime);
        break;
    case MaxTime:
        qSort(targetVector.begin(),targetVector.end(),sortMaxTime);
        break;
    case MaxChild:
        qSort(targetVector.begin(),targetVector.end(),sortMaxChild);
        break;
    case ByCrits:
        qSort(targetVector.begin(),targetVector.end(),sortByCrits);
        break;
    default:
        break;
    }
}

