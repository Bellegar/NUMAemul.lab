#ifndef TPROC_H
#define TPROC_H
#include <QVector>
#include <structs.h>
class TNode;
class TBus;
class TMachine;

class TProc
{
public:
    TProc();
    TProc(int index, TMachine* currMachine);
    QVector<StatusTime<PStat>> getProcStatsHistory() const;
    QVector<TNode*> getNodesHistory() const;
    QVector<StatusTime<LMStat>> getLMStatusHistory() const;
    QVector<TProc*> getFromTProcHistory() const;
    double getProcBusyTime() const;
    double getProcLMBusyTime() const;
    int getProcNumber() const;
    TMachine* getTMachine() const;

    StatusTime<PStat> getProcStatus() const;
    void setProcStatus(StatusTime<PStat> statusProc);
    void setProcStatus(StatusTime<PStat> statusProc, TNode* execNode, TProc* fromWhichTProc);

    StatusTime<LMStat> getLocalMemoryStatus() const;
    void setLocalMemoryStatus(StatusTime<LMStat> statusLM);

    TNode* getExecNode() const;
    void setExecNode(TNode* execNode);

    TProc* getFromTProc();
    void setFromTProc(TProc* fromProc);

    double getFinishTime() const;
    void setFinishTime(double finishTime);

    int getDownloadedPartsCount() const;
    void setDownloadedPartsCount(int dwnldPartsCount);

    TBus* getUsingTBus();
    void setUsingTBus(TBus* usingTBus);


private:
    QVector<StatusTime<PStat>> ProcStatsHistory;
    QVector<StatusTime<LMStat>> LMStatusHistory;
    QVector<TNode*> NodesHistory;
    QVector<TProc*> FromTProcHistory;

    int ProcNumber;
    StatusTime<PStat> ProcStatus;
    StatusTime<LMStat> LocalMemoryStatus;
    double FinishTime;
    TNode* ExecNode;
    TProc* FromTProc;
    int DownloadedPartsCount;
    TBus* UsingTBus;
    TMachine* InMachine;

};

#endif // TPROC_H
