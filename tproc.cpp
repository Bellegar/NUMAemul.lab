#include "tproc.h"

TProc::TProc()
{

}

TProc::TProc(int index, TMachine* currMachine)
{
    ProcStatsHistory.clear();
    LMStatusHistory.clear();
    NodesHistory.clear();
    ProcNumber = index + 1;
    ProcStatus = {Free,0};
    LocalMemoryStatus = {LMFree,0};
    FinishTime = 0;
    FromTProc = this;
    DownloadedPartsCount = 0;
    InMachine = currMachine;
}

QVector<StatusTime<PStat>> TProc::getProcStatsHistory() const
{
    return ProcStatsHistory;
}

QVector<TNode*> TProc::getNodesHistory() const
{
    return NodesHistory;
}

QVector<StatusTime<LMStat>> TProc::getLMStatusHistory() const
{
    return LMStatusHistory;
}

QVector<TProc*> TProc::getFromTProcHistory() const
{
    return FromTProcHistory;
}

double TProc::getProcBusyTime() const
{
    double BusyTime = 0;
    for (int i = 0; i < ProcStatsHistory.count() - 1; i++)
    {
        if (ProcStatsHistory[i].Stat == Busy)
            BusyTime += ProcStatsHistory[i+1].Time - ProcStatsHistory[i].Time;
    }

    return BusyTime;
}

double TProc::getProcLMBusyTime() const
{
    double BusyTime = 0;
    for (int i = 0; i < ProcStatsHistory.count() - 1; i++)
    {
        if (ProcStatsHistory[i].Stat == Busy || ProcStatsHistory[i].Stat == LoadFromLocalMem || ProcStatsHistory[i].Stat == LoadToLocalMem)
            BusyTime += ProcStatsHistory[i+1].Time - ProcStatsHistory[i].Time;
    }

    return BusyTime;
}

int TProc::getProcNumber() const
{
    return ProcNumber;
}

TMachine *TProc::getTMachine() const
{
    return InMachine;
}

StatusTime<PStat> TProc::getProcStatus() const
{
    return ProcStatus;
}

void TProc::setProcStatus(StatusTime<PStat> statusProc)
{
    ProcStatus = statusProc;
    ProcStatsHistory << statusProc;
    NodesHistory << ExecNode;
    FromTProcHistory << FromTProc;
}

void TProc::setProcStatus(StatusTime<PStat> statusProc, TNode* execNode, TProc*fromWhichTProc)
{
    ProcStatus = statusProc;
    ExecNode = execNode;
    FromTProc = fromWhichTProc;
    ProcStatsHistory << statusProc;
    NodesHistory << ExecNode;
    FromTProcHistory << fromWhichTProc;
}

StatusTime<LMStat> TProc::getLocalMemoryStatus() const
{
    return LocalMemoryStatus;
}

void TProc::setLocalMemoryStatus(StatusTime<LMStat> statusLM)
{
    LocalMemoryStatus = statusLM;
    LMStatusHistory << statusLM;
}

TNode*TProc::getExecNode() const
{
    return ExecNode;
}

void TProc::setExecNode(TNode* execNode)
{
    ExecNode = execNode;
}

TProc*TProc::getFromTProc()
{
    return FromTProc;
}

void TProc::setFromTProc(TProc*fromProc)
{
    FromTProc = fromProc;
}

double TProc::getFinishTime() const
{
    return FinishTime;
}

void TProc::setFinishTime(double finishTime)
{
    FinishTime = finishTime;
}

int TProc::getDownloadedPartsCount() const
{
    return DownloadedPartsCount;
}

void TProc::setDownloadedPartsCount(int dwnldPartsCount)
{
    DownloadedPartsCount = dwnldPartsCount;
}

TBus *TProc::getUsingTBus()
{
    return UsingTBus;
}

void TProc::setUsingTBus(TBus *usingTBus)
{
    UsingTBus = usingTBus;
}
