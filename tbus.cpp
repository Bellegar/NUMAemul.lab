#include "tbus.h"

TBus::TBus()
{

}

TBus::TBus(int index)
{
    BusStatsHistory.clear();
    FromProcNumHistory.clear();
    ToProcNumHistory.clear();
    BusNumber = index + 1;
    BusStatus = {BFree,0};
    ToProcNum = 1;
    FromProcNum = 1;

}

QVector<StatusTime<BStat>> TBus::getBusStatsHistory() const
{
    return BusStatsHistory;
}

QVector<int> TBus::getFromProcNumHistory() const
{
    return FromProcNumHistory;
}

QVector<int> TBus::getToProcNumHistory() const
{
    return ToProcNumHistory;
}

QVector<int> TBus::getGraphNumHistory() const
{
    return GraphNumHistory;
}

int TBus::getBusNumber() const
{
    return BusNumber;
}

double TBus::getBusBusyTime() const
{
    double BusyTime = 0;
    for (int i = 0; i < BusStatsHistory.count() - 1; i++)
    {
        if (BusStatsHistory[i].Stat == BBusy)
            BusyTime += BusStatsHistory[i+1].Time - BusStatsHistory[i].Time;
    }

    return BusyTime;
}

StatusTime<BStat> TBus::getBusStatus() const
{
    return BusStatus;
}

void TBus::setBusStatus(StatusTime<BStat> statusBus)
{
    BusStatus = statusBus;
    BusStatsHistory << BusStatus;
    ToProcNumHistory << ToProcNum;
    FromProcNumHistory << FromProcNum;
    GraphNumHistory << GraphNum;
}

void TBus::setBusStatus(StatusTime<BStat> statusBus, int fromProcNum, int toProcNum)
{
    BusStatus = statusBus;
    FromProcNum = fromProcNum;
    ToProcNum = toProcNum;
    BusStatsHistory << BusStatus;
    FromProcNumHistory << FromProcNum;
    ToProcNumHistory << ToProcNum;
}

int TBus::getFromProcNum() const
{
    return FromProcNum;
}

void TBus::setFromProcNum(int procNum)
{
    FromProcNum = procNum;
}

int TBus::getToProcNum() const
{
    return ToProcNum;
}

void TBus::setToProcNum(int procNum)
{
    ToProcNum = procNum;
}

int TBus::getGraphNum() const
{
    return GraphNum;
}

void TBus::setGraphNum(int graphNum)
{
    GraphNum = graphNum;
}
