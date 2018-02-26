#ifndef STRUCTS_H
#define STRUCTS_H
#include <QVector>
class TProc;
class TNode;

typedef enum BStat {BFree, BBusy} BStat;

typedef enum Strat {MinTime, MaxTime, MaxChild, ByCrits} Strat;

typedef enum NStat {NotReady, Ready, Exec, Completed} NStat;

struct TNodeEdge
{
    int DestNodeNum;
    int EWeight;
};

typedef enum PStat {Free, WaitForBus, WaitForMyLMFree, WaitForOtherLMFree, WaitForDownload, LoadFromLocalMem, Busy, LoadToLocalMem} PStat;

typedef enum LMStat {LMFree, LMBusy} LMStat;

template<class T>
struct StatusTime
{
   T Stat;
   double Time;
};

#endif // STRUCTS_H
