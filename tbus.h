#ifndef TBUS_H
#define TBUS_H
#include <QVector>
#include <structs.h>

class TBus
{
public:
    TBus();
    TBus(int index);
    QVector<StatusTime<BStat>> getBusStatsHistory() const;
    QVector<int> getFromProcNumHistory() const;
    QVector<int> getToProcNumHistory() const;
    QVector<int> getGraphNumHistory() const;
    int getBusNumber() const;
    double getBusBusyTime() const;
    StatusTime<BStat> getBusStatus() const;
    void setBusStatus(StatusTime<BStat> statusBus);
    void setBusStatus(StatusTime<BStat> statusBus, int fromProcNum, int toProcNum);

    int getFromProcNum() const;
    void setFromProcNum(int procNum);

    int getToProcNum() const;
    void setToProcNum(int procNum);

    int getGraphNum() const;
    void setGraphNum(int graphNum);

private:
    QVector<StatusTime<BStat>> BusStatsHistory;
    QVector<int> FromProcNumHistory;
    QVector<int> ToProcNumHistory;
    QVector<int> GraphNumHistory;
    int BusNumber;

    StatusTime<BStat> BusStatus;
    int FromProcNum;
    int ToProcNum;
    int GraphNum;
};

#endif // TBUS_H
