#ifndef TMACHINE_H
#define TMACHINE_H
#include <tgraph.h>
#include <tproc.h>
#include <tbus.h>

class TMachine
{
public:
    TMachine();
    TMachine(int countOfProc, int countOfBus, Strat strategy, QVector<TGraph> vectorOfGraph, bool isLM, int q);
    double getTotalTime() const;
    bool isCompleted() const;
    double getProcKoef(int number) const;
    double getProcLMKoef(int number) const;
    double getAverageProcKoef() const;
    double getAverageProcLMKoef() const;
    double getBusKoef(int number) const;
    double getAverageBusКoef() const;
    Strat getStrategy() const;
    QVector<TProc> getProcVect();
    QVector<TBus> getBusVect();
    QVector<TGraph> getGraphVect();
    void RunMachine();

private:
    QVector<TProc> ProcVect;
    QVector<TBus> BusVect;
    QVector<TGraph> GraphVect;
    Strat Strategy;
    double Time;
    double TotalTime;
    QVector<double> TimeEvents;
    bool AllCompleted;

    QVector<TProc*> QueueOfFreeProc;
    QVector<TProc*> QueueOfBusyProc;

    QVector<TNode*> QueueOfReadyNodes;
    QVector<TNode*> QueueOfNotReadyNodes;
    QVector<TNode*> QueueOfExecNodes;
    QVector<TNode*> QueueOfCompletedNodes;

    QVector<TBus*> QueueOfFreeBus;
    QVector<TBus*> QueueOfBusyBus;

    int NodesCount;
    bool IsLocalMem;
    int QKoef;

};

#endif // TMACHINE_H
