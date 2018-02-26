#ifndef TGRAPH_H
#define TGRAPH_H
#include <tnode.h>
#include <ogdf/energybased/dtree/GalaxyLevel.h>
#include <ogdf/graphalg/ShortestPathWithBFM.h>
#include <algorithm>
#include <structs.h>
class TGraph
{

public:
    TGraph();
    TGraph(ogdf::energybased::dtree::GalaxyLevel Gw, int index, bool isLM, int q);
    int getNodeCount() const;
    TNode* getNode(int number);
    int getGraphNumber() const;
    double getMinTime() const;
    double getMaxTime() const;
    QVector<QVector<TNode*>> getCritWays();
    void setCritWays();
    void fixFromBig();
    void fixBigByAll();
    QVector<QVector<int>> getFixedPair();
    void setIsLocalMem(bool LocalMemFlag);
    void setQKoef(int q);
    NStat calcPredStatusNode(int nodeNum) const;
    int getErr();

private:
    QVector<TNode> NodeVect;
    int GraphNumber;
    double MinTime;
    double MaxTime;
    QVector<QVector<TNode*>> CritWays;
    void DownTMinTimes();
    void UpTMaxTimes();
    ogdf::Graph GLocal;
    void setFixNode(int currNum, int targNum);
    QVector<QVector<int>> FixedPair;
    bool IsLocalMem;
    int QKoef;
    int Err;
};

#endif // TGRAPH_H
